#ifndef ARRAY_H
#define ARRAY_H

#include <string>

struct MyArray {
    static const int MaxSize = 10;
    std::string data[MaxSize];
    int size;

    // Конструктор
    MyArray();

    // Методы
    void APUSH(const std::string& value);
    void AINSERT(const std::string& value, int index);
    std::string AGET(int index) const;
    void ADEL(int index);
    void ACHANGE(const std::string& value, int index);
    int ALEIGHT() const;
    void AREAD() const;
};

#endif