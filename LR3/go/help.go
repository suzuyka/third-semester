package main

import "fmt"

func printGeneralHelp() {
	fmt.Println("Общая справка:")
	fmt.Println("Использование: ./project --file <файл> --query \"<команда>\"")
	fmt.Println("Доступные структуры данных:")
	fmt.Println("  -a   Справка по массиву")
	fmt.Println("  -f   Справка по односвязному списку")
	fmt.Println("  -l   Справка по двусвязному списку")
	fmt.Println("  -s   Справка по стеку")
	fmt.Println("  -q   Справка по очереди")
	fmt.Println("  -h   Справка по хеш-таблице")
	fmt.Println("Команды сериализации:")
	fmt.Println("  SAVE_BINARY <файл>  - сохранить в бинарный формат")
	fmt.Println("  LOAD_BINARY <файл>  - загрузить из бинарного формата")
	fmt.Println("  SAVE_TEXT <файл>    - сохранить в текстовый формат")
	fmt.Println("  LOAD_TEXT <файл>    - загрузить из текстового формата")
	fmt.Println("Пример: ./project --file array.txt --query \"MPUSH 10\"")
	fmt.Println("Пример сериализации: ./project --query \"SAVE_BINARY array.bin\"")
}

func printArrayHelp() {
	fmt.Println("Справка: Массив (Array)")
	fmt.Println("  MPUSH <name> <value>      - добавить элемент в конец")
	fmt.Println("  MINDEX <name> <i> <value> - вставить элемент по индексу")
	fmt.Println("  MGET <name> <i>           - получить элемент по индексу")
	fmt.Println("  MSET <name> <i> <value>   - заменить элемент по индексу")
	fmt.Println("  MDEL <name> <i>           - удалить элемент по индексу")
	fmt.Println("  PRINTM <name>             - вывести массив")
	fmt.Println("  СЕРИАЛИЗАЦИЯ:")
	fmt.Println("  SAVE_BINARY array.bin     - сохранить в бинарный файл")
	fmt.Println("  LOAD_BINARY array.bin     - загрузить из бинарного файла")
	fmt.Println("  SAVE_TEXT array.txt       - сохранить в текстовый файл")
	fmt.Println("  LOAD_TEXT array.txt       - загрузить из текстового файла")
}

func printSinglyListHelp() {
	fmt.Println("Справка: Односвязный список (Singly Linked List)")
	fmt.Println("  FPUSH <name> <value>          - добавить в хвост")
	fmt.Println("  FPUSHFRONT <name> <value>     - добавить в голову")
	fmt.Println("  FINSERTBEFORE <name> <x> <v>  - вставить v перед x")
	fmt.Println("  FINSERTAFTER <name> <x> <v>   - вставить v после x")
	fmt.Println("  FDEL <name> <value>           - удалить элемент по значению")
	fmt.Println("  FDELFRONT <name> <value>      - удалить первый элемент")
	fmt.Println("  FDELBACK <name> <value>       - удалить последний элемент")
	fmt.Println("  FGET <name> <i>               - получить элемент по индексу")
	fmt.Println("  FCONTAINS <name> <value>      - проверить наличие элемента")
	fmt.Println("  PRINTF <name>                 - вывести список")
	fmt.Println("  СЕРИАЛИЗАЦИЯ:")
	fmt.Println("  SAVE_BINARY slist.bin         - сохранить в бинарный файл")
	fmt.Println("  LOAD_BINARY slist.bin         - загрузить из бинарного файла")
	fmt.Println("  SAVE_TEXT slist.txt           - сохранить в текстовый файл")
	fmt.Println("  LOAD_TEXT slist.txt           - загрузить из текстового файла")
}

func printDoublyListHelp() {
	fmt.Println("Справка: Двусвязный список (Doubly Linked List)")
	fmt.Println("  LPUSH <name> <value>          - добавить в хвост")
	fmt.Println("  LPUSHFRONT <name> <value>     - добавить в голову")
	fmt.Println("  LINSERTBEFORE <name> <x> <v>  - вставить v перед x")
	fmt.Println("  LINSERTAFTER <name> <x> <v>   - вставить v после x")
	fmt.Println("  LDEL <name> <value>           - удалить элемент по значению")
	fmt.Println("  LDELFRONT <name> <value>      - удалить первый элемент")
	fmt.Println("  LDELBACK <name> <value>       - удалить последний элемент")
	fmt.Println("  LGET <name> <i>               - получить элемент по индексу")
	fmt.Println("  LCONTAINS <name> <value>      - проверить наличие элемента")
	fmt.Println("  PRINTL <name>                 - вывести список")
	fmt.Println("  СЕРИАЛИЗАЦИЯ:")
	fmt.Println("  SAVE_BINARY dlist.bin         - сохранить в бинарный файл")
	fmt.Println("  LOAD_BINARY dlist.bin         - загрузить из бинарного файла")
	fmt.Println("  SAVE_TEXT dlist.txt           - сохранить в текстовый файл")
	fmt.Println("  LOAD_TEXT dlist.txt           - загрузить из текстового файла")
}

func printStackHelp() {
	fmt.Println("Справка: Стек (Stack)")
	fmt.Println("  SPUSH <name> <value> - добавить элемент в стек")
	fmt.Println("  SPOP <name>          - удалить верхний элемент")
	fmt.Println("  PRINTS <name>        - вывести содержимое стека")
	fmt.Println("  СЕРИАЛИЗАЦИЯ:")
	fmt.Println("  SAVE_BINARY stack.bin - сохранить в бинарный файл")
	fmt.Println("  LOAD_BINARY stack.bin - загрузить из бинарного файла")
	fmt.Println("  SAVE_TEXT stack.txt   - сохранить в текстовый файл")
	fmt.Println("  LOAD_TEXT stack.txt   - загрузить из текстового файла")
}

func printQueueHelp() {
	fmt.Println("Справка: Очередь (Queue)")
	fmt.Println("  QPUSH <name> <value> - добавить элемент в очередь")
	fmt.Println("  QPOP <name>          - удалить первый элемент")
	fmt.Println("  PRINTQ <name>        - вывести содержимое очереди")
	fmt.Println("  СЕРИАЛИЗАЦИЯ:")
	fmt.Println("  SAVE_BINARY queue.bin - сохранить в бинарный файл")
	fmt.Println("  LOAD_BINARY queue.bin - загрузить из бинарного файла")
	fmt.Println("  SAVE_TEXT queue.txt   - сохранить в текстовый файл")
	fmt.Println("  LOAD_TEXT queue.txt   - загрузить из текстового файла")
}

func printHashTableHelp() {
	fmt.Println("Справка: Хеш-таблица (Hash Table)")
	fmt.Println("  HINSERT <name> <key> <value> - вставить пару ключ-значение")
	fmt.Println("  HGET <name> <key>            - получить значение по ключу")
	fmt.Println("  HDEL <name> <key>            - удалить пару по ключу")
	fmt.Println("  HCLEAR <name>                - очистить таблицу")
	fmt.Println("  HSETTYPE <name> <type>       - установить тип хеширования")
	fmt.Println("                               (DOUBLE, CUCKOO, FOLDING)")
	fmt.Println("  PRINTH <name>                - вывести таблицу")
	fmt.Println("  СЕРИАЛИЗАЦИЯ:")
	fmt.Println("  SAVE_BINARY hashtable.bin    - сохранить в бинарный файл")
	fmt.Println("  LOAD_BINARY hashtable.bin    - загрузить из бинарного файла")
	fmt.Println("  SAVE_TEXT hashtable.txt      - сохранить в текстовый файл")
	fmt.Println("  LOAD_TEXT hashtable.txt      - загрузить из текстового файла")
}
