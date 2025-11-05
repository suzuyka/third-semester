#include "Queue.h"
#include <iostream>
#include <string>

void initQueue(DynamicQueue* queue, int initialCapacity) {
    queue->data = new std::string[initialCapacity];
    queue->size = 0;
    queue->capacity = initialCapacity;
    queue->frontIndex = 0;
    queue->backIndex = -1;
}

void freeQueue(DynamicQueue* queue) {
    delete[] queue->data;
    queue->data = nullptr;
    queue->size = 0;
    queue->capacity = 0;
    queue->frontIndex = 0;
    queue->backIndex = -1;
}

void resizeQueue(DynamicQueue* queue) {
    int newCapacity = queue->capacity * 2;
    std::string* newData = new std::string[newCapacity];

    for (int i = 0; i < queue->size; ++i) {
        newData[i] = queue->data[(queue->frontIndex + i) % queue->capacity];
    }

    delete[] queue->data;
    queue->data = newData;
    queue->capacity = newCapacity;
    queue->frontIndex = 0;
    queue->backIndex = queue->size - 1;
}

void push(DynamicQueue* queue, const std::string& value) {
    if (queue->size == queue->capacity) {
        resizeQueue(queue);
    }
    queue->backIndex = (queue->backIndex + 1) % queue->capacity;
    queue->data[queue->backIndex] = value;
    queue->size++;
}

std::string pop(DynamicQueue* queue) {//возвращение элемента
    if (queue->size == 0) {
        std::cout << "ВНИМАНИЕ: ОЧЕРЕДЬ ПУСТА\n";
        return;
    }
    queue->frontIndex = (queue->frontIndex + 1) % queue->capacity;
    queue->size--;
    return front(queue);
}

std::string front(DynamicQueue* queue) {
    if (queue->size == 0) {
        std::cout << "ВНИМАНИЕ: ОЧЕРЕДЬ ПУСТА\n";
        return "";
    }
    return queue->data[queue->frontIndex];
}

bool isEmpty(DynamicQueue* queue) {
    return queue->size == 0;
}