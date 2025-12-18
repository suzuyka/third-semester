#include "include/CommandProcessor.h"

#include <iostream>
#include <string>

std::string getArgValue(int argc, char* argv[], const std::string& key) { // получить значение аргумента
    for (int i = 1; i < argc - 1; i++) {
        if (argv[i] == key) return argv[i + 1];
    }
    return "";
}

int main(int argc, char* argv[]) { // главная функция

    if (argc > 1) {
        std::string arg1 = argv[1];

        if (arg1 == "--help") { // справка по программе
            std::cout << "Использование: ./main --file <файл> --query \"<КОМАНДА>\"\n";
            std::cout << "Флаги справки:\n";
            std::cout << "  -a           : команды для массива\n";
            std::cout << "  -f           : команды для односвязного списка\n";
            std::cout << "  -l           : команды для двусвязного списка\n";
            std::cout << "  -s           : команды для стека\n";
            std::cout << "  -q           : команды для очереди\n";
            std::cout << "  -t           : команды для дерева\n";
            std::cout << "  -hash        : команды для хеш-таблицы\n";
            std::cout << "  -serialize   : команды сериализации\n";
            return 0;
        }
        else if (arg1 == "-a") { // справка по массиву
            std::cout << "Команды для массива:\n"
            << "  MPUSH <x>           - добавить в конец\n"
            << "  MINDEX <i> <x>      - вставить по индексу\n"
            << "  MGET <i>            - получить элемент\n"
            << "  MSET <i> <x>        - заменить элемент\n"
            << "  MDEL <i>            - удалить элемент\n"
            << "  PRINTM              - вывести массив\n";
            return 0;
        }
        else if (arg1 == "-f") { // справка по односвязному списку
            std::cout << "Команды для односвязного списка:\n"
            << "  FPUSHFRONT <x>      - добавить в голову\n"
            << "  FPUSH <x>           - добавить в хвост\n"
            << "  FINSERTBEFORE <t> <x> - вставить перед t\n"
            << "  FINSERTAFTER <t> <x>  - вставить после t\n"
            << "  FDEL <x>            - удалить по значению\n"
            << "  FDELFRONT <x>       - удалить первый элемент\n"
            << "  FDELBACK <x>        - удалить последний элемент\n"
            << "  FCONTAINS <x>       - поиск элемента\n"
            << "  FGET <i>            - получить по индексу\n"
            << "  PRINTF              - вывести список\n";
            return 0;
        }
        else if (arg1 == "-l") { // справка по двусвязному списку
            std::cout << "Команды для двусвязного списка:\n"
            << "  LPUSHFRONT <x>      - добавить в голову\n"
            << "  LPUSH <x>           - добавить в хвост\n"
            << "  LINSERTBEFORE <t> <x> - вставить перед t\n"
            << "  LINSERTAFTER <t> <x>  - вставить после t\n"
            << "  LDEL <x>            - удалить по значению\n"
            << "  LDELFRONT <x>       - удалить первый элемент\n"
            << "  LDELBACK <x>        - удалить последний элемент\n"
            << "  LCONTAINS <x>       - поиск элемента\n"
            << "  LGET <i>            - получить по индексу\n"
            << "  PRINTL              - вывести список\n";
            return 0;
        }
        else if (arg1 == "-s") { // справка по стеку
            std::cout << "Команды для стека:\n"
            << "  SPUSH <x>           - push\n"
            << "  SPOP                - pop\n"
            << "  PRINTS              - вывести стек\n";
            return 0;
        }
        else if (arg1 == "-q") { // справка по очереди
            std::cout << "Команды для очереди:\n"
            << "  QPUSH <x>           - enqueue\n"
            << "  QPOP                - dequeue\n"
            << "  PRINTQ              - вывести очередь\n";
            return 0;
        }
        else if (arg1 == "-t") { // справка по дереву
            std::cout << "Команды для дерева (красно-чёрного):\n"
            << "  TINSERT <x>         - вставить\n"
            << "  TDEL <x>            - удалить\n"
            << "  TGET <x>            - поиск\n"
            << "  TVALIDATE           - проверка дерева на свойства\n"
            << "  PRINT               - вывести дерево (in-order)\n";
            return 0;
        }
        else if (arg1 == "-hash") { // справка по хеш-таблице
            std::cout << "Команды для хеш-таблицы:\n"
            << "  SETDOUBLEHASH    - режим двойного хеширования\n"
            << "  SETCUCKOOHASH    - режим кукушкиного хеширования\n"
            << "  SETFOLDHASH      - режим метода свёртки (folding)\n"
            << "  HASHADD <k> <v>  - добавить пару (ключ, значение)\n"
            << "  HASHDEL <k>      - удалить элемент по ключу\n"
            << "  HASHGET <k>      - получить значение по ключу\n"
            << "  PRINTHASH        - вывести хеш-таблицу и текущий режим\n";
            return 0;
        }
        else if (arg1 == "-serialize") {
            std::cout << "Команды сериализации:\n"
            << "  Бинарный формат:\n"
            << "    ARRAY_SAVE_BIN    - сохранить массив в бинарном формате\n"
            << "    ARRAY_LOAD_BIN    - загрузить массив из бинарного формата\n"
            << "    SLIST_SAVE_BIN    - сохранить односвязный список в бинарном формате\n"
            << "    SLIST_LOAD_BIN    - загрузить односвязный список из бинарного формата\n"
            << "    DLIST_SAVE_BIN    - сохранить двусвязный список в бинарном формате\n"
            << "    DLIST_LOAD_BIN    - загрузить двусвязный список из бинарного формата\n"
            << "    STACK_SAVE_BIN    - сохранить стек в бинарном формате\n"
            << "    STACK_LOAD_BIN    - загрузить стек из бинарного формата\n"
            << "    QUEUE_SAVE_BIN    - сохранить очередь в бинарном формате\n"
            << "    QUEUE_LOAD_BIN    - загрузить очередь из бинарного формата\n"
            << "    TREE_SAVE_BIN     - сохранить дерево в бинарном формате\n"
            << "    TREE_LOAD_BIN     - загрузить дерево из бинарного формата\n"
            << "    HASH_SAVE_BIN     - сохранить хеш-таблицу в бинарном формате\n"
            << "    HASH_LOAD_BIN     - загрузить хеш-таблицу из бинарного формата\n"
            << "\n"
            << "  Текстовый формат:\n"
            << "    ARRAY_SAVE_TXT    - сохранить массив в текстовом формате\n"
            << "    ARRAY_LOAD_TXT    - загрузить массив из текстового формата\n"
            << "    SLIST_SAVE_TXT    - сохранить односвязный список в текстовом формате\n"
            << "    SLIST_LOAD_TXT    - загрузить односвязный список из текстового формата\n"
            << "    DLIST_SAVE_TXT    - сохранить двусвязный список в текстовом формате\n"
            << "    DLIST_LOAD_TXT    - загрузить двусвязный список из текстового формата\n"
            << "    STACK_SAVE_TXT    - сохранить стек в текстовом формате\n"
            << "    STACK_LOAD_TXT    - загрузить стек из текстового формата\n"
            << "    QUEUE_SAVE_TXT    - сохранить очередь в текстовом формате\n"
            << "    QUEUE_LOAD_TXT    - загрузить очередь из текстового формата\n"
            << "    TREE_SAVE_TXT     - сохранить дерево в текстовом формате\n"
            << "    TREE_LOAD_TXT     - загрузить дерево из текстового формата\n"
            << "    HASH_SAVE_TXT     - сохранить хеш-таблицу в текстовом формате\n"
            << "    HASH_LOAD_TXT     - загрузить хеш-таблицу из текстового формата\n"
            << "\n"
            << "Примеры использования:\n"
            << "  ./main --file data.txt --query \"ARRAY_SAVE_BIN\"\n"
            << "  ./main --file data.bin --query \"SLIST_LOAD_BIN\"\n"
            << "  ./main --file tree.data --query \"TREE_SAVE_TXT\"\n"
            << "  ./main --file hash.txt --query \"HASH_LOAD_TXT\"\n";
            return 0;
        }
    }



    if (argc < 5) {
        std::cerr << "Использование: ./main --file file.data --query \"COMMAND\"\n";
        std::cerr << "Комманда для справки: ./main --help\n";
        return 1;
    }

    std::string filename = getArgValue(argc, argv, "--file");
    std::string query = getArgValue(argc, argv, "--query");

    CommandProcessor processor;
    processor.execute(query, filename);

    return 0;
}
