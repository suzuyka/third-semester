#include "../include/Stack.h"

void Stack::push(int value) { // добавить в стек
    data.push_back(value);
}

void Stack::pop() { // удалить с вершины
    if (!data.empty()) {
        data.pop_back();
    } else {
        std::cerr << "Ошибка: стек пуст\n";
    }
}

int Stack::top() const { // получить вершину
    if (!data.empty()) {
        return data.back();
    }
    std::cerr << "Ошибка: стек пуст\n";
    return -1;
}

bool Stack::empty() const { // проверка на пустоту
    return data.empty();
}

void Stack::print() const { // вывод стека
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Stack::toVector() const { // преобразовать в вектор
    return data;
}

// Бинарная сериализация
void Stack::serializeBinary(std::ostream& os) const {
    size_t size = data.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    if (size > 0) {
        os.write(reinterpret_cast<const char*>(data.data()), size * sizeof(int));
    }
}

// Бинарная десериализация
void Stack::deserializeBinary(std::istream& is) {
    data.clear();
    size_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (size > 0) {
        data.resize(size);
        is.read(reinterpret_cast<char*>(data.data()), size * sizeof(int));
    }
}

// Текстовая сериализация
void Stack::serializeText(std::ostream& os) const {
    for (size_t i = 0; i < data.size(); ++i) {
        os << data[i];
        if (i < data.size() - 1) os << " ";
    }
}

// Текстовая десериализация
void Stack::deserializeText(std::istream& is) {
    data.clear();
    int value;
    while (is >> value) {
        data.push_back(value);
    }
}
