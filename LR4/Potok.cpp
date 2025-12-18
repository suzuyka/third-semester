#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <chrono>
#include <random>
using namespace std;

// Кол-во потоков и объём работы
const int THREAD_COUNT = 8;
const int CHAR_COUNT = 2000;

// === Примитивы синхронизации ===

// 1. Обычный мьютекс
mutex mtx;

// 2. Спинлок (простая активная блокировка)
atomic_flag spinLock = ATOMIC_FLAG_INIT;

// 3. "Ручной" семафор на основе condition_variable
class Semaphore {
private:
    mutex m;
    condition_variable cv;
    int count;
public:
    Semaphore(int c = 1) : count(c) {}
    void acquire() {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [&]() { return count > 0; });
        --count;
    }
    void release() {
        unique_lock<mutex> lock(m);
        ++count;
        cv.notify_one();
    }
};

// создаём семафор с 3 разрешениями
Semaphore sem(3);

// 4. Барьер — ждёт пока все потоки дойдут
class SimpleBarrier {
private:
    mutex m;
    condition_variable cv;
    int counter;
    int waiting;
public:
    SimpleBarrier(int count) : counter(count), waiting(0) {}
    void arrive_and_wait() {
        unique_lock<mutex> lock(m);
        waiting++;
        if (waiting < counter) {
            cv.wait(lock);
        } else {
            waiting = 0;
            cv.notify_all();
            cout << "\n--- Все потоки дошли до барьера ---\n";
        }
    }
};
SimpleBarrier sync_point(THREAD_COUNT);

// 5. Монитор — контролирует вход и выход потоков
class Monitor {
private:
    mutex mtx;
    condition_variable cv;
    bool isFree;
public:
    Monitor() : isFree(true) {}
    void enter() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this]() { return isFree; });
        isFree = false;
    }
    void exit() {
        unique_lock<mutex> lock(mtx);
        isFree = true;
        cv.notify_one();
    }
};
Monitor monitor;

// === Служебные функции ===
char getRandomChar() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(33, 126);
    return static_cast<char>(dist(gen));
}

// === Варианты тестов ===
void testWithMutex() {
    for (int i = 0; i < CHAR_COUNT; ++i) {
        lock_guard<mutex> lock(mtx);
        cout << getRandomChar();
    }
    sync_point.arrive_and_wait();
}

void testWithSemaphore() {
    for (int i = 0; i < CHAR_COUNT; ++i) {
        sem.acquire();
        cout << getRandomChar();
        sem.release();
    }
    sync_point.arrive_and_wait();
}

void testWithSpinLock() {
    for (int i = 0; i < CHAR_COUNT; ++i) {
        while (spinLock.test_and_set(memory_order_acquire));
        cout << getRandomChar();
        spinLock.clear(memory_order_release);
    }
    sync_point.arrive_and_wait();
}

void testWithSpinWait() {
    static atomic<bool> ready = false;

    // Первый поток выставляет флаг после печати
    if (this_thread::get_id() == this_thread::get_id()) {
        for (int i = 0; i < CHAR_COUNT; ++i)
            cout << getRandomChar();
        ready = true;
    } else {
        while (!ready.load()) {
            // активное ожидание
        }
    }

    sync_point.arrive_and_wait();
}

void testWithMonitor() {
    for (int i = 0; i < CHAR_COUNT; ++i) {
        monitor.enter();
        cout << getRandomChar();
        monitor.exit();
    }
    sync_point.arrive_and_wait();
}

// === Замер производительности ===
template<typename Func>
void benchmark(const string& name, Func func) {
    auto start = chrono::high_resolution_clock::now();

    vector<thread> threads;
    for (int i = 0; i < THREAD_COUNT; ++i)
        threads.emplace_back(func);
    for (auto& th : threads)
        th.join();

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> dur = stop - start;
    cout << "\n[" << name << "] Время: " << dur.count() << " сек.\n";
}

int main() {
    cout << "=== Сравнение работы синхронизационных примитивов ===\n";
    benchmark("Mutex", testWithMutex);
    benchmark("Semaphore", testWithSemaphore);
    benchmark("SpinLock", testWithSpinLock);
    benchmark("SpinWait", testWithSpinWait);
    benchmark("Monitor", testWithMonitor);
    return 0;
}
