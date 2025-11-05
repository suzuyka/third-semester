#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>

// Узел двусвязного списка
struct DLNode {
    std::string data;
    DLNode* next;
    DLNode* prev;
    DLNode(const std::string& d) : data(d), next(nullptr), prev(nullptr) {}
};

// Контейнер-обёртка
struct DoublyLinkedList {
    DLNode* head;
    DLNode* tail;

    // Конструктор
    DoublyLinkedList();
    // Деструктор
    ~DoublyLinkedList();

    // Методы
    void ListPUSHHEAD(const std::string& data);
    void ListPUSHTAIL(const std::string& data);
    void ListPUSHAT(const std::string& data, int index);
    void ListPUSHAFTER(const std::string& data, int index);
    void ListDELETEHEAD();
    void ListDELETETAIL();
    void ListDELETEAT(int index);
    void ListDELETETHAFTER(int index);
    void ListPRINTITER() const;
    void ListDELETEELEMENT(const std::string& data);
    void ListFINDELEMENT(const std::string& data) const;

    void clear();
};

#endif