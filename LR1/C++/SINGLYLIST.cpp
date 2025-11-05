#include "SinglyList.h"
#include <string>
#include <iostream>

List::List(const std::string& data) : Data(data), Next(nullptr) {}

void ListPUSHHEAD(List*& head, const std::string& data) {
    List* p = new List(data);
    p->Next = head;
    head = p;
}

void ListPUSHTAIL(List*& head, const std::string& data) {
    List* p = new List(data);
    if (head == nullptr) {
        head = p;
        return;
    }

    List* current = head;
    while (current->Next != nullptr) {
        current = current->Next;
    }
    current->Next = p;
}

void ListPUSHAT(List*& head, const std::string& data, int index) {
    if (index == 0) {
        ListPUSHHEAD(head, data);
        return;
    }

    List* current = head;
    for (int i = 0; i < index - 1 && current != nullptr; ++i) {
        current = current->Next;
    }

    if (current == nullptr) {
        std::cout << "ВНИМАНИЕ: ВЫХОД ЗА ПРЕДЕЛЫ\n";
        return;
    }

    List* p = new List(data);
    p->Next = current->Next;
    current->Next = p;
}

void ListPUSHAFTER(List*& head, const std::string& data, int index) {
    List* current = head;
    for (int i = 0; i < index && current != nullptr; ++i) {
        current = current->Next;
    }

    if (current == nullptr) {
        std::cout << "ВНИМАНИЕ: ВЫХОД ЗА ПРЕДЕЛЫ\n";
        return;
    }

    List* p = new List(data);
    p->Next = current->Next;
    current->Next = p;
}

void ListDELETEHEAD(List*& head) {
    if (head == nullptr) return;
    List* temp = head;
    head = head->Next;
    delete temp;
}

void ListDELETETAIL(List*& head) {
    if (head == nullptr) return;
    if (head->Next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    List* current = head;
    while (current->Next->Next != nullptr) {
        current = current->Next;
    }
    delete current->Next;
    current->Next = nullptr;
}

void ListDELETEAT(List*& head, int index) {
    if (index <= 0 || head == nullptr) return;
    if (index == 1) {
        ListDELETEHEAD(head);
        return;
    }

    List* current = head;
    for (int i = 0; i < index - 2; ++i) {
        if (current->Next == nullptr) return;
        current = current->Next;
    }

    if (current->Next == nullptr) return;

    List* toDelete = current->Next;
    current->Next = toDelete->Next;
    delete toDelete;
}

void ListDELETETHAFTER(List*& head, int index) {
    if (index < 0 || head == nullptr) return;

    List* current = head;
    for (int i = 0; i < index; ++i) {
        if (current == nullptr) return;
        current = current->Next;
    }

    if (current == nullptr || current->Next == nullptr) return;

    List* toDelete = current->Next;
    current->Next = toDelete->Next;
    delete toDelete;
}

void ListPRINTITER(List* head) {
    List* current = head;
    while (current != nullptr) {
        std::cout << current->Data << " ";
        current = current->Next;
    }
    std::cout << std::endl;
}

void ListPRINTREC(List* head) {
    if (head == nullptr) {
        std::cout << std::endl;
        return;
    }
    std::cout << head->Data << " ";
    ListPRINTREC(head->Next);
}

void ListDELETEELEMENT(List*& head, const std::string& data) {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    if (head->Data == data) {
        ListDELETEHEAD(head);
        return;
    }

    List* prev = head;
    List* current = head->Next;

    while (current != nullptr && current->Data != data) {
        prev = current;
        current = current->Next;
    }

    if (current == nullptr) {
        std::cout << "Значение не найдено" << std::endl;
        return;
    }

    prev->Next = current->Next;
    delete current;
}

void ListFINDELEMENT(List* head, const std::string& data) {
    if (head == nullptr) {
        std::cout << "Список пуст" << std::endl;
        return;
    }

    int index = 0;
    List* current = head;
    while (current != nullptr) {
        if (current->Data == data) {
            std::cout << index << std::endl;
            return;
        }
        current = current->Next;
        ++index;
    }

    std::cout << "Значение не найдено" << std::endl;
}