#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#include <string>

struct DynamicQueue {
    std::string* data;
    int size;
    int capacity;
    int frontIndex;
    int backIndex;
};

// Инициализация пустой очереди
void initQueue(DynamicQueue* queue, int initialCapacity = 2);

// Освобождение памяти
void freeQueue(DynamicQueue* queue);

// Увеличение размера очереди в 2 раза
void resizeQueue(DynamicQueue* queue);

// Добавление элемента в конец очереди
void push(DynamicQueue* queue, const std::string& value);

// Удаление элемента из начала очереди
std::string pop(DynamicQueue* queue);

// Получение первого элемента без удаления
std::string front(DynamicQueue* queue);

// Проверка, пуста ли очередь
bool isEmpty(DynamicQueue* queue);

#endif // DYNAMIC_QUEUE_H