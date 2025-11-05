#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <string>
#include <iostream>

struct List {
    std::string Data;
    List* Next;
    List(const std::string& data);
};

// Добавление в голову
void ListPUSHHEAD(List*& head, const std::string& data);

// Добавление в хвост
void ListPUSHTAIL(List*& head, const std::string& data);

// Добавление ПЕРЕД указанным индексом (в позицию `index`)
void ListPUSHAT(List*& head, const std::string& data, int index);

// Добавление ПОСЛЕ указанного индекса
void ListPUSHAFTER(List*& head, const std::string& data, int index);

// Удаление головы
void ListDELETEHEAD(List*& head);

// Удаление хвоста
void ListDELETETAIL(List*& head);

// Удаление элемента ПЕРЕД ИНДЕКСОМ (удаляет элемент перед позицией `index`)
void ListDELETEAT(List*& head, int index);

// Удаление элемента ПОСЛЕ указанного индекса
void ListDELETETHAFTER(List*& head, int index);

// Печать списка (итеративно)
void ListPRINTITER(List* head);

// Печать списка (рекурсивно)
void ListPRINTREC(List* head);

// Удаление первого вхождения элемента по значению
void ListDELETEELEMENT(List*& head, const std::string& data);

// Поиск элемента по значению (выводит индекс первого вхождения или сообщение)
void ListFINDELEMENT(List* head, const std::string& data);

#endif // SINGLY_LINKED_LIST_H