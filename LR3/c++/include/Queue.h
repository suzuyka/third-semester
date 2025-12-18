#pragma once
#include <iostream>
#include <vector>

class Queue {                              // класс очереди
private:
    std::vector<int> data;                 // внутреннее хранилище
public:
    void push(int value);                  // добавить в очередь
    void pop();                            // удалить из очереди
    int front() const;                     // посмотреть первый элемент
    bool empty() const;                    // проверка пустоты
    void print() const;                    // вывод содержимого
    std::vector<int> toVector() const;     // конвертация в вектор

    // Бинарная сериализация/десериализация
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);

    // Текстовая сериализация/десериализация
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
};
