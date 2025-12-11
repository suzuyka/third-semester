#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <optional>
#include <tuple>
#include <string>
#include <limits>

#include "LFUCache.h"

using namespace std;

LFUCache::LFUCache(int cap) : capacity(cap) {}

int LFUCache::findLeastFrequentKey() {
    if (cache.empty()) return -1;

    // Найдём минимальную частоту
    int minFreq = numeric_limits<int>::max();
    for (const auto& [k, node] : cache) {
        if (node.freq < minFreq) minFreq = node.freq;
    }

    // Проходим по списку ВСТАВКИ (с головы — от старых к новым)
    DLNode* current = insertionOrder.head;
    while (current != nullptr) {
        int key = stoi(current->data);
        if (cache.count(key) && cache[key].freq == minFreq) {
            return key;
        }
        current = current->next;
    }

    return cache.begin()->first;
}

void LFUCache::set(int key, int value) {
    if (capacity <= 0) return;

    if (cache.find(key) != cache.end()) {
        cache[key].value = value;
        cache[key].freq++;
        cout << "Обновлено: (" << key << ", " << value << "), freq=" << cache[key].freq << "\n";
        return;
    }

    if ((int)cache.size() >= capacity) {
        int removeKey = findLeastFrequentKey();
        cache.erase(removeKey);
        // Удаляем ключ и из списка вставки
        insertionOrder.ListDELETEELEMENT(to_string(removeKey));
        cout << "Удалён наименее часто используемый ключ: " << removeKey << "\n";
    }

    cache[key] = {value, 1};
    insertionOrder.ListPUSHTAIL(to_string(key)); // новые — в конец
    cout << "Добавлено: (" << key << ", " << value << "), freq=1\n";
}

optional<int> LFUCache::get(int key) {
    if (cache.find(key) == cache.end()) {
        cout << "GET(" << key << ") -> -1\n";
        return nullopt;
    }
    cache[key].freq++;
    cout << "GET(" << key << ") -> " << cache[key].value << " (freq=" << cache[key].freq << ")\n";
    return cache[key].value;
}

// печать содержимого
void LFUCache::print() const {
    cout << "LFU Cache (capacity=" << capacity << ", size=" << cache.size() << "):\n";
    for (const auto& [key, node] : cache) {
        cout << "  (" << key << ", " << node.value << "), freq=" << node.freq << "\n";
    }
}

// очистка кэша
void LFUCache::clear() {
    cache.clear();
}

// преобразование в вектор
vector<pair<int,int>> LFUCache::toVector() const {
    vector<pair<int,int>> res;
    for (const auto& [key, node] : cache) {
        res.push_back({key, node.value});
    }
    return res;
}
/*
// --- Работа с файлами ---

// сохранение состояния LFU кэша в файл
void saveLFUToFile(const string& filename, const LFUCache& lfu) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return;
    }

    out << "CAPACITY " << lfu.capacity << "\n";
    
    // Сохраняем в порядке вставки
    DLNode* current = lfu.insertionOrder.head;
    while (current != nullptr) {
        int key = stoi(current->data);
        if (lfu.cache.count(key)) {
            out << key << " " << lfu.cache.at(key).value << " " << lfu.cache.at(key).freq << "\n";
        }
        current = current->next;
    }
    out.close();
}

// загрузка состояния LFU кэша из файла
void loadLFUFromFile(const string& filename, LFUCache& lfu) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Файл не найден, создаётся новый LFU Cache\n";
        return;
    }

    lfu.cache.clear();
    lfu.insertionOrder.clear(); // <-- очистка списка

    string header;
    if (in >> header && header == "CAPACITY") {
        in >> lfu.capacity;
    } else {
        lfu.capacity = 3;
    }

    // Временный вектор для сохранения порядка из файла
    vector<tuple<int, int, int>> entries; // key, value, freq

    int key, value, freq;
    while (in >> key >> value >> freq) {
        entries.emplace_back(key, value, freq);
    }
    in.close();

    // Восстанавливаем в том же порядке, в каком были записаны
    for (const auto& [k, v, f] : entries) {
        lfu.cache[k] = {v, f};
        lfu.insertionOrder.ListPUSHTAIL(to_string(k));
    }
}
*/