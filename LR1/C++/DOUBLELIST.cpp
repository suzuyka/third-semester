#include <iostream>
#include "Doublelist.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

void DoublyLinkedList::clear() {
    while (head != nullptr) {
        ListDELETEHEAD();
    }
}

// Добавление в голову
void DoublyLinkedList::ListPUSHHEAD(const string& data) {
    DLNode* newNode = new DLNode(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    cout << "Добавлено в начало: " << data << endl;
}

// Добавление в хвост
void DoublyLinkedList::ListPUSHTAIL(const string& data) {
    DLNode* newNode = new DLNode(data);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    cout << "Добавлено в конец: " << data << endl;
}

// Вставка до индекса
void DoublyLinkedList::ListPUSHAT(const string& data, int index) {
    if (index == 0) {
        ListPUSHHEAD(data);
        return;
    }

    DLNode* current = head;
    int i = 0;
    while (current != nullptr && i < index) {
        current = current->next;
        i++;
    }

    if (current == nullptr) {
        cout << "ВНИМАНИЕ: ВЫХОД ЗА ПРЕДЕЛЫ\n";
        return;
    }

    DLNode* newNode = new DLNode(data);
    DLNode* prev = current->prev;

    newNode->next = current;
    newNode->prev = prev;
    if (prev) prev->next = newNode;
    current->prev = newNode;

    cout << "Добавлено на позицию " << index << ": " << data << endl;
}

// Вставка после индекса
void DoublyLinkedList::ListPUSHAFTER(const string& data, int index) {
    DLNode* current = head;
    int i = 0;
    while (current != nullptr && i < index) {
        current = current->next;
        i++;
    }
    if (current == nullptr) {
        cout << "ВНИМАНИЕ: ВЫХОД ЗА ПРЕДЕЛЫ\n";
        return;
    }

    DLNode* newNode = new DLNode(data);
    newNode->next = current->next;
    newNode->prev = current;
    if (current->next) current->next->prev = newNode;
    current->next = newNode;

    if (current == tail) tail = newNode;

    cout << "Добавлено после позиции " << index << ": " << data << endl;
}

// Удаление головы
void DoublyLinkedList::ListDELETEHEAD() {
    if (head == nullptr) return;
    
    DLNode* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    
    delete temp;
    cout << "Удален первый элемент" << endl;
}

// Удаление хвоста
void DoublyLinkedList::ListDELETETAIL() {
    if (tail == nullptr) return;
    
    DLNode* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    
    delete temp;
    cout << "Удален последний элемент" << endl;
}

// Удаление до индекса
void DoublyLinkedList::ListDELETEAT(int index) {
    if (head == nullptr) return;
    
    if (index == 1) {
        ListDELETEHEAD();
        return;
    }

    DLNode* current = head;
    int i = 0;
    while (current != nullptr && i < index - 1) {
        current = current->next;
        i++;
    }

    if (current == nullptr) {
        cout << "ВНИМАНИЕ: неверный индекс\n";
        return;
    }

    if (current == tail) {
        ListDELETETAIL();
        return;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    cout << "Удален элемент до индекса " << index << endl;
}

// Удаление после индекса
void DoublyLinkedList::ListDELETETHAFTER(int index) {
    if (head == nullptr) return;

    DLNode* current = head;
    int i = 0;
    while (current != nullptr && i < index) {
        current = current->next;
        i++;
    }

    if (current == nullptr || current->next == nullptr) {
        cout << "ВНИМАНИЕ: неверный индекс\n";
        return;
    }

    DLNode* toDelete = current->next;
    current->next = toDelete->next;
    if (toDelete->next) toDelete->next->prev = current;
    if (toDelete == tail) tail = current;

    delete toDelete;
    cout << "Удален элемент после индекса " << index << endl;
}

// Итеративный вывод списка
void DoublyLinkedList::ListPRINTITER() const {
    DLNode* current = head;
    cout << "Двусвязный список: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Удаление элемента по значению
void DoublyLinkedList::ListDELETEELEMENT(const string& data) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }

    DLNode* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            if (current == head) {
                ListDELETEHEAD();
            } else if (current == tail) {
                ListDELETETAIL();
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            cout << "Удален элемент: " << data << endl;
            return;
        }
        current = current->next;
    }
    cout << "Элемент не найден: " << data << endl;
}

// Поиск элемента по значению
void DoublyLinkedList::ListFINDELEMENT(const string& data) const {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }

    int index = 0;
    DLNode* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            cout << "Найден на позиции: " << index << endl;
            return;
        }
        current = current->next;
        index++;
    }
    cout << "Элемент не найден: " << data << endl;
}