package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Глобальные переменные для текущих структур данных
var (
	currentArray  *Array
	currentList   *SingleLL
	currentDList  *DoubleList
	currentStack  *Stack
	currentQueue  *Queue
)

func main() {
	fmt.Println("=== Интерфейс ===")
	fmt.Println("Введите команды (HELP MAIN для справки, EXIT для выхода):")

	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("> ")
		if !scanner.Scan() {
			break
		}

		command := strings.TrimSpace(scanner.Text())
		if command == "" {
			continue
		}

		mainCommand(command)
	}
}

func mainCommand(command string) {
	parts := strings.Fields(command)
	if len(parts) == 0 {
		return
	}

	cmd := parts[0]
	args := parts[1:]

	switch cmd {
	// =========================== МАССИВ ===================================
	case "MCREATE":
		currentArray = &Array{}
		MCreate(currentArray)
		fmt.Println("Массив создан")

	case "MPUSH":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		value := strings.Join(args[1:], " ")

		switch position {
		case "F":
			MInsert(currentArray, 0, value)
		case "B":
			MPushBack(currentArray, value)
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			MInsert(currentArray, index, value)
		}
		fmt.Println("Элемент добавлен")

	case "MDEL":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		switch position {
		case "F":
			MDelIndex(currentArray, 0)
		case "B":
			if currentArray.size > 0 {
				MDelIndex(currentArray, currentArray.size-1)
			}
		case "V":
			value := strings.Join(args[1:], " ")
			for i := 0; i < currentArray.size; i++ {
				if MGetValue(currentArray, i) == value {
					MDelIndex(currentArray, i)
					break
				}
			}
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			MDelIndex(currentArray, index)
		}
		fmt.Println("Элемент удален")

	case "MGET":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		switch position {
		case "F":
			if currentArray.size > 0 {
				fmt.Printf("Первый элемент: %s\n", MGetValue(currentArray, 0))
			}
		case "B":
			if currentArray.size > 0 {
				fmt.Printf("Последний элемент: %s\n", MGetValue(currentArray, currentArray.size-1))
			}
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			if index >= 0 && index < currentArray.size {
				fmt.Printf("Элемент по индексу %d: %s\n", index, MGetValue(currentArray, index))
			} else {
				fmt.Println("Неверный индекс")
			}
		}

	case "MFIND":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано значение для поиска")
			return
		}

		value := strings.Join(args, " ")
		found := false
		for i := 0; i < currentArray.size; i++ {
			if MGetValue(currentArray, i) == value {
				fmt.Printf("Значение найдено по индексу: %d\n", i)
				found = true
				break
			}
		}
		if !found {
			fmt.Println("Значение не найдено")
		}

	case "MSIZE":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		fmt.Printf("Размер массива: %d\n", MGetSize(currentArray))

	case "MPRINT":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		OutputM(currentArray)

	case "MSAVE":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		saveArrayToFile(currentArray, args[0])

	case "MLOAD":
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		if currentArray == nil {
			currentArray = &Array{}
		}
		loadArrayFromFile(currentArray, args[0])

	case "MREPLACE":
		if currentArray == nil {
			fmt.Println("Ошибка: Массив не создан")
			return
		}
		if len(args) < 2 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		index, err := strconv.Atoi(args[0])
		if err != nil {
			fmt.Println("Ошибка: Неверный индекс")
			return
		}
		value := strings.Join(args[1:], " ")
		if index >= 0 && index < currentArray.size {
			MReplace(currentArray, index, value)
			fmt.Println("Элемент заменен")
		} else {
			fmt.Println("Неверный индекс")
		}

	// =========================== ОДНОСВЯЗНЫЙ СПИСОК =======================
	case "FCREATE":
		if currentList != nil {
			FDelList(currentList)
		}
		currentList = &SingleLL{}
		fmt.Println("Односвязный список создан")

	case "FPUSH":
		if currentList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		value := strings.Join(args[1:], " ")

		switch position {
		case "F":
			FPushFront(currentList, value)
			fmt.Println("Элемент добавлен в начало")
		case "B":
			FPushBack(currentList, value)
			fmt.Println("Элемент добавлен в конец")
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			FPushAt(currentList, index, value)
		}

	case "FDEL":
		if currentList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		switch position {
		case "F":
			if currentList.head != nil {
				FDelValue(currentList, currentList.head.key)
				fmt.Println("Элемент удален из начала")
			}
		case "B":
			if currentList.head != nil {
				if currentList.head.next == nil {
					FDelValue(currentList, currentList.head.key)
				} else {
					current := currentList.head
					for current.next.next != nil {
						current = current.next
					}
					FDelValue(currentList, current.next.key)
				}
			}
		case "V":
			value := strings.Join(args[1:], " ")
			FDelValue(currentList, value)
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			FDelAt(currentList, index)
		}

	case "FGET":
		if currentList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		switch position {
		case "F":
			if currentList.head != nil {
				fmt.Printf("Первый элемент: %s\n", currentList.head.key)
			}
		case "B":
			if currentList.head != nil {
				current := currentList.head
				for current.next != nil {
					current = current.next
				}
				fmt.Printf("Последний элемент: %s\n", current.key)
			}
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			value := FGetIndex(currentList, index)
			if value != "" {
				fmt.Printf("Элемент по индексу %d: %s\n", index, value)
			}
		}

	case "FFIND":
		if currentList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано значение для поиска")
			return
		}

		value := strings.Join(args, " ")
		result := FGetValue(currentList, value)
		if result != "" {
			fmt.Printf("Значение найдено: %s\n", result)
		}

	case "FPRINT":
		if currentList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		OutputSL(currentList)

	case "FSAVE":
		if currentList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		saveListToFile(currentList, args[0])

	case "FLOAD":
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		if currentList == nil {
			currentList = &SingleLL{}
		}
		loadListFromFile(currentList, args[0])

	// =========================== ДВУСВЯЗНЫЙ СПИСОК ========================
	case "LCREATE":
		if currentDList != nil {
			DLDelAll(currentDList)
		}
		currentDList = &DoubleList{}
		CreateDL(currentDList)
		fmt.Println("Двусвязный список создан")

	case "LPUSH":
		if currentDList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		value := strings.Join(args[1:], " ")

		switch position {
		case "F":
			DLPushFront(currentDList, value)
		case "B":
			DLPushBack(currentDList, value)
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			DLPushAt(currentDList, index, value)
		}
		fmt.Println("Элемент добавлен")

	case "LDEL":
		if currentDList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		switch position {
		case "F":
			DLDelFront(currentDList)
		case "B":
			DLDelBack(currentDList)
		case "V":
			value := strings.Join(args[1:], " ")
			DLDelValue(currentDList, value)
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			DLDelAt(currentDList, index)
		}
		fmt.Println("Элемент удален")

	case "LGET":
		if currentDList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Недостаточно аргументов")
			return
		}

		position := args[0]
		switch position {
		case "F":
			value := DLGetFront(currentDList)
			if value != "" {
				fmt.Printf("Первый элемент: %s\n", value)
			}
		case "B":
			value := DLGetBack(currentDList)
			if value != "" {
				fmt.Printf("Последний элемент: %s\n", value)
			}
		default:
			index, err := strconv.Atoi(position)
			if err != nil {
				fmt.Println("Ошибка: Неверный индекс")
				return
			}
			value := DLGetAt(currentDList, index)
			if value != "" {
				fmt.Printf("Элемент по индексу %d: %s\n", index, value)
			}
		}

	case "LPRINT":
		if currentDList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) > 0 && args[0] == "B" {
			RevOutputDL(currentDList)
		} else {
			OutputDL(currentDList)
		}

	case "LSAVE":
		if currentDList == nil {
			fmt.Println("Ошибка: Список не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		saveDoubleListToFile(currentDList, args[0])

	case "LLOAD":
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		if currentDList == nil {
			currentDList = &DoubleList{}
		}
		loadDoubleListFromFile(currentDList, args[0])

	// =========================== СТЕК =====================================
	case "SCREATE":
		if currentStack != nil {
			SDelAll(currentStack)
		}
		currentStack = &Stack{}
		CreateS(currentStack)
		fmt.Println("Стек создан")

	case "SPUSH":
		if currentStack == nil {
			fmt.Println("Ошибка: Стек не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано значение")
			return
		}
		value := strings.Join(args, " ")
		SPush(currentStack, value)
		fmt.Println("Элемент добавлен в стек")

	case "SPOP":
		if currentStack == nil {
			fmt.Println("Ошибка: Стек не создан")
			return
		}
		value := SPop(currentStack)
		if value != "" {
			fmt.Printf("Удален элемент: %s\n", value)
		}

	case "STOP":
		if currentStack == nil {
			fmt.Println("Ошибка: Стек не создан")
			return
		}
		if currentStack.size > 0 {
			fmt.Printf("Верхний элемент: %s\n", currentStack.data[currentStack.size-1])
		}

	case "SPRINT":
		if currentStack == nil {
			fmt.Println("Ошибка: Стек не создан")
			return
		}
		OutputS(currentStack)

	case "SSAVE":
		if currentStack == nil {
			fmt.Println("Ошибка: Стек не создан")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		saveStackToFile(currentStack, args[0])

	case "SLOAD":
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		if currentStack == nil {
			currentStack = &Stack{}
		}
		loadStackFromFile(currentStack, args[0])

	// =========================== ОЧЕРЕДЬ ==================================
	case "QCREATE":
		if currentQueue != nil {
			QDelAll(currentQueue)
		}
		currentQueue = &Queue{}
		CreateQ(currentQueue)
		fmt.Println("Очередь создана")

	case "QPUSH":
		if currentQueue == nil {
			fmt.Println("Ошибка: Очередь не создана")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано значение")
			return
		}
		value := strings.Join(args, " ")
		QPush(currentQueue, value)
		fmt.Println("Элемент добавлен в очередь")

	case "QPOP":
		if currentQueue == nil {
			fmt.Println("Ошибка: Очередь не создана")
			return
		}
		QPop(currentQueue)
		fmt.Println("Элемент удален из очереди")

	case "QINDEX":
		if currentQueue == nil {
			fmt.Println("Ошибка: Очередь не создана")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указан индекс")
			return
		}
		index, err := strconv.Atoi(args[0])
		if err != nil {
			fmt.Println("Ошибка: Неверный индекс")
			return
		}
		value := QGetIndex(currentQueue, index)
		if value != "" {
			fmt.Printf("Queue [%d]: %s\n", index, value)
		}

	case "QPRINT":
		if currentQueue == nil {
			fmt.Println("Ошибка: Очередь не создана")
			return
		}
		OutputQ(currentQueue)

	case "QSAVE":
		if currentQueue == nil {
			fmt.Println("Ошибка: Очередь не создана")
			return
		}
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		saveQueueToFile(currentQueue, args[0])

	case "QLOAD":
		if len(args) < 1 {
			fmt.Println("Ошибка: Не указано имя файла")
			return
		}
		if currentQueue == nil {
			currentQueue = &Queue{}
		}
		loadQueueFromFile(currentQueue, args[0])

	// =========================== HELP =====================================
	case "HELP":
		if len(args) == 0 {
			fmt.Println("Используйте HELP M|F|L|S|Q - показать справку по конкретной структуре")
			return
		}

		switch args[0] {
		case "MAIN":
			printMain()
		case "ALL":
			printAll()
		case "M":
			printM()
		case "F":
			printF()
		case "L":
			printL()
		case "S":
			printS()
		case "Q":
			printQ()
		default:
			fmt.Println("Неизвестный тип справки")
		}

	// =========================== CLEAR ====================================
	case "CLEAR":
		currentArray = nil
		currentList = nil
		currentDList = nil
		currentStack = nil
		currentQueue = nil
		fmt.Println("Все структуры данных очищены")

	// =========================== EXIT =====================================
	case "EXIT":
		fmt.Println("Выход из программы...")
		os.Exit(0)

	default:
		fmt.Printf("Неизвестная команда: %s. Введите HELP для справки.\n", cmd)
	}
}

func saveArrayToFile(arr *Array, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка создания файла:", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString("ARRAY_SIZE:" + strconv.Itoa(arr.size) + "\n")
	for i := 0; i < arr.size; i++ {
		writer.WriteString(arr.data[i] + "\n")
	}
	writer.Flush()
	fmt.Printf("Массив сохранен в %s\n", filename)
}

func loadArrayFromFile(arr *Array, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла:", err)
		return
	}
	defer file.Close()

	// Очищаем текущий массив
	if arr.data != nil {
		arr.data = nil
	}
	arr.size = 0
	arr.capacity = 0

	MCreate(arr)

	scanner := bufio.NewScanner(file)
	firstLine := true
	
	for scanner.Scan() {
		line := scanner.Text()
		if firstLine {
			firstLine = false
			continue // Пропускаем строку с размером
		}
		if line != "" {
			MPushBack(arr, line)
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	fmt.Printf("Массив загружен из %s\n", filename)
}

func saveQueueToFile(q *Queue, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка создания файла:", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString("QUEUE_SIZE:" + strconv.Itoa(q.size) + "\n")
	
	current := q.front
	for current != nil {
		writer.WriteString(current.key + "\n")
		current = current.next
	}
	
	writer.Flush()
	fmt.Printf("Очередь сохранена в %s\n", filename)
}

func loadQueueFromFile(q *Queue, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла:", err)
		return
	}
	defer file.Close()

	// Очищаем текущую очередь
	if q.front != nil {
		QDelAll(q)
	}
	CreateQ(q)

	scanner := bufio.NewScanner(file)
	firstLine := true
	
	for scanner.Scan() {
		line := scanner.Text()
		if firstLine {
			firstLine = false
			continue // Пропускаем строку с размером
		}
		if line != "" {
			QPush(q, line)
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	fmt.Printf("Очередь загружена из %s\n", filename)
}

func saveStackToFile(st *Stack, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка создания файла:", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString("STACK_SIZE:" + strconv.Itoa(st.size) + "\n")
	
	// Создаем временный стек для сохранения в правильном порядке
	tempStack := &Stack{}
	CreateS(tempStack)
	tempStack.size = st.size
	
	// Копируем данные в обратном порядке
	for i := st.size - 1; i >= 0; i-- {
		writer.WriteString(st.data[i] + "\n")
	}
	
	writer.Flush()
	fmt.Printf("Стек сохранен в %s\n", filename)
}

func loadStackFromFile(st *Stack, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла:", err)
		return
	}
	defer file.Close()

	// Очищаем текущий стек
	if st.data != nil {
		SDelAll(st)
	}
	CreateS(st)

	scanner := bufio.NewScanner(file)
	firstLine := true
	
	// Временный слайс для хранения данных в правильном порядке
	var tempData []string
	
	for scanner.Scan() {
		line := scanner.Text()
		if firstLine {
			firstLine = false
			continue // Пропускаем строку с размером
		}
		if line != "" {
			tempData = append(tempData, line)
		}
	}

	// Загружаем данные в стек в обратном порядке
	for i := len(tempData) - 1; i >= 0; i-- {
		SPush(st, tempData[i])
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	fmt.Printf("Стек загружен из %s\n", filename)
}

func saveListToFile(ls *SingleLL, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка создания файла:", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString("LIST_SIZE:" + strconv.Itoa(ls.size) + "\n")
	
	current := ls.head
	for current != nil {
		writer.WriteString(current.key + "\n")
		current = current.next
	}
	
	writer.Flush()
	fmt.Printf("Список сохранен в %s\n", filename)
}

func loadListFromFile(ls *SingleLL, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла:", err)
		return
	}
	defer file.Close()

	// Очищаем текущий список
	if ls.head != nil {
		FDelList(ls)
	}

	scanner := bufio.NewScanner(file)
	firstLine := true
	
	for scanner.Scan() {
		line := scanner.Text()
		if firstLine {
			firstLine = false
			continue // Пропускаем строку с размером
		}
		if line != "" {
			FPushBack(ls, line)
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	fmt.Printf("Список загружен из %s\n", filename)
}

func saveDoubleListToFile(ls *DoubleList, filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка создания файла:", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.WriteString("DLIST_SIZE:" + strconv.Itoa(ls.size) + "\n")
	
	current := ls.head
	for i := 0; current != nil && i < ls.size; i++ {
		writer.WriteString(current.key + "\n")
		current = current.next
	}
	
	writer.Flush()
	fmt.Printf("Двусвязный список сохранен в %s\n", filename)
}

func loadDoubleListFromFile(ls *DoubleList, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Ошибка открытия файла:", err)
		return
	}
	defer file.Close()

	// Очищаем текущий список
	if ls.head != nil {
		DLDelAll(ls)
	}

	scanner := bufio.NewScanner(file)
	firstLine := true
	
	for scanner.Scan() {
		line := scanner.Text()
		if firstLine {
			firstLine = false
			continue // Пропускаем строку с размером
		}
		if line != "" {
			DLPushBack(ls, line)
		}
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Ошибка чтения файла:", err)
		return
	}

	fmt.Printf("Двусвязный список загружен из %s\n", filename)
}

// Функции помощи
func printMain() {
	fmt.Println("\n=== СПРАВКА ПО КОМАНДАМ ===")
	fmt.Println("\nОБЩИЕ КОМАНДЫ:")
	fmt.Println("  HELP ALL - показать справку по всем структурам")
	fmt.Println("  HELP M|F|L|S|Q - показать справку по конкретной структуре")
	fmt.Println("  CLEAR - очистить все структуры")
	fmt.Println("  EXIT - выход из программы")
	fmt.Println("=================================")
}

func printAll() {
	fmt.Println("\n=== СПРАВКА ПО КОМАНДАМ ===")
	fmt.Println("\nОСНОВНЫЕ КОМАНДЫ:")
	printM()
	printF()
	printL()
	printS()
	printQ()
	fmt.Println("=================================")
}

func printM() {
	fmt.Println("МАССИВ (M):")
	fmt.Println("  MCREATE - создать массив")
	fmt.Println("  MPUSH F|B|index \"value\" - добавить элемент")
	fmt.Println("  MDEL F|B|V|index - удалить элемент")
	fmt.Println("  MGET F|B|index - получить элемент")
	fmt.Println("  MFIND \"value\" - найти элемент")
	fmt.Println("  MSIZE - получить размер")
	fmt.Println("  MPRINT - вывести массив")
	fmt.Println("  MREPLACE index value - заменить значение по индексу")
	fmt.Println("  MSAVE filename - сохранить в файл")
	fmt.Println("  MLOAD filename - загрузить из файла")
}

func printF() {
	fmt.Println("\nОДНОСВЯЗНЫЙ СПИСОК (F):")
	fmt.Println("  FCREATE - создать список")
	fmt.Println("  FPUSH F|B|index \"value\" - добавить элемент")
	fmt.Println("  FDEL F|B|V|index - удалить элемент")
	fmt.Println("  FGET F|B|index - получить элемент")
	fmt.Println("  FFIND \"value\" - найти элемент")
	fmt.Println("  FPRINT - вывести список")
	fmt.Println("  FSAVE filename - сохранить в файл")
	fmt.Println("  FLOAD filename - загрузить из файла")
}

func printL() {
	fmt.Println("\nДВУСВЯЗНЫЙ СПИСОК (L):")
	fmt.Println("  LCREATE - создать список")
	fmt.Println("  LPUSH F|B|index \"value\" - добавить элемент")
	fmt.Println("  LDEL F|B|V|index \"target\" - удалить элемент")
	fmt.Println("  LGET F|B|index - получить элемент")
	fmt.Println("  LPRINT F|B - вывести список")
	fmt.Println("  LSAVE filename - сохранить в файл")
	fmt.Println("  LLOAD filename - загрузить из файла")
}

func printS() {
	fmt.Println("\nСТЕК (S):")
	fmt.Println("  SCREATE - создать стек")
	fmt.Println("  SPUSH \"value\" - добавить элемент")
	fmt.Println("  SPOP - удалить элемент")
	fmt.Println("  STOP - посмотреть верхний элемент")
	fmt.Println("  SPRINT - вывести стек")
	fmt.Println("  SSAVE filename - сохранить в файл")
	fmt.Println("  SLOAD filename - загрузить из файла")
}

func printQ() {
	fmt.Println("\nОЧЕРЕДЬ (Q):")
	fmt.Println("  QCREATE - создать очередь")
	fmt.Println("  QPUSH \"value\" - добавить элемент")
	fmt.Println("  QPOP - удалить элемент")
	fmt.Println("  QINDEX \"value\" - посмотреть элемент по индексу")
	fmt.Println("  QPRINT - вывести очередь")
	fmt.Println("  QSAVE filename - сохранить в файл")
	fmt.Println("  QLOAD filename - загрузить из файла")
}
