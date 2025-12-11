#include <iostream>
#include "Array.h"

using namespace std;

MyArray::MyArray() : size(0) {}

// Добавление в конец
void MyArray::APUSH(const string& value) {
    if (size < MaxSize) {
        data[size] = value;
        size++;
        //cout << "Добавлено в массив: " << value << endl;
    } else {
        cout << "ВНИМАНИЕ: выход за пределы массива\n";
    }
}

// Добавление по индексу
void MyArray::AINSERT(const string& value, int index) {
    if (size >= MaxSize) {
        cout << "ВНИМАНИЕ: массив полон\n";
        return;
    }
    if (index < 0 || index > size) {
        cout << "ВНИМАНИЕ: неверный индекс\n";
        return;
    }
    
    for (int i = size; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
    cout << "Добавлено в массив на позицию " << index << ": " << value << endl;
}

// Получение элемента по индексу
string MyArray::AGET(int index) const {
    if (index >= 0 && index < size) {
        return data[index];
    }
    cout << "ВНИМАНИЕ: неверный индекс\n";
    return "";
}

// Удаление элемента по индексу
void MyArray::ADEL(int index) {
    if (index < 0 || index >= size) {
        cout << "ВНИМАНИЕ: неверный индекс\n";
        return;
    }
    
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    cout << "Удален элемент с индексом " << index << endl;
}

// Замена элемента по индексу
void MyArray::ACHANGE(const string& value, int index) {
    if (index >= 0 && index < size) {
        data[index] = value;
        cout << "Элемент с индексом " << index << " изменен на: " << value << endl;
    } else {
        cout << "ВНИМАНИЕ: неверный индекс\n";
    }
}

// Длина массива
int MyArray::ALEIGHT() const {
    return size;
}

// Чтение массива
void MyArray::AREAD() const {
    cout << "Массив [" << size << "/" << MaxSize << "]: ";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << endl;
}