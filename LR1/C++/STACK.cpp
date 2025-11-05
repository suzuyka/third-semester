#include "Stack.h"
#include <iostream>
#include <string>

void initStack(DynamicStack* stack, int initialCapacity) {
    stack->data = new std::string[initialCapacity];
    stack->size = 0;
    stack->capacity = initialCapacity;
}

void freeStack(DynamicStack* stack) {
    delete[] stack->data;
    stack->data = nullptr;
    stack->size = 0;
    stack->capacity = 0;
}

void resizeStack(DynamicStack* stack) {
    int newCapacity = stack->capacity * 2;
    std::string* newData = new std::string[newCapacity];

    for (int i = 0; i < stack->size; ++i) {
        newData[i] = stack->data[i];
    }

    delete[] stack->data;
    stack->data = newData;
    stack->capacity = newCapacity;
}

void push(DynamicStack* stack, const std::string& value) {
    if (stack->size == stack->capacity) {
        resizeStack(stack);
    }
    stack->data[stack->size] = value;
    stack->size++;
}

std::string pop(DynamicStack* stack) {//возвращала этот элемент!
    if (stack->size == 0) {
        std::cout << "ВНИМАНИЕ: СТЕК ПУСТ\n";
        return;
    }
    //std::cout << top(stack) << std::endl;
    stack->size--;
    return top(stack);
}

std::string top(DynamicStack* stack) {
    if (stack->size == 0) {
        std::cout << "ВНИМАНИЕ: СТЕК ПУСТ\n";
        return "";
    }
    return stack->data[stack->size - 1];
}

bool isEmpty(DynamicStack* stack) {
    return stack->size == 0;
}