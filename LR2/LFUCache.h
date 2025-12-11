#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include <optional>
#include <vector>
#include <string>
#include <limits>
#include "Doublelist.h"

struct LFUNode {
    int value;
    int freq;
};

class LFUCache {
public:
    int capacity;
    LFUCache() = default;
    std::unordered_map<int, LFUNode> cache;
    DoublyLinkedList insertionOrder; // порядок вставки ключей

    LFUCache(int cap);

    void set(int key, int value);
    std::optional<int> get(int key);
    int findLeastFrequentKey();
    void print() const;
    void clear();
    std::vector<std::pair<int,int>> toVector() const;
};


#endif