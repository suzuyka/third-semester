#include "../include/Array.h"

// добавить в конец
void Array::push(int value) {
    data.push_back(value);
}

// вставка по индексу
void Array::insertAt(int index, int value) {
    if (index < 0 || index > (int)data.size()) {
        std::cerr << "Ошибка: индекс вне диапазона\n";
        return;
    }
    data.insert(data.begin() + index, value);
}

// удалить по индексу
void Array::delAt(int index) {
    if (index < 0 || index >= (int)data.size()) {
        std::cerr << "Ошибка: индекс вне диапазона\n";
        return;
    }
    data.erase(data.begin() + index);
}

// получить элемент
int Array::get(int index) {
    if (index < 0 || index >= (int)data.size()) {
        std::cerr << "Ошибка: индекс вне диапазона\n";
        return -1;
    }
    return data[index];
}

// заменить по индексу
void Array::set(int index, int value) {
    if (index < 0 || index >= (int)data.size()) {
        std::cerr << "Ошибка: индекс вне диапазона\n";
        return;
    }
    data[index] = value;
}

// длина массива
size_t Array::size() const {
    return data.size();
}

// вывод
void Array::print() const {
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// бинарная сериализация
void Array::serializeBinary(std::ostream& os) const {
    size_t size = data.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(reinterpret_cast<const char*>(data.data()), size * sizeof(int));
}

// бинарная десериализация
void Array::deserializeBinary(std::istream& is) {
    data.clear();
    size_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    data.resize(size);
    is.read(reinterpret_cast<char*>(data.data()), size * sizeof(int));
}

// текстовая сериализация
void Array::serializeText(std::ostream& os) const {
    for (size_t i = 0; i < data.size(); ++i) {
        os << data[i];
        if (i < data.size() - 1) os << " ";
    }
}

// текстовая десериализация
void Array::deserializeText(std::istream& is) {
    data.clear();
    int value;
    while (is >> value) {
        data.push_back(value);
    }
}
