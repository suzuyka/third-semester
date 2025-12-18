#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>
#include <random>
#include <mutex>

using namespace std;

// Структура заключения врача
struct DoctorVerdict {
    string specialty;
    char category; // A, B, C, D, E
};

// Структура призывника
struct Conscript {
    string name;
    string birth_date;
    vector<DoctorVerdict> verdicts;
};

// Генерация случайного призывника
Conscript generateConscript(int id) {
    static const vector<string> specialties = {"Терапевт", "Хирург", "Окулист", "ЛОР", "Невролог"};
    static const vector<char> categories = {'A', 'B', 'C', 'D', 'E'};
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> spec_dist(0, specialties.size() - 1);
    uniform_int_distribution<int> cat_dist(0, categories.size() - 1);

    Conscript c;
    c.name = "Призывник_" + to_string(id);
    c.birth_date = "01.01.1990"; // для простоты

    int n = 3 + gen() % 3; // 3-5 заключений
    for (int i = 0; i < n; ++i) {
        DoctorVerdict dv;
        dv.specialty = specialties[spec_dist(gen)];
        dv.category = categories[cat_dist(gen)];
        c.verdicts.push_back(dv);
    }

    return c;
}

// Проверка, пригоден ли призывник к службе (есть хотя бы одно заключение А или Б)
bool isFit(const Conscript& c) {
    for (const auto& v : c.verdicts) {
        if (v.category == 'A' || v.category == 'B') {
            return true;
        }
    }
    return false;
}

// Однопоточная обработка
vector<Conscript> processSingleThread(const vector<Conscript>& data) {
    vector<Conscript> result;
    for (const auto& c : data) {
        if (isFit(c)) {
            result.push_back(c);
        }
    }
    return result;
}

// Многопоточная обработка
vector<Conscript> processMultiThread(const vector<Conscript>& data, int num_threads) {
    vector<Conscript> result;
    mutex result_mutex;
    vector<thread> threads;

    int chunk_size = data.size() / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? data.size() : (i + 1) * chunk_size;

        threads.emplace_back([&data, &result, &result_mutex, start, end]() {
            vector<Conscript> local_result;
            for (int j = start; j < end; ++j) {
                if (isFit(data[j])) {
                    local_result.push_back(data[j]);
                }
            }
            lock_guard<mutex> lock(result_mutex);
            result.insert(result.end(), local_result.begin(), local_result.end());
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    return result;
}

int main() {
    int array_size = 10000;
    int num_threads = 4;

    // Генерация данных
    vector<Conscript> data;
    for (int i = 0; i < array_size; ++i) {
        data.push_back(generateConscript(i));
    }

    // Однопоточная обработка
    auto start = chrono::high_resolution_clock::now();
    auto single_result = processSingleThread(data);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> single_time = end - start;

    // Многопоточная обработка
    start = chrono::high_resolution_clock::now();
    auto multi_result = processMultiThread(data, num_threads);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> multi_time = end - start;

    // Вывод результатов
    cout << "Всего призывников: " << array_size << "\n";
    cout << "Пригодных к службе (однопоточно): " << single_result.size() << "\n";
    cout << "Пригодных к службе (многопоточно): " << multi_result.size() << "\n";
    cout << "Время однопоточной обработки: " << single_time.count() << " сек.\n";
    cout << "Время многопоточной обработки: " << multi_time.count() << " сек.\n";

    // Для отчёта можно вывести первые 10 пригодных
    cout << "\n10 пригодных призывников:\n";
    for (int i = 0; i < min(10, (int)multi_result.size()); ++i) {
        cout << multi_result[i].name << "\n";
    }

    return 0;
}
