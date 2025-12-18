#include "../include/SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList() : head(nullptr) {} // конструктор

SinglyLinkedList::~SinglyLinkedList() { // деструктор
    while (head) {
        FNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void SinglyLinkedList::pushFront(int value) { // добавить в начало
    FNode* node = new FNode(value);
    node->next = head;
    head = node;
}

void SinglyLinkedList::pushBack(int value) { // добавить в конец
    FNode* node = new FNode(value);
    if (!head) {
        head = node;
        return;
    }
    FNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = node;
}

bool SinglyLinkedList::delByValue(int value) { // удалить по значению
    if (!head) return false;

    if (head->data == value) {
        FNode* tmp = head;
        head = head->next;
        delete tmp;
        return true;
    }

    FNode* curr = head;
    while (curr->next && curr->next->data != value) {
        curr = curr->next;
    }
    if (!curr->next) return false;

    FNode* tmp = curr->next;
    curr->next = tmp->next;
    delete tmp;
    return true;
}


int SinglyLinkedList::get(int index) { // получить по индексу
    FNode* curr = head;
    int i = 0;
    while (curr) {
        if (i == index) return curr->data;
        curr = curr->next;
        i++;
    }
    std::cerr << "Ошибка: индекс вне диапазона\n";
    return -1;
}

void SinglyLinkedList::print() const { // вывод списка
    FNode* curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

std::vector<int> SinglyLinkedList::toVector() const { // преобразовать в вектор
    std::vector<int> result;
    FNode* curr = head;
    while (curr) {
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
}

void SinglyLinkedList::insertBefore(int target, int value) { // вставить перед элементом
    if (!head) return;

    if (head->data == target) {
        pushFront(value);
        return;
    }

    FNode* curr = head;
    while (curr->next && curr->next->data != target) {
        curr = curr->next;
    }
    if (!curr->next) return; // не нашли target

    FNode* node = new FNode(value);
    node->next = curr->next;
    curr->next = node;
}

void SinglyLinkedList::insertAfter(int target, int value) { // вставить после элемента
    FNode* curr = head;
    while (curr && curr->data != target) {
        curr = curr->next;
    }
    if (!curr) return; // не нашли target

    FNode* node = new FNode(value);
    node->next = curr->next;
    curr->next = node;
}

bool SinglyLinkedList::contains(int value) const { // проверить наличие
    FNode* curr = head;
    while (curr) {
        if (curr->data == value) return true;
        curr = curr->next;
    }
    return false;
}

bool SinglyLinkedList::delFront() { // удалить первый элемент
    if (!head) {
        std::cerr << "Ошибка: список пуст\n";
        return false;
    }
    FNode* tmp = head;
    head = head->next;
    delete tmp;
    return true;
}

bool SinglyLinkedList::delBack() { // удалить последний элемент
    if (!head) {
        std::cerr << "Ошибка: список пуст\n";
        return false;
    }
    if (!head->next) { // только один элемент
        delete head;
        head = nullptr;
        return true;
    }
    FNode* curr = head;
    while (curr->next->next) {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = nullptr;
    return true;
}

// Бинарная сериализация
void SinglyLinkedList::serializeBinary(std::ostream& os) const {
    std::vector<int> vec = toVector();
    size_t size = vec.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    if (size > 0) {
        os.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(int));
    }
}

// Бинарная десериализация
void SinglyLinkedList::deserializeBinary(std::istream& is) {
    // Очищаем текущий список
    while (head) {
        FNode* tmp = head;
        head = head->next;
        delete tmp;
    }

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
void SinglyLinkedList::serializeText(std::ostream& os) const {
    std::vector<int> vec = toVector();
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) os << " ";
    }
}

// Текстовая десериализация
void SinglyLinkedList::deserializeText(std::istream& is) {
    // Очищаем текущий список
    while (head) {
        FNode* tmp = head;
        head = head->next;
        delete tmp;
    }

    // Загружаем новые данные
    int value;
    while (is >> value) {
        pushBack(value);
    }
}
