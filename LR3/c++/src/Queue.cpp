#include "../include/Queue.h"

void Queue::push(int value) { // добавить в очередь
    data.push_back(value);
}

void Queue::pop() { // удалить из начала
    if (!data.empty()) {
        data.erase(data.begin()); // удаляем первый элемент
    } else {
        std::cerr << "Ошибка: очередь пуста\n";
    }
}

int Queue::front() const { // получить первый элемент
    if (!data.empty()) {
        return data.front();
    }
    std::cerr << "Ошибка: очередь пуста\n";
    return -1;
}

bool Queue::empty() const { // проверка на пустоту
    return data.empty();
}

void Queue::print() const { // вывод очереди
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Queue::toVector() const { // преобразовать в вектор
    return data;
}

// Бинарная десериализация
void Queue::serializeBinary(std::ostream& os) const {
    size_t size = data.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    if (size > 0) {
        os.write(reinterpret_cast<const char*>(data.data()), size * sizeof(int));
    }
}

// Бинарная десериализация
void Queue::deserializeBinary(std::istream& is) {
    data.clear();
    size_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (size > 0) {
        data.resize(size);
        is.read(reinterpret_cast<char*>(data.data()), size * sizeof(int));
    }
}

// Текстовая сериализация
void Queue::serializeText(std::ostream& os) const {
    for (size_t i = 0; i < data.size(); ++i) {
        os << data[i];
        if (i < data.size() - 1) os << " ";
    }
}

// Текстовая десериализация
void Queue::deserializeText(std::istream& is) {
    data.clear();
    int value;
    while (is >> value) {
        data.push_back(value);
    }
}
