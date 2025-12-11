#include "Set.h"

Set::Set() : capacity(16), count(0) {
    buckets.assign(capacity, nullptr);
}

Set::~Set() {
    clear();
}

void Set::clear() {
    for (auto& head : buckets) {
        Node* current = head;
        while (current) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
        head = nullptr;
    }
    count = 0;
}

void Set::add(int value) {
    if (capacity == 0 || buckets.empty()) {
        capacity = 16;
        buckets.assign(capacity, nullptr);
    }

    size_t idx = hash(value);
    Node* current = buckets[idx];

    while (current) {
        if (current->value == value) {
            return;
        }
        current = current->next;
    }

    Node* newNode = new Node(value);
    newNode->next = buckets[idx];
    buckets[idx] = newNode;
    count++;
}


void Set::del(int value) {
    if (capacity == 0 || buckets.empty()) return;

    size_t idx = hash(value);
    Node* current = buckets[idx];
    Node* prev = nullptr;

    while (current) {
        if (current->value == value) {
            if (prev)
                prev->next = current->next;
            else
                buckets[idx] = current->next;
            delete current;
            count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

bool Set::contains(int value) const {
    if (capacity == 0 || buckets.empty()) return false;

    size_t idx = hash(value);
    Node* current = buckets[idx];

    while (current) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}


void Set::print() const {
    if (buckets.empty()) {
        std::cout << "(пусто)" << std::endl;
        return;
    }
    for (auto head : buckets) {
        Node* current = head;
        while (current) {
            std::cout << current->value << " ";
            current = current->next;
        }
    }
    std::cout << std::endl;
}

std::vector<int> Set::toVector() const {
    std::vector<int> result;
    result.reserve(count);
    for (auto head : buckets) {
        Node* current = head;
        while (current) {
            result.push_back(current->value);
            current = current->next;
        }
    }
    return result;
}
