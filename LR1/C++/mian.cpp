#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Stack.h"
#include "SinglyList.h"
#include "Queue.h"
#include "FullBinaryTree.h"
#include "Doublelist.h"
#include "Array.h"

using namespace std;

MyArray* currentArray = nullptr;
List* currentList = nullptr;
DoublyLinkedList* currentDList = nullptr;
DynamicStack* currentStack = nullptr;
DynamicQueue* currentQueue = nullptr;
T* currentTree = nullptr;

// Функции для работы с файлами
void saveArrayToFile(MyArray* arr, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "ARRAY_SIZE:" << arr->ALEIGHT() << endl;
        for (int i = 0; i < arr->ALEIGHT(); i++) {
            file << arr->AGET(i) << endl;
        }
        file.close();
        cout << "Массив сохранен в " << filename << endl;
    } else {
        cout << "Ошибка сохранения массива" << endl;
    }
}

void loadArrayFromFile(MyArray*& arr, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        if (arr) delete arr;
        arr = new MyArray();
        string line;
        getline(file, line); // Пропускаем строку с размером
        while (getline(file, line)) {
            if (!line.empty()) {
                arr->APUSH(line);
            }
        }
        file.close();
        cout << "Массив загружен из " << filename << endl;
    } else {
        cout << "Ошибка загрузки массива" << endl;
    }
}

void saveListToFile(List* list, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        // Подсчитываем размер списка
        int size = 0;
        List* current = list;
        while (current != nullptr) {
            size++;
            current = current->Next;
        }
        
        file << "LIST_SIZE:" << size << endl;
        current = list;
        while (current != nullptr) {
            file << current->Data << endl;
            current = current->Next;
        }
        file.close();
        cout << "Список сохранен в " << filename << endl;
    } else {
        cout << "Ошибка сохранения списка" << endl;
    }
}

void loadListFromFile(List*& list, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        // Очищаем существующий список
        while (list != nullptr) {
            ListDELETEHEAD(list);
        }
        
        string line;
        getline(file, line); // Пропускаем строку с размером
        while (getline(file, line)) {
            if (!line.empty()) {
                ListPUSHHEAD(list, line);
            }
        }
        file.close();
        cout << "Список загружен из " << filename << endl;
    } else {
        cout << "Ошибка загрузки списка" << endl;
    }
}

void saveStackToFile(DynamicStack* stack, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "STACK_SIZE:" << stack->size << endl;
        DynamicStack temp;
        initStack(&temp, stack->capacity);
        
        // Сохраняем элементы во временный стек
        while (!isEmpty(stack)) {
            string value = top(stack);
            file << value << endl;
            pop(stack);
            push(&temp, value);
        }
        
        // Восстанавливаем исходный стек
        while (!isEmpty(&temp)) {
            string value = top(&temp);
            pop(&temp);
            push(stack, value);
        }
        
        freeStack(&temp);
        file.close();
        cout << "Стек сохранен в " << filename << endl;
    } else {
        cout << "Ошибка сохранения стека" << endl;
    }
}

void loadStackFromFile(DynamicStack*& stack, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        if (stack) freeStack(stack);
        stack = new DynamicStack;
        initStack(stack, 10);
        
        string line;
        getline(file, line); // Пропускаем строку с размером
        while (getline(file, line)) {
            if (!line.empty()) {
                push(stack, line);
            }
        }
        file.close();
        cout << "Стек загружен из " << filename << endl;
    } else {
        cout << "Ошибка загрузки стека" << endl;
    }
}

void saveQueueToFile(DynamicQueue* queue, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "QUEUE_SIZE:" << queue->size << endl;
        
        // Сохраняем элементы в правильном порядке
        int count = queue->size;
        int frontIdx = queue->frontIndex;
        for (int i = 0; i < count; i++) {
            int index = (frontIdx + i) % queue->capacity;
            file << queue->data[index] << endl;
        }
        
        file.close();
        cout << "Очередь сохранена в " << filename << endl;
    } else {
        cout << "Ошибка сохранения очереди" << endl;
    }
}

void loadQueueFromFile(DynamicQueue*& queue, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        if (queue) freeQueue(queue);
        queue = new DynamicQueue;
        initQueue(queue, 10);
        
        string line;
        getline(file, line); // Пропускаем строку с размером
        while (getline(file, line)) {
            if (!line.empty()) {
                push(queue, line);
            }
        }
        file.close();
        cout << "Очередь загружена из " << filename << endl;
    } else {
        cout << "Ошибка загрузки очереди" << endl;
    }
}

int getDoublyLinkedListSize(const DoublyLinkedList& list) {
    int count = 0;
    DLNode* current = list.head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Сохранение списка в файл
void saveDoubleListToFile(DoublyLinkedList& list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка сохранения двусвязного списка" << endl;
        return;
    }

    int size = getDoublyLinkedListSize(list);
    file << "DLIST_SIZE:" << size << endl;

    DLNode* current = list.head;
    while (current != nullptr) {
        file << current->data << endl;
        current = current->next;
    }

    file.close();
    cout << "Двусвязный список сохранен в " << filename << endl;
}

// Загрузка списка из файла
void loadDoubleListFromFile(DoublyLinkedList& list, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка загрузки двусвязного списка" << endl;
        return;
    }

    list.clear();

    string line;
    getline(file, line);

    // Читаем остальные строки и добавляем в конец
    while (getline(file, line)) {
        if (!line.empty()) {
            list.ListPUSHTAIL(line);
        }
    }

    file.close();
    cout << "Двусвязный список загружен из " << filename << endl;
}

void printHelp() {
    cout << "\n=== СПРАВКА ПО КОМАНДАМ ===" << endl;
    cout << "МАССИВ (M):" << endl;
    cout << "  MCREATE - создать массив" << endl;
    cout << "  MPUSH value - добавить элемент в конец" << endl;
    cout << "  MGET index - получить элемент по индексу" << endl;
    cout << "  MDEL index - удалить элемент по индексу" << endl;
    cout << "  MCHANGE value index - замена элемента по инедксу" << endl;
    cout << "  MINSERT value index - вставка элемента по индексу" << endl;
    cout << "  MSIZE - получить размер" << endl;
    cout << "  MPRINT - вывести массив" << endl;
    cout << "  MSAVE filename - сохранить в файл" << endl;
    cout << "  MLOAD filename - загрузить из файла" << endl;
    
    cout << "\nОДНОСВЯЗНЫЙ СПИСОК (F):" << endl;
    cout << "  FCREATE - создать список" << endl;
    cout << "  FPUSHHEAD value - добавить элемент в голову" << endl;
    cout << "  FPUSHTAIL value - добавить элемент в хвост" << endl;
    cout << "  FPUSHAT value index - добавить элемент перед индексом" << endl;
    cout << "  FPUSHAFTER value index - добавить элемент после индекса" << endl;
    cout << "  FDELHEAD - удалить элемент в голове" << endl;
    cout << "  FDELTAIL - удалить элемент в хвосте" << endl;
    cout << "  FDELAT index - удалить элемент перед индексом" << endl;
    cout << "  FDELAFTER index - удалить элемент после индекса" << endl;
    cout << "  FGET value - найти элемент" << endl;
    cout << "  FPRINT - вывести список" << endl;
    cout << "  FSAVE filename - сохранить в файл" << endl;
    cout << "  FLOAD filename - загрузить из файла" << endl;
    
    cout << "\nДВУСВЯЗНЫЙ СПИСОК (L):" << endl;
    cout << "  LCREATE - создать список" << endl;
    cout << "  LPUSHHEAD value - добавить элемент в голову" << endl;
    cout << "  LPUSHTAIL value - добавить элемент в хвост" << endl;
    cout << "  LPUSHAT value index - добавить элемент перед индексом" << endl;
    cout << "  LPUSHAFTER value index - добавить элемент после индекса" << endl;
    cout << "  LDELHEAD - удалить элемент в голове" << endl;
    cout << "  LDELTAIL - удалить элемент в хвосте" << endl;
    cout << "  LDELAT value index - удалить элемент перед индексом" << endl;
    cout << "  LDELAFTER value index - удалить элемент после индекса" << endl;
    cout << "  LGET value - найти элемент" << endl;
    cout << "  LPRINT - вывести список" << endl;
    cout << "  LSAVE filename - сохранить в файл" << endl;
    cout << "  LLOAD filename - загрузить из файла" << endl;
    
    cout << "\nСТЕК (S):" << endl;
    cout << "  SCREATE - создать стек" << endl;
    cout << "  SPUSH value - добавить элемент" << endl;
    cout << "  SPOP - удалить элемент" << endl;
    cout << "  STOP - посмотреть верхний элемент" << endl;
    cout << "  SPRINT - вывести стек" << endl;
    cout << "  SSAVE filename - сохранить в файл" << endl;
    cout << "  SLOAD filename - загрузить из файла" << endl;
    
    cout << "\nОЧЕРЕДЬ (Q):" << endl;
    cout << "  QCREATE - создать очередь" << endl;
    cout << "  QPUSH value - добавить элемент" << endl;
    cout << "  QPOP - удалить элемент" << endl;
    cout << "  QFRONT - посмотреть первый элемент" << endl;
    cout << "  QPRINT - вывести очередь" << endl;
    cout << "  QSAVE filename - сохранить в файл" << endl;
    cout << "  QLOAD filename - загрузить из файла" << endl;
    
    cout << "\nДЕРЕВО (T):" << endl;
    cout << "  TCREATE - создать дерево" << endl;
    cout << "  TINSERT value - добавить элемент" << endl;
    cout << "  TFIND value - поиск элемента" << endl;
    cout << "  TGET - получить корень" << endl;
    cout << "  TISFULL - проверка на full" << endl;
    cout << "  TPRINT - вывести дерево" << endl;
    
    cout << "\nОБЩИЕ КОМАНДЫ:" << endl;
    cout << "  HELP - показать справку" << endl;
    cout << "  CLEAR - очистить все структуры" << endl;
    cout << "  EXIT - выход из программы" << endl;
    cout << "=================================" << endl;
}

void executeCommand(const string& command) {
    stringstream ss(command);
    string cmd;
    ss >> cmd;
//массив
    if (cmd == "MCREATE") {
        if (currentArray) delete currentArray;
        currentArray = new MyArray();
        cout << "Массив создан" << endl;
    }
    else if (cmd == "MPUSH") {
        if (!currentArray) {
            cout << "Ошибка: Массив не создан" << endl;
            return;
        }
        string value;
        ss >> value;
        currentArray->APUSH(value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "MGET") {
        if (!currentArray) {
            cout << "Ошибка: Массив не создан" << endl;
            return;
        }
        int index;
        ss >> index;
        if (index >= 0 && index < currentArray->ALEIGHT()) {
            cout << "Элемент: " << currentArray->AGET(index) << endl;
        } else {
            cout << "Неверный индекс" << endl;
        }
    }
    else if (cmd == "MDEL") {
        if (!currentArray) {
            cout << "Ошибка: Массив не создан" << endl;
            return;
        }
        int index;
        ss >> index;
        if (index >= 0 && index < currentArray->ALEIGHT()) {
            currentArray->ADEL(index);
            cout << "Элемент удален" << endl;
        } else {
            cout << "Неверный индекс" << endl;
        }
    }
    else if (cmd == "MINSERT") {
    if (!currentArray) {
        cout << "Ошибка: Массив не создан" << endl;
        return;
    }
    int index;
    string value;
    ss >> value >> index;
        
    currentArray->AINSERT(value, index);
    }
    else if (cmd == "MCHANGE") {
        if (!currentArray) {
            cout << "Ошибка: Массив не создан" << endl;
            return;
        }
        int index;
        string value;
        ss >> value >> index;
        
        currentArray->ACHANGE(value, index);
    }
    else if (cmd == "MSIZE") {
        if (!currentArray) {
            cout << "Ошибка: Массив не создан" << endl;
            return;
        }
        cout << "Размер массива: " << currentArray->ALEIGHT() << endl;
    }
    else if (cmd == "MPRINT") {
        if (!currentArray) {
            cout << "Ошибка: Массив не создан" << endl;
            return;
        }
        currentArray->AREAD();
    }
    else if (cmd == "MSAVE") {
        if (!currentArray) {
            cout << "Ошибка: Массив не создан" << endl;
            return;
        }
        string filename;
        ss >> filename;
        saveArrayToFile(currentArray, filename);
    }
    else if (cmd == "MLOAD") {
        string filename;
        ss >> filename;
        loadArrayFromFile(currentArray, filename);
    }
//односвязный список
    else if (cmd == "FCREATE") {
        if (currentList) {
            while (currentList != nullptr) {
                ListDELETEHEAD(currentList);
            }
        }
        currentList = nullptr;
        cout << "Односвязный список создан" << endl;
    }
    else if (cmd == "FPUSHHEAD") {
        if (!currentList) {
            currentList = nullptr;
        }
        string value;
        ss >> value;
        ListPUSHHEAD(currentList, value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "FPUSHTAIL") {
        if (!currentList) {
            currentList = nullptr;
        }
        string value;
        ss >> value;
        ListPUSHTAIL(currentList, value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "FPUSHAT") {
        if (!currentList) {
            currentList = nullptr;
        }
        string value;
        int index;
        ss >> value >> index;
        ListPUSHAT(currentList, value, index);
        cout << "Добавлено: " << value << " перед индексом " << index << endl;
    }
    else if (cmd == "FPUSHAFTER") {
        if (!currentList) {
            currentList = nullptr;
        }
        string value;
        int index;
        ss >> value >> index;
        ListPUSHAFTER(currentList, value, index);
        cout << "Добавлено: " << value << " после индекса " << index << endl;
    }
    else if (cmd == "FGET") {
        if (!currentList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string value;
        ss >> value;
        cout << "Поиск: ";
        ListFINDELEMENT(currentList, value);
    }
    else if (cmd == "FDELHEAD") {
        if (!currentList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        ListDELETEHEAD(currentList);
    }
    else if (cmd == "FDELTAIL") {
        if (!currentList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        ListDELETETAIL(currentList);
    }
    else if (cmd == "FDELAT") {
        if (!currentList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        int index;
        ss >> index;
        ListDELETEAT(currentList, index);
        cout << "Удаление до индекса " << index << endl;
    }
    else if (cmd == "FDELAFTER") {
        if (!currentList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        int index;
        ss >> index;
        ListDELETETHAFTER(currentList, index);
        cout << "Удалено после индекса " << index << endl;
    }
    else if (cmd == "FPRINT") {
        if (!currentList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        ListPRINTITER(currentList);
    }
    else if (cmd == "FSAVE") {
        if (!currentList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string filename;
        ss >> filename;
        saveListToFile(currentList, filename);
    }
    else if (cmd == "FLOAD") {
        string filename;
        ss >> filename;
        loadListFromFile(currentList, filename);
    }
//двусвязный список
    else if (cmd == "LCREATE") {
        if (currentDList) delete currentDList;
        currentDList = new DoublyLinkedList();
        cout << "Двусвязный список создан" << endl;
    }
    else if (cmd == "LPUSHHEAD") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string value;
        ss >> value;
        currentDList->ListPUSHHEAD(value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "LPUSHTAIL") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string value;
        ss >> value;
        currentDList->ListPUSHTAIL(value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "LPUSHAT") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string value;
        int index;
        ss >> value >> index;
        currentDList->ListPUSHAT(value, index);
        cout << "Добавлено: " << value << " по индексу " << index << endl;
    }
    else if (cmd == "LPUSHAFTER") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string value;
        int index;
        ss >> value >> index;
        currentDList->ListPUSHAFTER(value, index);
        cout << "Добавлено: " << value << " после индекса " << index << endl;
    }
    else if (cmd == "LGET") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string value;
        ss >> value;
        cout << "Поиск: ";
        currentDList->ListFINDELEMENT(value);
    }
    else if (cmd == "LDELHEAD") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        currentDList->ListDELETEHEAD();
    }
    else if (cmd == "LDELTAIL") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        currentDList->ListDELETETAIL();
    }
    else if (cmd == "LDELAT") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        int index;
        ss >> index;
        currentDList->ListDELETEAT(index);
    }
    else if (cmd == "LDELAFTER") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        int index;
        ss >> index;
        currentDList->ListDELETETHAFTER(index);
    }
    else if (cmd == "LPRINT") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        currentDList->ListPRINTITER();
    }
    else if (cmd == "LSAVE") {
        if (!currentDList) {
            cout << "Ошибка: Список не создан" << endl;
            return;
        }
        string filename;
        ss >> filename;
        saveDoubleListToFile(*currentDList, filename);
    }
    else if (cmd == "LLOAD") {
        string filename;
        ss >> filename;
        loadDoubleListFromFile(*currentDList, filename);
    }
// стек
    else if (cmd == "SCREATE") {
        if (currentStack) freeStack(currentStack);
        currentStack = new DynamicStack;
        initStack(currentStack, 2);
        cout << "Стек создан" << endl;
    }
    else if (cmd == "SPUSH") {
        if (!currentStack) {
            cout << "Ошибка: Стек не создан" << endl;
            return;
        }
        string value;
        ss >> value;
        push(currentStack, value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "SPOP") {
        if (!currentStack || isEmpty(currentStack)) {
            cout << "Ошибка: Стек пуст" << endl;
            return;
        }
        string value = top(currentStack);
        pop(currentStack);
        cout << "Извлечено: " << value << endl;
    }
    else if (cmd == "STOP") {
        if (!currentStack || isEmpty(currentStack)) {
            cout << "Ошибка: Стек пуст" << endl;
            return;
        }
        cout << "Верхний элемент: " << top(currentStack) << endl;
    }
    else if (cmd == "SPRINT") {
        if (!currentStack) {
            cout << "Ошибка: Стек не создан" << endl;
            return;
        }
        if (isEmpty(currentStack)) {
            cout << "Стек пуст" << endl;
            return;
        }
        
        string result = "";
        DynamicStack temp;
        initStack(&temp, currentStack->capacity);
        
        while (!isEmpty(currentStack)) {
            string val = top(currentStack);
            result = val + (result.empty() ? "" : " ") + result;
            pop(currentStack);
            push(&temp, val);
        }

        cout << "Стек: " << result << endl;
    }
    else if (cmd == "SSAVE") {
        if (!currentStack) {
            cout << "Ошибка: Стек не создан" << endl;
            return;
        }
        string filename;
        ss >> filename;
        saveStackToFile(currentStack, filename);
    }
    else if (cmd == "SLOAD") {
        string filename;
        ss >> filename;
        loadStackFromFile(currentStack, filename);
    }
//очередь
    else if (cmd == "QCREATE") {
        if (currentQueue) freeQueue(currentQueue);
        currentQueue = new DynamicQueue;
        initQueue(currentQueue, 2);
        cout << "Очередь создана" << endl;
    }
    else if (cmd == "QPUSH") {
        if (!currentQueue) {
            cout << "Ошибка: Очередь не создана" << endl;
            return;
        }
        string value;
        ss >> value;
        push(currentQueue, value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "QPOP") {
        if (!currentQueue || isEmpty(currentQueue)) {
            cout << "Ошибка: Очередь пуста" << endl;
            return;
        }
        string value = front(currentQueue);
        pop(currentQueue);
        cout << "Извлечено: " << value << endl;
    }
    else if (cmd == "QFRONT") {
        if (!currentQueue || isEmpty(currentQueue)) {
            cout << "Ошибка: Очередь пуста" << endl;
            return;
        }
        cout << "Первый элемент: " << front(currentQueue) << endl;
    }
    else if (cmd == "QPRINT") {
        if (!currentQueue) {
            cout << "Ошибка: Очередь не создана" << endl;
            return;
        }
        if (isEmpty(currentQueue)) {
            cout << "Очередь пуста" << endl;
            return;
        }
        
        string result = "";
        DynamicQueue temp;
        initQueue(&temp, currentQueue->capacity);
        
        while (!isEmpty(currentQueue)) {
            string val = front(currentQueue);
            result += val + " ";
            pop(currentQueue);
            push(&temp, val);
        }
        
        while (!isEmpty(&temp)) {
            string val = front(&temp);
            pop(&temp);
            push(currentQueue, val);
        }
        
        freeQueue(&temp);
        cout << "Очередь: " << result << endl;
    }
    else if (cmd == "QSAVE") {
        if (!currentQueue) {
            cout << "Ошибка: Очередь не создана" << endl;
            return;
        }
        string filename;
        ss >> filename;
        saveQueueToFile(currentQueue, filename);
    }
    else if (cmd == "QLOAD") {
        string filename;
        ss >> filename;
        loadQueueFromFile(currentQueue, filename);
    }
//дерево
    else if (cmd == "TCREATE") {
        if (currentTree) freeTree(currentTree->root);
        currentTree = new T;
        cout << "Дерево создано" << endl;
    }
    else if (cmd == "TINSERT") {
        if (!currentTree) {
            cout << "Дерево не создано";
            return;
            }
        int value;
        ss >> value;
        // Упрощенная вставка - создаем новое дерево
        insert(currentTree, value);
        cout << "Добавлено: " << value << endl;
    }
    else if (cmd == "TGET") {
        if (!currentTree) {
            cout << "Ошибка: Дерево не создано" << endl;
            return;
        }
        cout << "Корень: " << currentTree->root->data << endl;
    }
    else if (cmd == "TISFULL") {
        if (!currentTree) {
            cout << "Ошибка: Дерево не создано" << endl;
            return;
        }
        cout << isFull(currentTree) << endl;
    }
    else if (cmd == "TFIND") {
        if (!currentTree) {
            cout << "Ошибка: Дерево не создано" << endl;
            return;
        }
        int value;
        ss >> value;
        TreeNode* result = find(currentTree, value);
        if (result) {
            cout << "Значение " << value << " найдено в дереве." << endl;
        } else {
            cout << "Значение " << value << " не найдено." << endl;
        }
    }
    else if (cmd == "TPRINT") {
        if (!currentTree) {
            cout << "Ошибка: Дерево не создано" << endl;
            return;
        }
        printPreOrder(currentTree->root);
        cout << endl;
    }

    else if (cmd == "HELP") {
        printHelp();
    }
    else if (cmd == "CLEAR") {
        if (currentArray) { delete currentArray; currentArray = nullptr; }
        if (currentList) { while (currentList != nullptr) ListDELETEHEAD(currentList); currentList = nullptr; }
        if (currentDList) { delete currentDList; currentDList = nullptr; }
        if (currentStack) { freeStack(currentStack); delete currentStack; currentStack = nullptr; }
        if (currentQueue) { freeQueue(currentQueue); delete currentQueue; currentQueue = nullptr; }
        if (currentTree) { freeTree(currentTree->root); currentTree = nullptr; }
        cout << "Все структуры данных очищены" << endl;
    }
    else if (cmd == "EXIT") {
        if (currentArray) delete currentArray;
        if (currentList) while (currentList != nullptr) ListDELETEHEAD(currentList);
        if (currentDList) delete currentDList;
        if (currentStack) { freeStack(currentStack); delete currentStack; }
        if (currentQueue) { freeQueue(currentQueue); delete currentQueue; }
        if (currentTree) freeTree(currentTree->root);
        cout << "Выход из программы..." << endl;
        exit(0);
    }
    else {
        cout << "Неизвестная команда: " << cmd << ". Введите HELP для справки." << endl;
    }
}

int main() {
    string command;
    cout << "=== ИНТЕРФЕЙС РАБОТЫ СО СТРУКТУРАМИ ДАННЫХ ===" << endl;
    cout << "Введите команды (HELP для справки, EXIT для выхода):" << endl;
    while (true) {
        cout << "> ";
        getline(cin, command);
        if (command.empty()) continue;
        executeCommand(command);
    }
    return 0;
}
