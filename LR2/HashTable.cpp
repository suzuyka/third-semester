#include "HashTable.h"
#include <cmath>
#include <algorithm>

using namespace std;

// конструктор
HashTable::HashTable(int s, HashType t) : size(s), type(t) {
    table.resize(size);
}

// подсчёт коэффициента загрузки
double HashTable::loadFactor() const {
    int filled = 0;
    for (auto &slot : table) {
        if (slot.has_value()) ++filled;
    }
    return static_cast<double>(filled) / size;
}

// полная очистка
void HashTable::clear() {
    table.clear();
    table.resize(size);
}

// увеличение таблицы (удвоение)
void HashTable::rehash() {
    size *= 2;
    vector<optional<pair<int, int>>> old = table;
    table.clear();
    table.resize(size);

    for (auto &entry : old) {
        if (entry.has_value())
            insert(entry->first, entry->second);
    }
}

// реорганизация кукушкиной таблицы (если зациклилась)
void HashTable::cuckooRehash() {
    size *= 2;
    vector<optional<pair<int, int>>> old = table;
    table.clear();
    table.resize(size);

    for (auto &entry : old) {
        if (entry.has_value())
            insert(entry->first, entry->second);
    }
}

// основной метод вставки
void HashTable::insert(int key, int value) {
    // Проверяем, существует ли ключ — для корректного обновления
    if (type == HashType::CUCKOO_HASHING) {
        auto existing = get(key);
        if (existing.has_value()) {
            // Обновляем значение на месте
            int pos1 = hashFunc1(key);
            int pos2 = hashFunc2(key);
            if (table[pos1].has_value() && table[pos1]->first == key) {
                table[pos1]->second = value;
            } else if (table[pos2].has_value() && table[pos2]->first == key) {
                table[pos2]->second = value;
            }
            return;
        }
    }

    if (loadFactor() > 0.9)
        rehash();

    if (type == HashType::DOUBLE_HASHING) {
        int h1 = hashFunc1(key);
        int h2 = hashFunc2(key);

        for (int i = 0; i < size; ++i) {
            int index = (h1 + i * h2) % size;
            if (!table[index].has_value()) {
                table[index] = {key, value};
                return;
            }
            if (table[index]->first == key) {
                table[index]->second = value;
                return;
            }
        }

        rehash();
        insert(key, value);
    }
    else if (type == HashType::CUCKOO_HASHING) {
        insertCuckoo(key, value);
    }
}

// реализация кукушкиного метода с вытеснением
void HashTable::insertCuckoo(int key, int value) {
    int keyToInsert = key;
    int valueToInsert = value;
    const int MAX_ITER = size;

    for (int i = 0; i < MAX_ITER; ++i) {
        int pos1 = hashFunc1(keyToInsert);
        if (!table[pos1].has_value()) {
            table[pos1] = {keyToInsert, valueToInsert};
            return;
        }

        swap(keyToInsert, table[pos1]->first);
        swap(valueToInsert, table[pos1]->second);

        int pos2 = hashFunc2(keyToInsert);
        if (!table[pos2].has_value()) {
            table[pos2] = {keyToInsert, valueToInsert};
            return;
        }

        swap(keyToInsert, table[pos2]->first);
        swap(valueToInsert, table[pos2]->second);
    }

    cuckooRehash();
    insertCuckoo(keyToInsert, valueToInsert);
}

// удаление
bool HashTable::remove(int key) {
    if (type == HashType::CUCKOO_HASHING) {
        int i1 = hashFunc1(key);
        int i2 = hashFunc2(key);
        if (table[i1].has_value() && table[i1]->first == key) {
            table[i1].reset();
            return true;
        }
        if (table[i2].has_value() && table[i2]->first == key) {
            table[i2].reset();
            return true;
        }
        return false;
    }

    // Double hashing
    int h1 = hashFunc1(key);
    int h2 = hashFunc2(key);
    for (int i = 0; i < size; ++i) {
        int index = (h1 + i * h2) % size;
        if (table[index].has_value() && table[index]->first == key) {
            table[index].reset();
            return true;
        }
        if (!table[index].has_value()) break;
    }
    return false;
}

// поиск
optional<int> HashTable::get(int key) const {
    if (type == HashType::CUCKOO_HASHING) {
        int i1 = hashFunc1(key);
        int i2 = hashFunc2(key);
        if (table[i1].has_value() && table[i1]->first == key) 
            return table[i1]->second;
        if (table[i2].has_value() && table[i2]->first == key) 
            return table[i2]->second;
        return nullopt;
    }

    // Double hashing
    int h1 = hashFunc1(key);
    int h2 = hashFunc2(key);
    for (int i = 0; i < size; ++i) {
        int index = (h1 + i * h2) % size;
        if (!table[index].has_value()) 
            return nullopt;
        if (table[index]->first == key) 
            return table[index]->second;
    }
    return nullopt;
}

// печать
void HashTable::print() const {
    for (int i = 1; i < size + 1; ++i) {
        cout << i << ": ";
        if (table[i].has_value())
            cout << "(" << table[i]->first << ", " << table[i]->second << ")";
        cout << "\n";
    }
}

// преобразование в вектор
vector<pair<int,int>> HashTable::toVector() const {
    vector<pair<int,int>> res;
    for (const auto &slot : table) {
        if (slot.has_value()) 
            res.push_back(slot.value());
    }
    return res;
}