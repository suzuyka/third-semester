#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include <utility>


// Методы хеширования
enum class HashType { DOUBLE_HASHING, CUCKOO_HASHING, FOLDING_HASHING };

class HashTable {
private:
    std::vector<std::optional<std::pair<int, int>>> table;
    int size;
    HashType type;

    // Основные хеш-функции
    int hashFunc1(int key) const { return key % size; }
    int hashFunc2(int key) const { return 1 + (key % (size - 1)); }

    // Метод свёртки — folding hash
    int hash1(int key) const;
    int foldingHash(int key, bool verbose = false) const;

    // Проверка заполненности
    double loadFactor() const;

    // Реорганизация таблицы (rehash)
    void rehash();
    void cuckooRehash();

    // Основная вставка для кукушки
    void insertCuckoo(int key, int value);

public:
    HashTable(int s = 11, HashType t = HashType::DOUBLE_HASHING);   // конструктор хеш-таблицы

    void insert(int key, int value);                                // вставка пары в таблицу
    bool remove(int key);                                           // удаление элемента по ключу
    std::vector<std::pair<int,int>> toVector() const;               // экспорт содержимого таблицы
    HashType getType() const { return type; }                       // узнать текущий режим
    int getSize() const { return size; }                            // узнать текущий размер
    std::optional<int> get(int key) const;                          // поиск значения по ключу
    void print() const;                                             // печать таблицы
    void clear();                                                   // очистка

    // Бинарная сериализация/десериализация
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);

    // Текстовая сериализация/десериализация
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
};
