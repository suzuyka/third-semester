#include "../include/DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {} // конструктор

DoublyLinkedList::~DoublyLinkedList() { // деструктор
    while (head) {
        LNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void DoublyLinkedList::pushFront(int value) { // добавить в начало
    LNode* node = new LNode(value);
    node->next = head;
    if (head) head->prev = node;
    head = node;
    if (!tail) tail = node;
}

void DoublyLinkedList::pushBack(int value) { // добавить в конец
    LNode* node = new LNode(value);
    node->prev = tail;
    if (tail) tail->next = node;
    tail = node;
    if (!head) head = node;
}

bool DoublyLinkedList::delByValue(int value) { // удалить по значению
    LNode* curr = head;
    while (curr && curr->data != value) {
        curr = curr->next;
    }
    if (!curr) return false; // не нашли

    if (curr->prev) curr->prev->next = curr->next;
    else head = curr->next; // удаляем голову

    if (curr->next) curr->next->prev = curr->prev;
    else tail = curr->prev; // удаляем хвост

    delete curr;
    return true;
}

int DoublyLinkedList::get(int index) { // получить по индекс
    LNode* curr = head;
    int i = 0;
    while (curr) {
        if (i == index) return curr->data;
        curr = curr->next;
        i++;
    }
    std::cerr << "Ошибка: индекс вне диапазона\n";
    return -1;
}

void DoublyLinkedList::print() const { // вывод списка
    LNode* curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

void DoublyLinkedList::insertBefore(int target, int value) { // вставить перед элементом
    LNode* curr = head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    if (!curr) return; // не нашли target

    LNode* node = new LNode(value);
    node->next = curr;
    node->prev = curr->prev;

    if (curr->prev) {
        curr->prev->next = node;
    } else {
        head = node; // вставка перед головой
    }
    curr->prev = node;
}

void DoublyLinkedList::insertAfter(int target, int value) { // вставить после элемента
    LNode* curr = head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    if (!curr) return; // не нашли target

    LNode* node = new LNode(value);
    node->prev = curr;
    node->next = curr->next;

    if (curr->next) {
        curr->next->prev = node;
    } else {
        tail = node; // вставка в хвост
    }
    curr->next = node;
}


std::vector<int> DoublyLinkedList::toVector() const { // преобразовать в вектор
    std::vector<int> result;
    LNode* curr = head;
    while (curr) {
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
}

bool DoublyLinkedList::contains(int value) const { // проверить наличие
    LNode* curr = head;
    while (curr) {
        if (curr->data == value) return true;
        curr = curr->next;
    }
    return false;
}

bool DoublyLinkedList::delFront() { // удалить первый элемент
    if (!head) {
        std::cerr << "Ошибка: список пуст\n";
        return false;
    }
    LNode* tmp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr; // список стал пуст
    delete tmp;
    return true;
}

bool DoublyLinkedList::delBack() { // удалить последний элемент
    if (!tail) {
        std::cerr << "Ошибка: список пуст\n";
        return false;
    }
    LNode* tmp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr; // список стал пуст
    delete tmp;
    return true;
}

// Бинарная сериализация
void DoublyLinkedList::serializeBinary(std::ostream& os) const {
    std::vector<int> vec = toVector();
    size_t size = vec.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    if (size > 0) {
        os.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(int));
    }
}

// Бинарная десериализация
void DoublyLinkedList::deserializeBinary(std::istream& is) {
    // Очищаем текущий список
    while (head) {
        LNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;

    // Загружаем новые данные
    size_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (size > 0) {
        std::vector<int> temp(size);
        is.read(reinterpret_cast<char*>(temp.data()), size * sizeof(int));

        for (int value : temp) {
            pushBack(value);
        }
    }
}

// Текстовая сериализация
void DoublyLinkedList::serializeText(std::ostream& os) const {
    std::vector<int> vec = toVector();
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) os << " ";
    }
}

// Текстовая десериализация
void DoublyLinkedList::deserializeText(std::istream& is) {
    // Очищаем текущий список
    while (head) {
        LNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;

    // Загружаем новые данные
    int value;
    while (is >> value) {
        pushBack(value);
    }
}
