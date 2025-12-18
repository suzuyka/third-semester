package main

import (
	"flag"
	"fmt"
	"os"
	"strings"
)


func main() {
	// Парсим флаги
	helpFlag := flag.Bool("help", false, "Показать справку")
	arrayFlag := flag.Bool("a", false, "Справка по массиву")
	slistFlag := flag.Bool("f", false, "Справка по односвязному списку")
	dlistFlag := flag.Bool("l", false, "Справка по двусвязному списку")
	stackFlag := flag.Bool("s", false, "Справка по стеку")
	queueFlag := flag.Bool("q", false, "Справка по очереди")
	hashTableFlag := flag.Bool("h", false, "Справка по хеш-таблице")

	file := flag.String("file", "", "Файл для хранения данных")
	query := flag.String("query", "", "Команда для выполнения")

	flag.Parse()

	// Справка
	if *helpFlag {
		printGeneralHelp()
		os.Exit(0)
	}
	if *arrayFlag {
		printArrayHelp()
		os.Exit(0)
	}
	if *slistFlag {
		printSinglyListHelp()
		os.Exit(0)
	}
	if *dlistFlag {
		printDoublyListHelp()
		os.Exit(0)
	}
	if *stackFlag {
		printStackHelp()
		os.Exit(0)
	}
	if *queueFlag {
		printQueueHelp()
		os.Exit(0)
	}
	if *hashTableFlag {
		printHashTableHelp()
		os.Exit(0)
	}

	if *file != "" && *query != "" {
		if strings.HasPrefix(*query, "M") || strings.HasPrefix(*query, "PRINTM") {
			loadArrayFromFile(*file, &globalArray)
			executeCommand(*query)
			saveArrayToFile(*file, &globalArray)

		} else if strings.HasPrefix(*query, "F") || strings.HasPrefix(*query, "PRINTF") {
			loadSinglyListFromFile(*file, &globalSList)
			executeCommand(*query)
			saveSinglyListToFile(*file, &globalSList)

		} else if strings.HasPrefix(*query, "L") || strings.HasPrefix(*query, "PRINTL") {
			loadDListFromFile(*file, &globalDList)
			executeCommand(*query)
			saveDListToFile(*file, &globalDList)

		} else if strings.HasPrefix(*query, "S") || strings.HasPrefix(*query, "PRINTS") {
			loadStackFromFile(*file, &globalStack)
			executeCommand(*query)
			saveStackToFile(*file, &globalStack)

		} else if strings.HasPrefix(*query, "Q") || strings.HasPrefix(*query, "PRINTQ") {
			loadQueueFromFile(*file, &globalQueue)
			executeCommand(*query)
			saveQueueToFile(*file, &globalQueue)

		} else if strings.HasPrefix(*query, "H") || strings.HasPrefix(*query, "PRINTH") { // Добавлено
			loadHashTableFromFile(*file, globalHashTable)
			executeCommand(*query)
			saveHashTableToFile(*file, globalHashTable)

		} else {
			executeCommand(*query)
		}

		fmt.Println("Файл:", *file)
		fmt.Println("Команда:", *query)
	} else {
		fmt.Println("Запустите с --help для справки")
	}

}
