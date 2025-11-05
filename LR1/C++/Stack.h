#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include <string>

struct DynamicStack {
    std::string* data;
    int size;
    int capacity;
};

// Инициализация пустого стека
void initStack(DynamicStack* stack, int initialCapacity = 2);

// Освобождение памяти
void freeStack(DynamicStack* stack);

// Увеличение ёмкости стека в 2 раза
void resizeStack(DynamicStack* stack);

// Добавление элемента наверх стека
void push(DynamicStack* stack, const std::string& value);

// Удаление верхнего элемента
std::string pop(DynamicStack* stack);

// Чтение верхнего элемента (без удаления)
std::string top(DynamicStack* stack);

// Проверка, пуст ли стек
bool isEmpty(DynamicStack* stack);

#endif // DYNAMIC_STACK_H