#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;

const int PHILOSOPHERS = 5; // кол-во философов
const int EAT_ROUNDS = 5;    // сколько раз каждый поест
const int THINK_TIME = 500;   // макс. время мышления (мс)
const int EAT_TIME = 500;    // макс. время еды (мс)

// Мьютексы для каждой вилки (чтобы не было deadlock, философы берут сначала меньшую)
vector<mutex> forks(PHILOSOPHERS);

// Мьютекс для синхронизации вывода, чтобы сообщения не "перемешивались"
mutex cout_mutex;

// Генератор случайных чисел для симуляции задержек
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> think_dist(100, THINK_TIME); // время мышления
uniform_int_distribution<int> eat_dist(100, EAT_TIME);      // время еды

void philosopher(int id) {
    int left = id;          // левая вилка
    int right = (id + 1) % PHILOSOPHERS; // правая вилка

    // Каждый философ будет есть EAT_ROUNDS раз
    for (int round = 0; round < EAT_ROUNDS; ++round) {
        // Философ думает
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Философ " << id << " думает..." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(think_dist(gen)));

        // Чтобы избежать deadlock, сначала берём вилку с меньшим номером
        int first = min(left, right);
        int second = max(left, right);

        // Блокируем обе вилки
        {
            lock_guard<mutex> lock1(forks[first]);
            lock_guard<mutex> lock2(forks[second]);

            // Философ ест
            {
                lock_guard<mutex> lock(cout_mutex);
                cout << "Философ " << id << " ест (раз " << round + 1 << ")..." << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(eat_dist(gen)));
        }

        // Вилки автоматически освобождаются при выходе из блока
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Философ " << id << " закончил есть (раз " << round + 1 << ")." << endl;
        }
    }

    // Философ закончил есть и уходит
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Философ " << id << " полностью наелся и ушёл." << endl;
    }
}

int main() {
    // Создаём потоки для каждого философа
    vector<thread> philosophers;
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        philosophers.emplace_back(philosopher, i);
    }

    // Ждём завершения всех потоков
    for (auto& p : philosophers) {
        p.join();
    }

    return 0;
}
