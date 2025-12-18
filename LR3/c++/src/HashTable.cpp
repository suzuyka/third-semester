#include "../include/HashTable.h"
#include <cmath>
#include <algorithm>

// конструктор
HashTable::HashTable(int s, HashType t)
: size(s), type(t) {
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
    std::vector<std::optional<std::pair<int, int>>> old = table;
    table.clear();
    table.resize(size);

    for (auto &entry : old) {
        if (entry.has_value())
            insert(entry->first, entry->second);
    }
}

// пеорганизация кукушкиной таблицы (если зациклилась)
void HashTable::cuckooRehash() {
    size *= 2;
    std::vector<std::optional<std::pair<int, int>>> old = table;
    table.clear();
    table.resize(size);

    for (auto &entry : old) {
        if (entry.has_value())
            insert(entry->first, entry->second);
    }
}

// вставка элемента
void HashTable::insert(int key, int value) {
    if (loadFactor() > 0.7)
        rehash();

    if (type == HashType::FOLDING_HASHING) {
        int index = foldingHash(key, true);
        if (!table[index].has_value() || table[index]->first == key) {
            table[index] = {key, value};
            return;
        } else {
            rehash();
            insert(key, value);
        }
        return;
    }

    if (type == HashType::DOUBLE_HASHING) {
        int h1 = hashFunc1(key);
        int h2 = hashFunc2(key);

        for (int i = 0; i < size; ++i) {
            int index = (h1 + i * h2) % size;
            if (!table[index].has_value() || table[index]->first == key) {
                table[index] = {key, value};
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
    const int MAX_ITER = size; // защита от зацикливания

    for (int i = 0; i < MAX_ITER; ++i) {
        int pos1 = hashFunc1(keyToInsert);
        if (!table[pos1].has_value()) {
            table[pos1] = {keyToInsert, valueToInsert};
            return;
        }

        std::swap(keyToInsert, table[pos1]->first);
        std::swap(valueToInsert, table[pos1]->second);

        int pos2 = hashFunc2(keyToInsert);
        if (!table[pos2].has_value()) {
            table[pos2] = {keyToInsert, valueToInsert};
            return;
        }

        std::swap(keyToInsert, table[pos2]->first);
        std::swap(valueToInsert, table[pos2]->second);
    }

    // если зациклились — расширяем таблицу
    cuckooRehash();
    insertCuckoo(keyToInsert, valueToInsert);
}

// удаление
bool HashTable::remove(int key) {
    // ---- Folding ----
    if (type == HashType::FOLDING_HASHING) {
        int idx = foldingHash(key, false);
        if (idx >= 0 && idx < size && table[idx].has_value() && table[idx]->first == key) {
            table[idx].reset();
            return true;
        }
        return false;
    }

    // ---- Double hashing ----
    int h1 = hashFunc1(key);
    int h2 = hashFunc2(key);
    for (int i = 0; i < size; ++i) {
        int index = (h1 + i * h2) % size;
        if (table[index].has_value() && table[index]->first == key) {
            table[index].reset();
            return true;
        }
        if (!table[index].has_value()) break; // встретили пустой слот — дальше искать не имеет смысла
    }

    // ---- Cuckoo: проверяем две позиции ----
    if (type == HashType::CUCKOO_HASHING) {
        int i1 = hashFunc1(key);
        int i2 = hashFunc2(key);
        if (table[i1].has_value() && table[i1]->first == key) { table[i1].reset(); return true; }
        if (table[i2].has_value() && table[i2]->first == key) { table[i2].reset(); return true; }
    }

    return false;
}

// поиск
std::optional<int> HashTable::get(int key) const {
    // ---- Folding (метод свёртки) ----
    if (type == HashType::FOLDING_HASHING) {
        int idx = foldingHash(key, false);
        if (idx >= 0 && idx < size && table[idx].has_value() && table[idx]->first == key)
            return table[idx]->second;
        return std::nullopt;
    }

    // ---- Cuckoo ----
    if (type == HashType::CUCKOO_HASHING) {
        int i1 = hashFunc1(key);
        int i2 = hashFunc2(key);
        if (table[i1].has_value() && table[i1]->first == key) return table[i1]->second;
        if (table[i2].has_value() && table[i2]->first == key) return table[i2]->second;
        return std::nullopt;
    }

    // ---- Double hashing (по умолчанию) ----
    int h1 = hashFunc1(key);
    int h2 = hashFunc2(key);
    for (int i = 0; i < size; ++i) {
        int index = (h1 + i * h2) % size;
        if (!table[index].has_value()) return std::nullopt; // если пусто — дальше искать некуда
        if (table[index]->first == key) return table[index]->second;
    }
    return std::nullopt;
}


// печать
void HashTable::print() const {
    for (int i = 0; i < size; ++i) {
        std::cout << i << ": ";
        if (table[i].has_value())
            std::cout << "(" << table[i]->first << ", " << table[i]->second << ")";
        std::cout << "\n";
    }
}

// преобразование в вектор
std::vector<std::pair<int,int>> HashTable::toVector() const {
    std::vector<std::pair<int,int>> res;
    for (const auto &slot : table) {
        if (slot.has_value()) res.push_back(slot.value());
    }
    return res;
}

// основная хеш-функция в зависимости от выбранного типа
int HashTable::hash1(int key) const {
    switch (type) {
        case HashType::DOUBLE_HASHING:
            return key % size;
        case HashType::CUCKOO_HASHING:
            return (key * 1315423911u) % size;
        case HashType::FOLDING_HASHING:
            return foldingHash(key, false);
    }
    return key % size; // по умолчанию
}

// хеш-функция методом свёртки
int HashTable::foldingHash(int key, bool verbose) const {
    int originalKey = key;
    int sum = 0;
    std::vector<int> parts;

    // разбиваем по три цифры и запоминаем каждую часть
    while (key > 0) {
        int part = key % 1000;
        parts.push_back(part);
        sum += part;
        key /= 1000;
    }

    int index = sum % size;

    if (verbose) {
        std::cout << "[Folding hash] Ключ: " << originalKey << " → части: ";
        for (int i = (int)parts.size() - 1; i >= 0; --i) {
            std::cout << parts[i];
            if (i != 0) std::cout << " + ";
        }
        std::cout << " = " << sum << " → индекс: " << index << std::endl;
    }

    return index;
}

// бинарная сериализация
void HashTable::serializeBinary(std::ostream& os) const {
    // Сохраняем метаданные
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    int typeInt = static_cast<int>(type);
    os.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));

    // Сохраняем данные таблицы
    for (const auto& slot : table) {
        bool hasValue = slot.has_value();
        os.write(reinterpret_cast<const char*>(&hasValue), sizeof(hasValue));

        if (hasValue) {
            os.write(reinterpret_cast<const char*>(&slot->first), sizeof(slot->first));
            os.write(reinterpret_cast<const char*>(&slot->second), sizeof(slot->second));
        }
    }
}

// бинарная десериализация
void HashTable::deserializeBinary(std::istream& is) {
    // Читаем метаданные
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    int typeInt;
    is.read(reinterpret_cast<char*>(&typeInt), sizeof(typeInt));
    type = static_cast<HashType>(typeInt);

    // восстанавливаем таблицу
    table.resize(size);
    for (int i = 0; i < size; ++i) {
        bool hasValue;
        is.read(reinterpret_cast<char*>(&hasValue), sizeof(hasValue));

        if (hasValue) {
            int key, value;
            is.read(reinterpret_cast<char*>(&key), sizeof(key));
            is.read(reinterpret_cast<char*>(&value), sizeof(value));
            table[i] = std::make_pair(key, value);
        } else {
            table[i].reset();
        }
    }
}

// текстовая сериализация
void HashTable::serializeText(std::ostream& os) const {
    os << "TYPE ";
    switch (type) {
        case HashType::DOUBLE_HASHING:  os << "DOUBLE\n"; break;
        case HashType::CUCKOO_HASHING:  os << "CUCKOO\n"; break;
        case HashType::FOLDING_HASHING: os << "FOLDING\n"; break;
    }

    os << "SIZE " << size << "\n";

    for (const auto& slot : table) {
        if (slot.has_value()) {
            os << slot->first << " " << slot->second << "\n";
        }
    }
}

// текстовая десериализация
void HashTable::deserializeText(std::istream& is) {
    std::string token;
    is >> token;

    if (token == "TYPE") {
        std::string typeStr;
        is >> typeStr;

        if (typeStr == "DOUBLE") type = HashType::DOUBLE_HASHING;
        else if (typeStr == "CUCKOO") type = HashType::CUCKOO_HASHING;
        else if (typeStr == "FOLDING") type = HashType::FOLDING_HASHING;

        is >> token; // "SIZE"
        is >> size;
    } else {
        // Старый формат файла
        size = 11;
        type = HashType::DOUBLE_HASHING;
        is.seekg(0); // Возвращаемся к началу файла
    }

    table.resize(size);
    int key, value;
    while (is >> key >> value) {
        insert(key, value);
    }
}
