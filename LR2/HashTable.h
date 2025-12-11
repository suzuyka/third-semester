#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include <utility>

enum class HashType { DOUBLE_HASHING, CUCKOO_HASHING };

class HashTable {
private:
    std::vector<std::optional<std::pair<int, int>>> table;
    int size;
    HashType type;

    int hashFunc1(int key) const { return key % size; }
    int hashFunc2(int key) const { return 1 + (key % (size - 1)); }

    double loadFactor() const;
    void rehash();
    void cuckooRehash();
    void insertCuckoo(int key, int value);

public:
    HashTable(int s = 11, HashType t = HashType::DOUBLE_HASHING);
    void insert(int key, int value);
    bool remove(int key);
    std::vector<std::pair<int,int>> toVector() const;
    HashType getType() const { return type; }
    int getSize() const { return size; }
    std::optional<int> get(int key) const;
    void print() const;
    void clear();
};