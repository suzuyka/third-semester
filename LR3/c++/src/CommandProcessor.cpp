#include "../include/Array.h"
#include "../include/SinglyLinkedList.h"
#include "../include/CommandProcessor.h"
#include "../include/DoublyLinkedList.h"
#include "../include/Stack.h"
#include "../include/Queue.h"
#include "../include/RedBlackTree.h"
#include "../include/HashTable.h"

#include <sstream>
#include <iostream>
#include <fstream>

// ----- Бинарные версии -----
void saveArrayToBinaryFile(const std::string& filename, Array& arr) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) {
        std::cerr << "Ошибка открытия файла для бинарной записи: " << filename << std::endl;
        return;
    }
    arr.serializeBinary(fout);
}

void loadArrayFromBinaryFile(const std::string& filename, Array& arr) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        std::cerr << "Ошибка открытия файла для бинарного чтения: " << filename << std::endl;
        return;
    }
    arr.deserializeBinary(fin);
}

void saveListToBinaryFile(const std::string& filename, SinglyLinkedList& list) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) return;
    list.serializeBinary(fout);
}

void loadListFromBinaryFile(const std::string& filename, SinglyLinkedList& list) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        // Явно создаем пустой список если файл не открылся
        list = SinglyLinkedList();
        return;
    }
    list.deserializeBinary(fin);
}

void saveDoublyListToBinaryFile(const std::string& filename, DoublyLinkedList& list) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) return;
    list.serializeBinary(fout);
}

void loadDoublyListFromBinaryFile(const std::string& filename, DoublyLinkedList& list) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        list = DoublyLinkedList(); // Инициализируем пустым списком
        return;
    }
    list.deserializeBinary(fin);
}

void saveStackToBinaryFile(const std::string& filename, Stack& stack) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) return;
    stack.serializeBinary(fout);
}

void loadStackFromBinaryFile(const std::string& filename, Stack& stack) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        stack = Stack(); // Инициализируем пустым стеком
        return;
    }
    stack.deserializeBinary(fin);
}

void saveQueueToBinaryFile(const std::string& filename, Queue& queue) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) return;
    queue.serializeBinary(fout);
}

void loadQueueFromBinaryFile(const std::string& filename, Queue& queue) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        queue = Queue(); // Инициализируем пустой очередью
        return;
    }
    queue.deserializeBinary(fin);
}

void saveTreeToBinaryFile(const std::string& filename, RedBlackTree& tree) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) return;
    tree.serializeBinary(fout);
}

void loadTreeFromBinaryFile(const std::string& filename, RedBlackTree& tree) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        tree = RedBlackTree(); // Инициализируем пустым деревом
        return;
    }
    tree.deserializeBinary(fin);
}

void saveHashToBinaryFile(const std::string& filename, HashTable& ht) {
    std::ofstream fout(filename, std::ios::binary);
    if (!fout) {
        std::cerr << "Ошибка открытия файла для бинарной записи: " << filename << std::endl;
        return;
    }
    ht.serializeBinary(fout);
}

void loadHashFromBinaryFile(const std::string& filename, HashTable& ht) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        std::cerr << "Ошибка открытия файла для бинарного чтения: " << filename << std::endl;
        return;
    }
    ht.deserializeBinary(fin);
}

// ----- Вспомогательные функции для Array -----
void loadArrayFromFile(const std::string& filename, Array& arr) { // загрузка массива из файла
    std::ifstream fin(filename);
    if (!fin.is_open()) return;
    int value;
    while (fin >> value) {
        arr.push(value);
    }
    fin.close();
}

void saveArrayToFile(const std::string& filename, Array& arr) { // сохранение массива в файл
    std::ofstream fout(filename);
    if (!fout.is_open()) return;
    for (size_t i = 0; i < arr.size(); i++) {
        fout << arr.get(i) << " ";
    }
    fout.close();
}

// ----- Вспомогательные функции для Tree -----
void loadTreeFromFile(const std::string& filename, RedBlackTree& tree) { // загрузка дерева из файла
    std::ifstream fin(filename);
    if (!fin.is_open()) return;
    int value;
    while (fin >> value) {
        tree.insert(value);
    }
    fin.close();
}

void saveTreeToFile(const std::string& filename, RedBlackTree& tree) { // сохранение дерева в файл
    std::ofstream fout(filename);
    if (!fout.is_open()) return;

    std::vector<int> keys = tree.toVector();
    for (size_t i = 0; i < keys.size(); ++i) {
        fout << keys[i];
        if (i + 1 < keys.size()) fout << " ";
    }
    fout << std::endl;
    fout.close();
}


// ----- Вспомогательные функции для SinglyLinkedList -----
void loadListFromFile(const std::string& filename, SinglyLinkedList& list) { // загрузка односвязного списка
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    int value;
    while (fin >> value) {
        list.pushBack(value); // читаем и добавляем в хвост
    }
    fin.close();
}

void saveListToFile(const std::string& filename, SinglyLinkedList& list) { // сохранение односвязного списка
    std::ofstream fout(filename);
    if (!fout.is_open()) return;

    for (int val : list.toVector()) {
        fout << val << " ";
    }
    fout.close();
}

// ----- Вспомогательные функции для DoublyLinkedList -----
void loadDoublyListFromFile(const std::string& filename, DoublyLinkedList& list) { // загрузка двусвязного списка
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    int value;
    while (fin >> value) {
        list.pushBack(value);
    }
    fin.close();
}

void saveDoublyListToFile(const std::string& filename, DoublyLinkedList& list) { // сохранение двусвязного списка
    std::ofstream fout(filename);
    if (!fout.is_open()) return;

    for (int val : list.toVector()) {
        fout << val << " ";
    }
    fout.close();
}

// ----- Вспомогательные функции для Stack -----
void loadStackFromFile(const std::string& filename, Stack& stack) { // загрузка стека из файла
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    int value;
    while (fin >> value) {
        stack.push(value);
    }
    fin.close();
}

void saveStackToFile(const std::string& filename, Stack& stack) { // сохранение стека в файл
    std::ofstream fout(filename);
    if (!fout.is_open()) return;

    for (int val : stack.toVector()) {
        fout << val << " ";
    }
    fout.close();
}

// ----- Вспомогательные функции для Queue -----
void loadQueueFromFile(const std::string& filename, Queue& queue) { // загрузка очереди из файла
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    int value;
    while (fin >> value) {
        queue.push(value);
    }
    fin.close();
}

void saveQueueToFile(const std::string& filename, Queue& queue) { // сохранение очереди в файл
    std::ofstream fout(filename);
    if (!fout.is_open()) return;

    for (int val : queue.toVector()) {
        fout << val << " ";
    }
    fout.close();
}

// ----- Вспомогательные функции для Hash -----
static inline std::string ltrim(const std::string &s) { // удаляет пробелы в начале строки
    size_t i = 0;
    while (i < s.size() && isspace((unsigned char)s[i])) ++i;
    return s.substr(i);
}

void loadHashFromFile(const std::string& filename, HashTable& ht) { // загрузка хэш-таблицы из файла
    std::ifstream in(filename);
    if (!in.is_open()) return;

    std::string token, typeStr;
    int size = 11; // значение по умолчанию

    // читаем тип и размер
    if (in >> token >> typeStr && token == "TYPE") {
        HashType type = HashType::DOUBLE_HASHING;
        if (typeStr == "CUCKOO") type = HashType::CUCKOO_HASHING;
        else if (typeStr == "FOLDING") type = HashType::FOLDING_HASHING;

        // читаем следующую строчку с SIZE
        in >> token >> size;
        ht = HashTable(size, type);
    } else {
        // если файл старый
        ht = HashTable(size, HashType::DOUBLE_HASHING);
    }

    int key, value;
    while (in >> key >> value)
        ht.insert(key, value);
}

void saveHashToFile(const std::string& filename, const HashTable& ht) { // сохранение хэш-таблицы в файл
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи.\n";
        return;
    }

    // сохраняем тип хеширования
    out << "TYPE ";
    switch (ht.getType()) {
        case HashType::DOUBLE_HASHING:  out << "DOUBLE\n"; break;
        case HashType::CUCKOO_HASHING:  out << "CUCKOO\n"; break;
        case HashType::FOLDING_HASHING: out << "FOLDING\n"; break;
    }

    // сохраняем размер таблицы
    out << "SIZE " << ht.getSize() << "\n";

    // сохраняем пары ключ–значение
    for (auto& p : ht.toVector())
        out << p.first << " " << p.second << "\n";
}

// Глобальная хеш-таблица для приложения
static HashTable hashTable(11, HashType::DOUBLE_HASHING);

// ----- Обработка команд -----
void CommandProcessor::execute(const std::string& query, const std::string& filename) {
    std::istringstream iss(query);
    std::string command, name;
    iss >> command >> name;

    // ---- TREE ----
    if (command == "TINSERT") { // вставка в дерево
        int value; iss >> value;
        RedBlackTree tree;
        loadTreeFromFile(filename, tree);
        tree.insert(value);
        saveTreeToFile(filename, tree);
        std::cout << "-> вставлен " << value << std::endl;
    }
    else if (command == "TDEL") { // удаление из дерева
        int value; iss >> value;
        RedBlackTree tree;
        loadTreeFromFile(filename, tree);

        // проверяем существование элемента перед удалением
        if (tree.contains(value)) {
            tree.remove(value);
            saveTreeToFile(filename, tree);
            std::cout << "-> удалён " << value << std::endl;
        } else {
            std::cout << "Ошибка: элемент " << value << " не найден" << std::endl;
        }
    }
    else if (command == "TGET") { // поиск в дереве
        int value; iss >> value;
        RedBlackTree tree;
        loadTreeFromFile(filename, tree);
        std::cout << "-> " << (tree.contains(value) ? "TRUE" : "FALSE") << std::endl;
    }

    else if (command == "TVALIDATE") { // проверка дерева на свойства
        RedBlackTree tree;
        loadTreeFromFile(filename, tree);
        bool ok = tree.validate();
        std::cout << "-> " << (ok ? "VALID" : "INVALID") << std::endl;
    }

    else if (command == "PRINT") { // печать дерева
        RedBlackTree tree;
        loadTreeFromFile(filename, tree);
        std::cout << "-> ";
        tree.print();
    }

    // ---- ARRAY ----
    else if (command == "MPUSH") { // добавление в массив
        int value; iss >> value;
        Array arr;
        loadArrayFromFile(filename, arr);
        arr.push(value);
        saveArrayToFile(filename, arr);
        std::cout << "-> добавлен " << value << std::endl;
    }
    else if (command == "MDEL") { // удаление из массива
        int index; iss >> index;
        Array arr;
        loadArrayFromFile(filename, arr);

        // Проверяем валидность индекса перед удалением
        if (index >= 0 && index < (int)arr.size()) {
            arr.delAt(index);
            saveArrayToFile(filename, arr);
            std::cout << "-> удалён элемент по индексу " << index << std::endl;
        } else {
            std::cout << "Ошибка: индекс " << index << " вне диапазона" << std::endl;
        }
    }
    else if (command == "MGET") { // получение из массива
        int index; iss >> index;
        Array arr;
        loadArrayFromFile(filename, arr);
        std::cout << "-> " << arr.get(index) << std::endl;
    }
    else if (command == "PRINTM") { // печать массива
        Array arr;
        loadArrayFromFile(filename, arr);
        std::cout << "-> ";
        arr.print();
    }

    else if (command == "MINDEX") { // вставка по индексу
        int index, value; iss >> index >> value;
        Array arr;
        loadArrayFromFile(filename, arr);

        // проверяем валидность индекса перед вставкой
        if (index >= 0 && index <= (int)arr.size()) {
            arr.insertAt(index, value);
            saveArrayToFile(filename, arr);
            std::cout << "-> вставлен " << value << " по индексу " << index << std::endl;
        } else {
            std::cout << "Ошибка: индекс " << index << " вне диапазона" << std::endl;
        }
    }
    else if (command == "MSET") { // замена по индексу
        int index, value; iss >> index >> value;
        Array arr;
        loadArrayFromFile(filename, arr);
        arr.set(index, value);
        saveArrayToFile(filename, arr);
        std::cout << "-> заменён элемент по индексу " << index << " на " << value << std::endl;
    }


    // ---- SINGLY LINKED LIST ----
    else if (command == "FPUSH") { // добавление в односвязный список
        int value; iss >> value;
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        list.pushBack(value);
        saveListToFile(filename, list);
        std::cout << "-> добавлен " << value << std::endl;
    }
    else if (command == "FDEL") { // удаление из односвязного списка
        int value; iss >> value;
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        bool ok = list.delByValue(value);
        saveListToFile(filename, list);
        if (ok)
            std::cout << "-> удалён " << value << std::endl;
        else
            std::cout << "-> элемент " << value << " не найден" << std::endl;
    }
    else if (command == "FGET") { // получение из односвязного списка
        int index; iss >> index;
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        std::cout << "-> " << list.get(index) << std::endl;
    }
    else if (command == "PRINTF") { // печать односвязного списка
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        std::cout << "-> ";
        list.print();
    }

    else if (command == "FPUSHFRONT") { // добавление в начало односвязного списка
        int value; iss >> value;
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        list.pushFront(value);
        saveListToFile(filename, list);
        std::cout << "-> добавлен " << value << " в голову" << std::endl;
    }
    else if (command == "FINSERTBEFORE") { // вставка перед элементом
        int target, value; iss >> target >> value;
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        list.insertBefore(target, value);
        saveListToFile(filename, list);
        std::cout << "-> вставлен " << value << " перед " << target << std::endl;
    }
    else if (command == "FINSERTAFTER") { // вставка после элемента
        int target, value; iss >> target >> value;
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        list.insertAfter(target, value);
        saveListToFile(filename, list);
        std::cout << "-> вставлен " << value << " после " << target << std::endl;
    }

    else if (command == "FDELFRONT") { // удаление первого элемента
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        bool ok = list.delFront();
        saveListToFile(filename, list);
        if (ok) std::cout << "-> удалён первый элемент" << std::endl;
        else std::cout << "Ошибка: список пуст" << std::endl;
    }
    else if (command == "FDELBACK") { // удаление последнего элемента
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        bool ok = list.delBack();
        saveListToFile(filename, list);
        if (ok) std::cout << "-> удалён последний элемент" << std::endl;
        else std::cout << "Ошибка: список пуст" << std::endl;
    }


    else if (command == "FCONTAINS") { // проверка наличия элемента
        int value; iss >> value;
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        bool found = list.contains(value);
        std::cout << "-> " << (found ? "найден " : "не найден ") << value << std::endl;
    }

    // ---- DOUBLY LINKED LIST ----
    else if (command == "LPUSH") { // добавление в двусвязный список
        int value; iss >> value;
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        list.pushBack(value);
        saveDoublyListToFile(filename, list);
        std::cout << "-> добавлен " << value << std::endl;
    }
    else if (command == "LDEL") { // удаление из двусвязного списка
        int value; iss >> value;
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        bool ok = list.delByValue(value);
        saveDoublyListToFile(filename, list);
        if (ok)
            std::cout << "-> удалён " << value << std::endl;
        else
            std::cout << "-> элемент " << value << " не найден" << std::endl;
    }
    else if (command == "LGET") { // получение из двусвязного списка
        int index; iss >> index;
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        std::cout << "-> " << list.get(index) << std::endl;
    }
    else if (command == "PRINTL") { // печать двусвязного списка
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        std::cout << "-> ";
        list.print();
    }

    else if (command == "LPUSHFRONT") { // добавление в начало двусвязного списка
        int value; iss >> value;
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        list.pushFront(value);
        saveDoublyListToFile(filename, list);
        std::cout << "-> добавлен " << value << " в голову" << std::endl;
    }
    else if (command == "LINSERTBEFORE") { // вставка перед элементом
        int target, value; iss >> target >> value;
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        list.insertBefore(target, value);
        saveDoublyListToFile(filename, list);
        std::cout << "-> вставлен " << value << " перед " << target << std::endl;
    }
    else if (command == "LINSERTAFTER") { // вставка после элемента
        int target, value; iss >> target >> value;
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        list.insertAfter(target, value);
        saveDoublyListToFile(filename, list);
        std::cout << "-> вставлен " << value << " после " << target << std::endl;
    }

    else if (command == "LCONTAINS") { // проверка наличия элемента
        int value; iss >> value;
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        bool found = list.contains(value);
        std::cout << "-> " << (found ? "найден " : "не найден ") << value << std::endl;
    }

    else if (command == "LDELFRONT") { // удаление первого элемента
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        bool ok = list.delFront();
        saveDoublyListToFile(filename, list);
        if (ok) std::cout << "-> удалён первый элемент" << std::endl;
        else std::cout << "Ошибка: список пуст" << std::endl;
    }
    else if (command == "LDELBACK") { // удаление последнего элемента
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        bool ok = list.delBack();
        saveDoublyListToFile(filename, list);
        if (ok) std::cout << "-> удалён последний элемент" << std::endl;
        else std::cout << "Ошибка: список пуст" << std::endl;
    }

    // ---- STACK ----
    else if (command == "SPUSH") { // добавление в стек
        int value; iss >> value;
        Stack stack;
        loadStackFromFile(filename, stack);
        stack.push(value);
        saveStackToFile(filename, stack);
        std::cout << "-> добавлен " << value << std::endl;
    }
    else if (command == "SPOP") { // удаление из стека
        Stack stack;
        loadStackFromFile(filename, stack);
        if (!stack.empty()) {
            int value = stack.top();
            stack.pop();
            saveStackToFile(filename, stack);
            std::cout << "-> удалён верхний элемент " << value << std::endl;
        } else {
            std::cout << "Ошибка: стек пуст" << std::endl;
        }
    }
    else if (command == "PRINTS") { // печать стека
        Stack stack;
        loadStackFromFile(filename, stack);
        std::cout << "-> ";
        stack.print();
    }

    // ---- QUEUE ----
    else if (command == "QPUSH") { // добавление в очередь
        int value; iss >> value;
        Queue queue;
        loadQueueFromFile(filename, queue);
        queue.push(value);
        saveQueueToFile(filename, queue);
        std::cout << "-> добавлен " << value << std::endl;
    }
    else if (command == "QPOP") { // удаление из очереди
        Queue queue;
        loadQueueFromFile(filename, queue);
        if (!queue.empty()) {
            int value = queue.front();
            queue.pop();
            saveQueueToFile(filename, queue);
            std::cout << "-> удалён первый элемент " << value << std::endl;
        } else {
            std::cout << "Ошибка: очередь пуста" << std::endl;
        }
    }
    else if (command == "PRINTQ") { // печать очереди
        Queue queue;
        loadQueueFromFile(filename, queue);
        std::cout << "-> ";
        queue.print();
    }

    // ---- ХЕШ-ТАБЛИЦА ----
    else if (command == "SETDOUBLEHASH") { // выбор режима двойного хеширования
        hashTable = HashTable(11, HashType::DOUBLE_HASHING);
        saveHashToFile(filename, hashTable);
        std::cout << "Режим: Двойное хеширование.\n";
        return;
    }

    else if (command == "SETCUCKOOHASH") { // выбор режима кукушкиного хеширования
        hashTable = HashTable(11, HashType::CUCKOO_HASHING);
        saveHashToFile(filename, hashTable);
        std::cout << "Режим: Кукушкино хеширование.\n";
        return;
    }

    else if (command == "SETFOLDHASH") { // выбор режима хеширования свёрткой
        hashTable = HashTable(11, HashType::FOLDING_HASHING);
        std::cout << "Режим: Метод свёртки (Folding hashing)." << std::endl;
        saveHashToFile(filename, hashTable);
        return;
    }

    else if (command == "HASHADD") { // добавление пары (ключ - значение) в хеш-таблицу
        // получаем оставшуюся часть строки после команды
        size_t pos = query.find(command);
        std::string rest = (pos != std::string::npos) ? ltrim(query.substr(pos + command.size())) : std::string();
        std::istringstream args(rest);
        int key, value;
        if (!(args >> key >> value)) {
            std::cerr << "Ошибка: команда должна быть вида HASHADD <key> <value>\n";
            return;
        }

        // загрузим актуальное состояние (и режим) из файла
        loadHashFromFile(filename, hashTable);

        hashTable.insert(key, value);

        // сохраняем всё назад (включая header)
        saveHashToFile(filename, hashTable);

        std::cout << "Элемент (" << key << ", " << value << ") добавлен в хеш-таблицу и сохранён в файл.\n";
        return;
    }

    else if (command == "HASHDEL") { // удаление по ключу
        size_t pos = query.find(command);
        std::string rest = (pos != std::string::npos) ? ltrim(query.substr(pos + command.size())) : std::string();
        std::istringstream args(rest);
        int key;
        if (!(args >> key)) {
            std::cerr << "Ошибка: команда должна быть вида HASHDEL <key>\n";
            return;
        }

        // загрузим актуальное состояние (и режим) из файла
        loadHashFromFile(filename, hashTable);

        bool removed = hashTable.remove(key);
        if (!removed) {
            std::cout << "Ключ " << key << " не найден.\n";
            return;
        }

        // перезаписываем файл с текущими парами и header
        saveHashToFile(filename, hashTable);

        std::cout << "Ключ " << key << " удалён из таблицы и файла.\n";
        return;
    }

    else if (command == "HASHGET") { // получение значения по ключу их хеш-таблицы
        size_t pos = query.find(command);
        std::string rest = (pos != std::string::npos) ? ltrim(query.substr(pos + command.size())) : std::string();
        std::istringstream args(rest);
        int key;
        if (!(args >> key)) {
            std::cerr << "Ошибка: команда должна быть вида HASHGET <key>\n";
            return;
        }

        // загрузка файла с текущими параметрами
        loadHashFromFile(filename, hashTable);
        auto res = hashTable.get(key);
        if (res.has_value()) std::cout << "Значение для ключа " << key << ": " << res.value() << "\n";
        else std::cout << "Ключ " << key << " не найден.\n";
        return;
    }


    // печать таблицы
    else if (command == "PRINTHASH") {
        loadHashFromFile(filename, hashTable);
        std::string mode;
        switch (hashTable.getType()) {
            case HashType::DOUBLE_HASHING:  mode = "Double hashing"; break;
            case HashType::CUCKOO_HASHING:  mode = "Cuckoo hashing"; break;
            case HashType::FOLDING_HASHING: mode = "Folding hashing (метод свёртки)"; break;
        }

        std::cout << "Текущий режим: " << mode << "\n";

        hashTable.print();
        return;
    }

    // ----- Бинарные команды сериализации ----
    else if (command == "ARRAY_SAVE_BIN") {
        Array arr;
        loadArrayFromFile(filename, arr);
        saveArrayToBinaryFile(filename + ".bin", arr);
        std::cout << "Массив сохранен в бинарном формате: " << filename + ".bin" << std::endl;
    }
    else if (command == "ARRAY_LOAD_BIN") {
        Array arr;
        loadArrayFromBinaryFile(filename, arr);
        saveArrayToFile(filename, arr);
        std::cout << "Массив загружен из бинарного формата: " << filename << std::endl;
    }
    else if (command == "SLIST_SAVE_BIN") {
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        saveListToBinaryFile(filename + ".bin", list);
        std::cout << "Односвязный список сохранен в бинарном формате: " << filename + ".bin" << std::endl;
    }
    else if (command == "SLIST_LOAD_BIN") {
        SinglyLinkedList list;
        loadListFromBinaryFile(filename, list);
        saveListToFile(filename, list);
        std::cout << "Односвязный список загружен из бинарного формата: " << filename << std::endl;
    }
    else if (command == "DLIST_SAVE_BIN") {
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        saveDoublyListToBinaryFile(filename + ".bin", list);
        std::cout << "Двусвязный список сохранен в бинарном формате: " << filename + ".bin" << std::endl;
    }
    else if (command == "DLIST_LOAD_BIN") {
        DoublyLinkedList list;
        loadDoublyListFromBinaryFile(filename, list);
        saveDoublyListToFile(filename, list);
        std::cout << "Двусвязный список загружен из бинарного формата: " << filename << std::endl;
    }
    else if (command == "STACK_SAVE_BIN") {
        Stack stack;
        loadStackFromFile(filename, stack);
        saveStackToBinaryFile(filename + ".bin", stack);
        std::cout << "Стек сохранен в бинарном формате: " << filename + ".bin" << std::endl;
    }
    else if (command == "STACK_LOAD_BIN") {
        Stack stack;
        loadStackFromBinaryFile(filename, stack);
        saveStackToFile(filename, stack);
        std::cout << "Стек загружен из бинарного формата: " << filename << std::endl;
    }
    else if (command == "QUEUE_SAVE_BIN") {
        Queue queue;
        loadQueueFromFile(filename, queue);
        saveQueueToBinaryFile(filename + ".bin", queue);
        std::cout << "Очередь сохранена в бинарном формате: " << filename + ".bin" << std::endl;
    }
    else if (command == "QUEUE_LOAD_BIN") {
        Queue queue;
        loadQueueFromBinaryFile(filename, queue);
        saveQueueToFile(filename, queue);
        std::cout << "Очередь загружена из бинарного формата: " << filename << std::endl;
    }
    else if (command == "TREE_SAVE_BIN") {
        RedBlackTree tree;
        loadTreeFromFile(filename, tree);
        saveTreeToBinaryFile(filename + ".bin", tree);
        std::cout << "Дерево сохранено в бинарном формате: " << filename + ".bin" << std::endl;
    }
    else if (command == "TREE_LOAD_BIN") {
        RedBlackTree tree;
        loadTreeFromBinaryFile(filename, tree);
        saveTreeToFile(filename, tree);
        std::cout << "Дерево загружено из бинарного формата: " << filename << std::endl;
    }
    else if (command == "HASH_SAVE_BIN") {
        HashTable ht;
        loadHashFromFile(filename, ht);
        saveHashToBinaryFile(filename + ".bin", ht);
        std::cout << "Хеш-таблица сохранена в бинарном формате: " << filename + ".bin" << std::endl;
    }
    else if (command == "HASH_LOAD_BIN") {
        HashTable ht;
        loadHashFromBinaryFile(filename, ht);
        saveHashToFile(filename, ht);
        std::cout << "Хеш-таблица загружена из бинарного формата: " << filename << std::endl;
    }

    // ----- Текстовые команды сериализации ----
    else if (command == "ARRAY_SAVE_TXT") {
        Array arr;
        loadArrayFromFile(filename, arr);
        std::ofstream fout(filename + ".txt");
        arr.serializeText(fout);
        std::cout << "Массив сохранен в текстовом формате: " << filename + ".txt" << std::endl;
    }
    else if (command == "ARRAY_LOAD_TXT") {
        Array arr;
        std::ifstream fin(filename);
        arr.deserializeText(fin);
        saveArrayToFile(filename, arr);
        std::cout << "Массив загружен из текстового формата: " << filename << std::endl;
    }
    else if (command == "SLIST_SAVE_TXT") {
        SinglyLinkedList list;
        loadListFromFile(filename, list);
        std::ofstream fout(filename + ".txt");
        list.serializeText(fout);
        std::cout << "Односвязный список сохранен в текстовом формате: " << filename + ".txt" << std::endl;
    }
    else if (command == "SLIST_LOAD_TXT") {
        SinglyLinkedList list;
        std::ifstream fin(filename);
        list.deserializeText(fin);
        saveListToFile(filename, list);
        std::cout << "Односвязный список загружен из текстового формата: " << filename << std::endl;
    }
    else if (command == "DLIST_SAVE_TXT") {
        DoublyLinkedList list;
        loadDoublyListFromFile(filename, list);
        std::ofstream fout(filename + ".txt");
        list.serializeText(fout);
        std::cout << "Двусвязный список сохранен в текстовом формате: " << filename + ".txt" << std::endl;
    }
    else if (command == "DLIST_LOAD_TXT") {
        DoublyLinkedList list;
        std::ifstream fin(filename);
        list.deserializeText(fin);
        saveDoublyListToFile(filename, list);
        std::cout << "Двусвязный список загружен из текстового формата: " << filename << std::endl;
    }
    else if (command == "STACK_SAVE_TXT") {
        Stack stack;
        loadStackFromFile(filename, stack);
        std::ofstream fout(filename + ".txt");
        stack.serializeText(fout);
        std::cout << "Стек сохранен в текстовом формате: " << filename + ".txt" << std::endl;
    }
    else if (command == "STACK_LOAD_TXT") {
        Stack stack;
        std::ifstream fin(filename);
        stack.deserializeText(fin);
        saveStackToFile(filename, stack);
        std::cout << "Стек загружен из текстового формата: " << filename << std::endl;
    }
    else if (command == "QUEUE_SAVE_TXT") {
        Queue queue;
        loadQueueFromFile(filename, queue);
        std::ofstream fout(filename + ".txt");
        queue.serializeText(fout);
        std::cout << "Очередь сохранена в текстовом формате: " << filename + ".txt" << std::endl;
    }
    else if (command == "QUEUE_LOAD_TXT") {
        Queue queue;
        std::ifstream fin(filename);
        queue.deserializeText(fin);
        saveQueueToFile(filename, queue);
        std::cout << "Очередь загружена из текстового формата: " << filename << std::endl;
    }
    else if (command == "TREE_SAVE_TXT") {
        RedBlackTree tree;
        loadTreeFromFile(filename, tree);
        std::ofstream fout(filename + ".txt");
        tree.serializeText(fout);
        std::cout << "Дерево сохранено в текстовом формате: " << filename + ".txt" << std::endl;
    }
    else if (command == "TREE_LOAD_TXT") {
        RedBlackTree tree;
        std::ifstream fin(filename);
        tree.deserializeText(fin);
        saveTreeToFile(filename, tree);
        std::cout << "Дерево загружено из текстового формата: " << filename << std::endl;
    }
    else if (command == "HASH_SAVE_TXT") {
        HashTable ht;
        loadHashFromFile(filename, ht);
        std::ofstream fout(filename + ".txt");
        ht.serializeText(fout);
        std::cout << "Хеш-таблица сохранена в текстовом формате: " << filename + ".txt" << std::endl;
    }
    else if (command == "HASH_LOAD_TXT") {
        HashTable ht;
        std::ifstream fin(filename);
        ht.deserializeText(fin);
        saveHashToFile(filename, ht);
        std::cout << "Хеш-таблица загружена из текстового формата: " << filename << std::endl;
    }

    else {
        std::cerr << "Неизвестная команда: " << command << std::endl;
    }
}

