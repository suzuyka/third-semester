#pragma once
#include <iostream>
#include <vector>

class Set {
private:
    struct Node {
        int value;
        Node* next;
        Node(int v) : value(v), next(nullptr) {}
    };

    std::vector<Node*> buckets;
    size_t capacity;
    size_t count;

    size_t hash(int value) const {
        if (capacity == 0) return 0;
        return (static_cast<unsigned long>(value) * 2654435761u) % capacity;
    }

    void clear(); 

public:
    Set();
    ~Set();

    void add(int value);
    void del(int value);
    bool contains(int value) const;
    void print() const;
    std::vector<int> toVector() const;
};
