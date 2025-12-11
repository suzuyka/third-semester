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
#include "Set.h"
#include "LFUCache.h"
#include "HashTable.h"
#include "BinarySearchTreeZadacha.h"

using namespace std;

MyArray* currentArray = nullptr;
List* currentList = nullptr;
DoublyLinkedList* currentDList = nullptr;
DynamicStack* currentStack = nullptr;
DynamicQueue* currentQueue = nullptr;
T* currentTree = nullptr;
BST* currentBST = nullptr;

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

// ----- Вспомогательные функции для Set -----
void loadSetFromFile(const string& filename, Set& set) { // загрузка множества из файла
    ifstream fin(filename);
    if (!fin.is_open()) return;

    int value;
    while (fin >> value) {
        set.add(value);
    }
    fin.close();
}

void saveSetToFile(const string& filename, Set& set) { // сохранение множества в файл
    ofstream fout(filename);
    if (!fout.is_open()) return;

    for (int val : set.toVector()) {
        fout << val << " ";
    }
    fout.close();
}

// ----- Вспомогательные функции для Hash -----
static inline string ltrim(const string &s) { // удаляет пробелы в начале строки
    size_t i = 0;
    while (i < s.size() && isspace((unsigned char)s[i])) ++i;
    return s.substr(i);
}

void loadHashFromFile(const string& filename, HashTable& ht) { // загрузка хэш-таблицы из файла
    ifstream in(filename);
    if (!in.is_open()) return;

    string token, typeStr;
    int size = 11; // значение по умолчанию

    // читаем тип и размер
    if (in >> token >> typeStr && token == "TYPE") {
        HashType type = HashType::DOUBLE_HASHING;
        if (typeStr == "CUCKOO") type = HashType::CUCKOO_HASHING;

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

void saveHashToFile(const string& filename, const HashTable& ht) { // сохранение хэш-таблицы в файл
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Ошибка при открытии файла для записи.\n";
        return;
    }

    // сохраняем тип хеширования
    out << "TYPE ";
    switch (ht.getType()) {
        case HashType::DOUBLE_HASHING:  out << "DOUBLE\n"; break;
        case HashType::CUCKOO_HASHING:  out << "CUCKOO\n"; break;
    }

    // сохраняем размер таблицы
    out << "SIZE " << ht.getSize() << "\n";

    // сохраняем пары ключ–значение
    for (auto& p : ht.toVector())
        out << p.first << " " << p.second << "\n";
}

// ----- Вспомогательные функции для работы с текстом -----
void saveStringToFile(const string& filename, const string& text) { // сохранение строки в файл
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи\n";
        return;
    }
    fout << text;
    fout.close();
}

string loadStringFromFile(const string& filename) { // загрузка строки из файла
    ifstream fin(filename);
    if (!fin.is_open()) return "";

    string content((istreambuf_iterator<char>(fin)),
                        istreambuf_iterator<char>());
    fin.close();
    return content;
}
// сохранение состояния LFU кэша в файл
void saveLFUToFile(const string& filename, const LFUCache& lfu) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return;
    }

    out << "CAPACITY " << lfu.capacity << "\n";
    
    // Сохраняем в порядке вставки
    DLNode* current = lfu.insertionOrder.head;
    while (current != nullptr) {
        int key = stoi(current->data);
        if (lfu.cache.count(key)) {
            out << key << " " << lfu.cache.at(key).value << " " << lfu.cache.at(key).freq << "\n";
        }
        current = current->next;
    }
    out.close();
}

// загрузка состояния LFU кэша из файла
void loadLFUFromFile(const string& filename, LFUCache& lfu) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Файл не найден, создаётся новый LFU Cache\n";
        return;
    }

    lfu.cache.clear();
    lfu.insertionOrder.clear(); // <-- очистка списка

    string header;
    if (in >> header && header == "CAPACITY") {
        in >> lfu.capacity;
    } else {
        lfu.capacity = 3;
    }

    // Временный вектор для сохранения порядка из файла
    vector<tuple<int, int, int>> entries; // key, value, freq

    int key, value, freq;
    while (in >> key >> value >> freq) {
        entries.emplace_back(key, value, freq);
    }
    in.close();

    // Восстанавливаем в том же порядке, в каком были записаны
    for (const auto& [k, v, f] : entries) {
        lfu.cache[k] = {v, f};
        lfu.insertionOrder.ListPUSHTAIL(to_string(k));
    }
}


// ========= ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ДОП. КОМАНД =========

// ---------- ЛОГИЧЕСКИЕ ВЫРАЖЕНИЯ ----------
int getPriority(char op) {
    switch (op) {
        case '!': return 3;
        case '&': return 2;
        case '|':
        case '^': return 1;
        case '(': return 0;
        default: return -1;
    }
}

bool isOperator(char c) {
    return c == '!' || c == '&' || c == '|' || c == '^';
}

bool applyBinaryOp(bool a, bool b, char op) {
    switch (op) {
        case '&': return a && b;
        case '|': return a || b;
        case '^': return a != b;
        default: throw runtime_error("Неизвестный бинарный оператор");
    }
}

bool applyUnaryOp(bool a, char op) {
    if (op == '!') return !a;
    throw runtime_error("Неизвестный унарный оператор");
}

bool evaluateExpression(const string& expr) {
    DynamicStack outputStack, operatorStack;
    initStack(&outputStack, 50);
    initStack(&operatorStack, 50);

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];
        if (ch == ' ') continue;

        if (ch == '0' || ch == '1') {
            push(&outputStack, string(1, ch));
        }
        else if (ch == '(') {
            push(&operatorStack, string(1, ch));
        }
        else if (ch == ')') {
            while (!isEmpty(&operatorStack) && top(&operatorStack)[0] != '(') {
                string op_str = pop(&operatorStack);
                char op = op_str[0];
                if (op == '!') {
                    if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов для !");
                    bool a = (pop(&outputStack)[0] == '1');
                    push(&outputStack, applyUnaryOp(a, op) ? "1" : "0");
                } else {
                    if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов");
                    bool b = (pop(&outputStack)[0] == '1');
                    if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов");
                    bool a = (pop(&outputStack)[0] == '1');
                    push(&outputStack, applyBinaryOp(a, b, op) ? "1" : "0");
                }
            }
            if (!isEmpty(&operatorStack)) pop(&operatorStack); // убрать '('
            else throw runtime_error("Несоответствие скобок");
        }
        else if (isOperator(ch)) {
            bool isUnary = (i == 0 || expr[i-1] == '(' || isOperator(expr[i-1]));
            if (isUnary) {
                push(&operatorStack, string(1, ch));
            } else {
                while (!isEmpty(&operatorStack) &&
                       top(&operatorStack)[0] != '(' &&
                       getPriority(top(&operatorStack)[0]) >= getPriority(ch)) {
                    string op_str = pop(&operatorStack);
                    char op = op_str[0];
                    if (op == '!') {
                        if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов для !");
                        bool a = (pop(&outputStack)[0] == '1');
                        push(&outputStack, applyUnaryOp(a, op) ? "1" : "0");
                    } else {
                        if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов");
                        bool b = (pop(&outputStack)[0] == '1');
                        if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов");
                        bool a = (pop(&outputStack)[0] == '1');
                        push(&outputStack, applyBinaryOp(a, b, op) ? "1" : "0");
                    }
                }
                push(&operatorStack, string(1, ch));
            }
        }
        else {
            throw runtime_error("Недопустимый символ: " + string(1, ch));
        }
    }

    while (!isEmpty(&operatorStack)) {
        string op_str = pop(&operatorStack);
        char op = op_str[0];
        if (op == '(' || op == ')') throw runtime_error("Несоответствие скобок");
        if (op == '!') {
            if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов для !");
            bool a = (pop(&outputStack)[0] == '1');
            push(&outputStack, applyUnaryOp(a, op) ? "1" : "0");
        } else {
            if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов");
            bool b = (pop(&outputStack)[0] == '1');
            if (isEmpty(&outputStack)) throw runtime_error("Недостаточно операндов");
            bool a = (pop(&outputStack)[0] == '1');
            push(&outputStack, applyBinaryOp(a, b, op) ? "1" : "0");
        }
    }

    if (isEmpty(&outputStack)) throw runtime_error("Пустое выражение");
    string res = pop(&outputStack);
    if (!isEmpty(&outputStack)) throw runtime_error("Лишние операнды");

    freeStack(&outputStack);
    freeStack(&operatorStack);
    return res == "1";
}

// ---------- ПОДМНОЖЕСТВА С МИНИМАЛЬНОЙ РАЗНИЦЕЙ ----------
void handleSimilarSets() {
    string line;
    cout << "Введите целые числа через пробел: ";
    getline(cin, line);
    if (line.empty()) {
        cout << "Пустой ввод." << endl;
        return;
    }

    Set inputSet;
    stringstream ss(line);
    int val;
    while (ss >> val) {
        inputSet.add(val);
    }

    vector<int> elements = inputSet.toVector();
    if (elements.empty()) {
        cout << "Множество пустое." << endl;
        return;
    }

    long long total = 0;
    for (int x : elements) total += x;

    const long long MAX_SUM = 10000;
    long long limit = min(abs(total), MAX_SUM);
    vector<vector<bool>> dp(elements.size() + 1, vector<bool>(limit + 1, false));

    for (size_t i = 0; i <= elements.size(); ++i) dp[i][0] = true;

    for (size_t i = 1; i <= elements.size(); ++i) {
        int num = elements[i - 1];
        for (long long s = 0; s <= limit; ++s) {
            dp[i][s] = dp[i - 1][s];
            if (s >= num) dp[i][s] = dp[i][s] || dp[i - 1][s - num];
        }
    }

    long long target = total / 2;
    long long best = 0;
    for (long long s = min(target, limit); s >= 0; --s) {
        if (dp[elements.size()][s]) { best = s; break; }
    }
    long long diff = abs(total - 2 * best);

    // Восстановление подмножества
    Set A, B;
    long long cur = best;
    for (int i = (int)elements.size() - 1; i >= 0; --i) {
        if (cur >= elements[i] && dp[i][cur - elements[i]]) {
            A.add(elements[i]);
            cur -= elements[i];
        } else {
            B.add(elements[i]);
        }
    }

    cout << "Подмножество A: "; A.print(); cout << endl;
    cout << "Подмножество B: "; B.print(); cout << endl;
    cout << "Минимальная разница: " << diff << endl;
}

// ---------- ПОИСК ПОДМАССИВОВ С ЗАДАННОЙ СУММОЙ ----------
void handleFindSubarray() {
    string line;
    cout << "Введите массив целых чисел через пробел: ";
    getline(cin, line);
    if (line.empty()) {
        cout << "Пустой ввод." << endl;
        return;
    }

    int target;
    cout << "Введите цель (сумму): ";
    if (!(cin >> target)) {
        cout << "Неверная цель." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    cin.ignore();

    MyArray arr;
    stringstream ss(line);
    int num;
    while (ss >> num) {
        arr.APUSH(to_string(num));
    }

    cout << "\nПодмассивы с суммой " << target << ":\n";
    bool found = false;
    int n = arr.ALEIGHT(); // получаем длину один раз

    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        MyArray sub;

        for (int j = i; j < n; ++j) {
            // Получаем число из строки
            int value = stoi(arr.AGET(j));
            sum += value;

            // Добавляем строку в подмассив для вывода
            sub.APUSH(arr.AGET(j));

            if (sum == target) {
                found = true;
                cout << "[";
                for (int k = 0; k < sub.ALEIGHT(); ++k) {
                    if (k > 0) cout << ", ";
                    cout << sub.AGET(k);
                }
                cout << "]" << endl;
            }
        }
    }

    if (!found) {
        cout << "Подмассивов с такой суммой не найдено." << endl;
    }
}

// ---------- ВЫВОД РОДИТЕЛЕЙ С ДВУМЯ ДЕТЬМИ ----------
void handlePrintTreeParents() {
    if (!currentBST) {
        cout << "BST не создано." << endl;
        return;
    }
    currentBST->printForks();
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

    cout << "\nМНОЖЕСТВО (T):" << endl;
    cout << "  SETADD value - добавить элемент" << endl;
    cout << "  SETDEL value - удалить элемент" << endl;
    cout << "  SET_AT value - проверка нахождения элемента в множестве" << endl;
    cout << "  PRINTSET - вывести множество" << endl;
    
    cout << "\nХЕШ-ТАБЛИЦА (HASH):" << endl;
    cout << "  SETDOUBLEHASH    - режим двойного хеширования" << endl;
    cout << "  SETCUCKOOHASH    - режим кукушкиного хеширования" << endl;
    cout << "  HASHADD key value  - добавить пару (ключ, значение)" << endl;
    cout << "  HASHDEL key     - удалить элемент по ключу" << endl;
    cout << "  HASHGET key      - получить значение по ключу" << endl;
    cout << "  PRINTHASH        - вывести хеш-таблицу и текущий режим" << endl;

    cout << "\nLFU КЭШ (LFU):" << endl;
    cout << "  SETLFUCAP num    - задать ёмкость кэша (capacity)" << endl;
    cout << "  LFUSET key value   - вставить пару (key, value)" << endl;
    cout << "  LFUGET key       - получить значение по ключу (или -1)" << endl;
    cout << "  CLEARLFU         - очистка кеша" << endl;
    cout << "  PRINTLFU         - вывести текущее состояние кэша" << endl;

    cout << "\nОБЩИЕ КОМАНДЫ:" << endl;
    cout << "  HELP - показать справку" << endl;
    cout << "  CLEAR - очистить все структуры" << endl;
    cout << "  LOGICEXPRESSION <выражение> - вычисление логического выражения" << endl;
    cout << "  SIMULARSETS <множество> - нахождение схожых подмножеств(минимальная разница в суммах элементах полученных подмножеств)" << endl;
    cout << "  FINDSUBARRAY <массив> <цель> - нахождение массивов с заданной суммой элементов" << endl;
    cout << "  PRINTTREEPARENTS <бинарное дерево поиска> - вывод родителей дерева с двумя детьми" << endl;
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

//множество 
    else if (cmd == "SETADD") {
        string valStr;
        if (!(ss >> valStr)) {
            cout << "Ошибка: укажите целое число для добавления" << endl;
            return;
        }
        int value = stoi(valStr);
        Set set;
        loadSetFromFile("set.txt", set);
        set.add(value);
        saveSetToFile("set.txt", set);
        cout << "-> добавлен " << value << endl;
    }
    else if (cmd == "SETDEL") {
        string valStr;
        if (!(ss >> valStr)) {
            cout << "Ошибка: укажите целое число для удаления" << endl;
            return;
        }
        int value = stoi(valStr);
        Set set;
        loadSetFromFile("set.txt", set);
        if (set.contains(value)) {
            set.del(value);
            saveSetToFile("set.txt", set);
            cout << "-> удалён " << value << endl;
        } else {
            cout << "Ошибка: элемент " << value << " не найден в множестве" << endl;
        }
    }
    else if (cmd == "SET_AT") {
        string valStr;
        if (!(ss >> valStr)) {
            cout << "Ошибка: укажите целое число для проверки" << endl;
            return;
        }
        int value = stoi(valStr);
        Set set;
        loadSetFromFile("set.txt", set);
        cout << "-> " << (set.contains(value) ? "TRUE" : "FALSE") << endl;
    }
    else if (cmd == "PRINTSET") {
        Set set;
        loadSetFromFile("set.txt", set);
        cout << "-> ";
        set.print();
        cout << endl;
    }

//хэш таблица
    else if (cmd == "SETDOUBLEHASH") {
        HashTable ht(11, HashType::DOUBLE_HASHING);
        saveHashToFile("hash.txt", ht);
        cout << "Режим: Двойное хеширование." << endl;
    }
    else if (cmd == "SETCUCKOOHASH") {
        HashTable ht(11, HashType::CUCKOO_HASHING);
        saveHashToFile("hash.txt", ht);
        cout << "Режим: Кукушкино хеширование." << endl;
    }
    else if (cmd == "HASHADD") {
        int key, value;
        if (!(ss >> key >> value)) {
            cout << "Ошибка: команда должна быть вида HASHADD <ключ> <значение>" << endl;
            return;
        }
        HashTable ht;
        loadHashFromFile("hash.txt", ht);
        ht.insert(key, value);
        saveHashToFile("hash.txt", ht);
        cout << "Элемент (" << key << ", " << value << ") добавлен." << endl;
    }
    else if (cmd == "HASHDEL") {
        int key;
        if (!(ss >> key)) {
            cout << "Ошибка: укажите ключ для удаления" << endl;
            return;
        }
        HashTable ht;
        loadHashFromFile("hash.txt", ht);
        if (ht.remove(key)) {
            saveHashToFile("hash.txt", ht);
            cout << "Ключ " << key << " удалён." << endl;
        } else {
            cout << "Ключ " << key << " не найден." << endl;
        }
    }
    else if (cmd == "HASHGET") {
        int key;
        if (!(ss >> key)) {
            cout << "Ошибка: укажите ключ для поиска" << endl;
            return;
        }
        HashTable ht;
        loadHashFromFile("hash.txt", ht);
        auto res = ht.get(key);
        if (res.has_value()) {
            cout << "Значение для ключа " << key << ": " << res.value() << endl;
        } else {
            cout << "Ключ " << key << " не найден." << endl;
        }
    }
    else if (cmd == "PRINTHASH") {
        HashTable ht;
        loadHashFromFile("hash.txt", ht);
        string mode;
        switch (ht.getType()) {
            case HashType::DOUBLE_HASHING:  mode = "Double hashing"; break;
            case HashType::CUCKOO_HASHING:  mode = "Cuckoo hashing"; break;
            default: mode = "Unknown";
        }
        cout << "Текущий режим: " << mode << endl;
        ht.print();
    }
//lfu кэш
    else if (cmd == "SETLFUCAP") {
        int cap;
        if (!(ss >> cap) || cap <= 0) {
            cout << "Ошибка: укажите положительное целое число как ёмкость кэша" << endl;
            return;
        }
        LFUCache lfu(cap);
        saveLFUToFile("lfu.txt", lfu);
        cout << "LFU Cache создан с ёмкостью " << cap << endl;
    }
    else if (cmd == "LFUSET") {
        int key, value;
        if (!(ss >> key >> value)) {
            cout << "Ошибка: команда должна быть вида LFUSET <ключ> <значение>" << endl;
            return;
        }
        LFUCache lfu;
        loadLFUFromFile("lfu.txt", lfu);
        lfu.set(key, value);
        saveLFUToFile("lfu.txt", lfu);
        cout << "Значение " << value << " присвоено ключу " << key << endl;
    }
    else if (cmd == "LFUGET") {
        int key;
        if (!(ss >> key)) {
            cout << "Ошибка: укажите ключ для получения значения" << endl;
            return;
        }
        LFUCache lfu;
        loadLFUFromFile("lfu.txt", lfu);
        auto res = lfu.get(key);
        saveLFUToFile("lfu.txt", lfu); // важно, частота обновляется при get
        if (res.has_value()) {
            cout << "-> " << res.value() << endl;
        } else {
            cout << "-> -1" << endl;
        }
    }
    else if (cmd == "PRINTLFU") {
        LFUCache lfu;
        loadLFUFromFile("lfu.txt", lfu);
        lfu.print();
    }
    else if (cmd == "CLEARLFU") {
        LFUCache lfu;
        loadLFUFromFile("lfu.txt", lfu);
        lfu.clear();
        saveLFUToFile("lfu.txt", lfu);
        cout << "LFU Cache очищен." << endl;
    }
    else if (cmd == "BSTCREATE") {
        delete currentBST;
        currentBST = new BST();
        cout << "Дерево создано." << endl;
    }
    else if (cmd == "BSTINSERT") {
        if (currentBST == nullptr) {
            cout << "Сначала создайте дерево (BSTCREATE)." << endl;
            return;
        }
        int value;
        if (ss >> value) {
            currentBST->add(value);
            cout << "Элемент " << value << " добавлен." << endl;
        } else {
            cout << "Ошибка: укажите целое число после BSTINSERT." << endl;
        }
    }

//доп команды
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
    else if (cmd == "LOGICEXPRESSION") {
        string expr;
        cout << "Введите логическое выражение (0,1,!,&,|,^, скобки): ";
        getline(cin, expr);
        try {
            bool res = evaluateExpression(expr);
            cout << "Результат: " << (res ? "1" : "0") << endl;
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    else if (cmd == "SIMULARSETS") {
        handleSimilarSets();
    }
    else if (cmd == "FINDSUBARRAY") {
        handleFindSubarray();
    }
    else if (cmd == "PRINTTREEPARENTS") {
        handlePrintTreeParents();
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