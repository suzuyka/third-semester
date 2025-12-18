package main

import (
	"fmt"
	"strconv"
	"strings"
)

// Array структура (динамический массив)
type Array struct {
	data []int
}

func (a *Array) Push(value int) {
	a.data = append(a.data, value)
}

func (a *Array) Insert(index int, value int) bool {
	if index < 0 || index > len(a.data) {
		fmt.Println("Ошибка: индекс вне диапазона")
		return false
	}
	a.data = append(a.data[:index], append([]int{value}, a.data[index:]...)...)
	return true
}

func (a *Array) Get(index int) int {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Ошибка: индекс вне диапазона")
		return -1
	}
	return a.data[index]
}

func (a *Array) Set(index int, value int) bool {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Ошибка: индекс вне диапазона")
		return false
	}
	a.data[index] = value
	return true
}

func (a *Array) Delete(index int) bool {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Ошибка: индекс вне диапазона")
		return false
	}
	a.data = append(a.data[:index], a.data[index+1:]...)
	return true
}

func (a *Array) Print() {
	for _, v := range a.data {
		fmt.Print(v, " ")
	}
	fmt.Println()
}

// Обработка команды для массива
func handleArrayCommand(array *Array, parts []string) {
	if len(parts) < 1 {
		fmt.Println("Ошибка: пустая команда для массива")
		return
	}

	switch parts[0] {
		case "MPUSH":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			array.Push(val)
			fmt.Println("-> добавлен", val)

		case "MINDEX":
			if len(parts) < 3 {
				fmt.Println("Ошибка: укажите индекс и значение")
				return
			}
			idx, err1 := strconv.Atoi(parts[1])
			val, err2 := strconv.Atoi(parts[2])
			if err1 != nil || err2 != nil {
				fmt.Println("Ошибка: неверные параметры")
				return
			}
			if array.Insert(idx, val) {
				fmt.Println("-> вставлен", val, "по индексу", idx)
			}

		case "MGET":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите индекс")
				return
			}
			idx, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверный индекс")
				return
			}
			val := array.Get(idx)
			fmt.Println("->", val)

		case "MSET":
			if len(parts) < 3 {
				fmt.Println("Ошибка: укажите индекс и новое значение")
				return
			}
			idx, err1 := strconv.Atoi(parts[1])
			val, err2 := strconv.Atoi(parts[2])
			if err1 != nil || err2 != nil {
				fmt.Println("Ошибка: неверные параметры")
				return
			}
			if array.Set(idx, val) {
				fmt.Println("-> элемент по индексу", idx, "заменён на", val)
			}

		case "MDEL":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите индекс")
				return
			}
			idx, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверный индекс")
				return
			}
			if array.Delete(idx) {
				fmt.Println("-> удалён элемент по индексу", idx)
			} else {
				fmt.Println("Удаление не выполнено (индекс вне диапазона)")
			}

		case "PRINTM":
			fmt.Print("-> ")
			array.Print()

		default:
			fmt.Println("Неизвестная команда:", parts[0])
	}
}

// Обработка команд для односвязного списка
func handleSListCommand(list *SinglyLinkedList, parts []string) {
	if len(parts) < 1 {
		fmt.Println("Ошибка: пустая команда для списка")
		return
	}

	switch parts[0] {
		case "FPUSH":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			list.PushBack(val)
			fmt.Println("-> добавлен", val)

		case "FPUSHFRONT":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			list.PushFront(val)
			fmt.Println("-> добавлен", val, "в голову")

		case "FINSERTBEFORE":
			if len(parts) < 3 {
				fmt.Println("Ошибка: укажите target и value")
				return
			}
			target, _ := strconv.Atoi(parts[1])
			val, _ := strconv.Atoi(parts[2])
			if list.InsertBefore(target, val) {
				fmt.Println("-> вставлен", val, "перед", target)
			} else {
				fmt.Println("Элемент", target, "не найден")
			}

		case "FINSERTAFTER":
			if len(parts) < 3 {
				fmt.Println("Ошибка: укажите target и value")
				return
			}
			target, _ := strconv.Atoi(parts[1])
			val, _ := strconv.Atoi(parts[2])
			if list.InsertAfter(target, val) {
				fmt.Println("-> вставлен", val, "после", target)
			} else {
				fmt.Println("Элемент", target, "не найден")
			}

		case "FDEL":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, _ := strconv.Atoi(parts[1])
			if list.Delete(val) {
				fmt.Println("-> удалён", val)
			} else {
				fmt.Println("Элемент", val, "не найден")
			}

		case "FGET":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите индекс")
				return
			}
			idx, _ := strconv.Atoi(parts[1])
			val := list.Get(idx)
			fmt.Println("->", val)

		case "FCONTAINS":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, _ := strconv.Atoi(parts[1])
			if list.Contains(val) {
				fmt.Println("-> найден", val)
			} else {
				fmt.Println("-> не найден", val)
			}

		case "FDELFRONT":
			if list.DelFront() {
				fmt.Println("-> удалён первый элемент")
			} else {
				fmt.Println("Ошибка: список пуст")
			}

		case "FDELBACK":
			if list.DelBack() {
				fmt.Println("-> удалён последний элемент")
			} else {
				fmt.Println("Ошибка: список пуст")
			}

		case "PRINTF":
			fmt.Print("-> ")
			list.Print()

		default:
			fmt.Println("Неизвестная команда:", parts[0])
	}
}

// Обработка команд двусвязного списка
func handleDListCommand(dlist *DoublyLinkedList, parts []string) {
	if len(parts) < 1 {
		fmt.Println("Ошибка: пустая команда для списка")
		return
	}

	switch parts[0] {
		case "LPUSH":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			dlist.PushBack(val)
			fmt.Println("-> добавлен", val)

		case "LPUSHFRONT":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			dlist.PushFront(val)
			fmt.Println("-> добавлен", val, "в голову")

		case "LINSERTBEFORE":
			if len(parts) < 3 {
				fmt.Println("Ошибка: укажите target и значение")
				return
			}
			target, err1 := strconv.Atoi(parts[1])
			val, err2 := strconv.Atoi(parts[2])
			if err1 != nil || err2 != nil {
				fmt.Println("Ошибка: неверные параметры")
				return
			}
			if dlist.InsertBefore(target, val) {
				fmt.Println("-> вставлен", val, "перед", target)
			} else {
				fmt.Println("Элемент", target, "не найден")
			}

		case "LINSERTAFTER":
			if len(parts) < 3 {
				fmt.Println("Ошибка: укажите target и значение")
				return
			}
			target, err1 := strconv.Atoi(parts[1])
			val, err2 := strconv.Atoi(parts[2])
			if err1 != nil || err2 != nil {
				fmt.Println("Ошибка: неверные параметры")
				return
			}
			if dlist.InsertAfter(target, val) {
				fmt.Println("-> вставлен", val, "после", target)
			} else {
				fmt.Println("Элемент", target, "не найден")
			}

		case "LDEL":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			if dlist.Delete(val) {
				fmt.Println("-> удалён", val)
			} else {
				fmt.Println("Элемент", val, "не найден")
			}

		case "LGET":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите индекс")
				return
			}
			idx, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверный индекс")
				return
			}
			val := dlist.Get(idx)
			fmt.Println("->", val)

		case "LCONTAINS":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			if dlist.Contains(val) {
				fmt.Println("-> найден", val)
			} else {
				fmt.Println("->", val, "не найден")
			}

		case "LDELFRONT":
			if dlist.DelFront() {
				fmt.Println("-> удалён первый элемент")
			} else {
				fmt.Println("Ошибка: список пуст")
			}

		case "LDELBACK":
			if dlist.DelBack() {
				fmt.Println("-> удалён последний элемент")
			} else {
				fmt.Println("Ошибка: список пуст")
			}

		case "PRINTL":
			fmt.Print("-> ")
			dlist.Print()

		default:
			fmt.Println("Неизвестная команда:", parts[0])
	}
}

// Обработка команд для хеш-таблицы
func handleHashTableCommand(ht *HashTable, parts []string) {
	if len(parts) < 1 {
		fmt.Println("Ошибка: пустая команда для хеш-таблицы")
		return
	}

	switch parts[0] {
		case "HINSERT":
			if len(parts) < 3 {
				fmt.Println("Ошибка: укажите ключ и значение")
				return
			}
			key, err1 := strconv.Atoi(parts[1])
			value, err2 := strconv.Atoi(parts[2])
			if err1 != nil || err2 != nil {
				fmt.Println("Ошибка: неверные параметры")
				return
			}
			ht.Insert(key, value)
			fmt.Printf("-> вставлена пара (%d, %d)\n", key, value)

		case "HGET":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите ключ")
				return
			}
			key, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверный ключ")
				return
			}
			if value, ok := ht.Get(key); ok {
				fmt.Printf("-> ключ %d: значение %d\n", key, value)
			} else {
				fmt.Printf("-> ключ %d не найден\n", key)
			}

		case "HDEL":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите ключ")
				return
			}
			key, err := strconv.Atoi(parts[1])
			if err != nil {
				fmt.Println("Ошибка: неверный ключ")
				return
			}
			if ht.Remove(key) {
				fmt.Printf("-> ключ %d удалён\n", key)
			} else {
				fmt.Printf("-> ключ %d не найден\n", key)
			}

		case "HCLEAR":
			ht.Clear()
			fmt.Println("-> хеш-таблица очищена")

		case "PRINTH":
			fmt.Println("-> Хеш-таблица:")
			ht.Print()

		case "HSETTYPE":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите тип хеширования")
				return
			}
			switch parts[1] {
				case "DOUBLE":
					ht.htype = DOUBLE_HASHING
					fmt.Println("-> установлен тип: DOUBLE_HASHING")
				case "CUCKOO":
					ht.htype = CUCKOO_HASHING
					fmt.Println("-> установлен тип: CUCKOO_HASHING")
				case "FOLDING":
					ht.htype = FOLDING_HASHING
					fmt.Println("-> установлен тип: FOLDING_HASHING")
				default:
					fmt.Println("Ошибка: неверный тип. Доступно: DOUBLE, CUCKOO, FOLDING")
			}

				default:
					fmt.Println("Неизвестная команда:", parts[0])
	}
}

// Разбор строки команды
func executeCommand(query string) {
	parts := strings.Fields(query)
	if len(parts) == 0 {
		fmt.Println("Ошибка: пустая команда")
		return
	}

	// Определяем тип структуры по первой команде
	switch {
		// Команды для массива
		case parts[0] == "MPUSH" || parts[0] == "MINDEX" || parts[0] == "MGET" ||
		parts[0] == "MSET" || parts[0] == "MDEL" || parts[0] == "PRINTM":
		handleArrayCommand(&globalArray, parts)

		// Команды для односвязного списка
		case parts[0] == "FPUSH" || parts[0] == "FPUSHFRONT" || parts[0] == "FINSERTBEFORE" ||
		parts[0] == "FINSERTAFTER" || parts[0] == "FDEL" || parts[0] == "FGET" ||
		parts[0] == "FCONTAINS" || parts[0] == "FDELFRONT" || parts[0] == "FDELBACK" ||
		parts[0] == "PRINTF":
		handleSListCommand(&globalSList, parts)

		// Команды для двусвязного списка
		case parts[0] == "LPUSH" || parts[0] == "LPUSHFRONT" || parts[0] == "LINSERTBEFORE" ||
		parts[0] == "LINSERTAFTER" || parts[0] == "LDEL" || parts[0] == "LGET" ||
		parts[0] == "LCONTAINS" || parts[0] == "LDELFRONT" || parts[0] == "LDELBACK" ||
		parts[0] == "PRINTL":
		handleDListCommand(&globalDList, parts)

		// Команды для стека
		case parts[0] == "SPUSH" || parts[0] == "SPOP" || parts[0] == "PRINTS":
			handleStackCommand(&globalStack, parts)

			// Команды для очереди
		case parts[0] == "QPUSH" || parts[0] == "QPOP" || parts[0] == "PRINTQ":
			handleQueueCommand(&globalQueue, parts)

			// Команды для хеш-таблицы
			case parts[0] == "HINSERT" || parts[0] == "HGET" || parts[0] == "HDEL" ||
			parts[0] == "HCLEAR" || parts[0] == "PRINTH" || parts[0] == "HSETTYPE":
			handleHashTableCommand(globalHashTable, parts)

			// Команды сериализации
			case parts[0] == "SAVE_BINARY" || parts[0] == "LOAD_BINARY" ||
			parts[0] == "SAVE_TEXT" || parts[0] == "LOAD_TEXT":
			handleSerializationCommand(parts)

		default:
			fmt.Println("Неизвестная команда:", parts[0])
	}
}

// Обработка команд сериализации
func handleSerializationCommand(parts []string) {
	if len(parts) < 2 {
		fmt.Println("Ошибка: укажите имя файла")
		return
	}

	filename := parts[1]

	// Определяем тип структуры
	if strings.Contains(filename, "array") || strings.HasSuffix(filename, "_array.") {
		// Для массива
		switch parts[0] {
			case "SAVE_BINARY":
				if err := globalArray.SerializeBinary(filename); err != nil {
					fmt.Printf("Ошибка сохранения массива: %v\n", err)
				} else {
					fmt.Printf("-> массив сохранен в бинарный файл %s\n", filename)
				}
			case "LOAD_BINARY":
				if err := globalArray.DeserializeBinary(filename); err != nil {
					fmt.Printf("Ошибка загрузки массива: %v\n", err)
				} else {
					fmt.Printf("-> массив загружен из бинарного файла %s\n", filename)
				}
			case "SAVE_TEXT":
				if err := globalArray.SerializeText(filename); err != nil {
					fmt.Printf("Ошибка сохранения массива: %v\n", err)
				} else {
					fmt.Printf("-> массив сохранен в текстовый файл %s\n", filename)
				}
			case "LOAD_TEXT":
				if err := globalArray.DeserializeText(filename); err != nil {
					fmt.Printf("Ошибка загрузки массива: %v\n", err)
				} else {
					fmt.Printf("-> массив загружен из текстового файла %s\n", filename)
				}
		}
	} else if strings.Contains(filename, "slist") || strings.Contains(filename, "singly") {
		// Для односвязного списка
		switch parts[0] {
			case "SAVE_BINARY":
				if err := globalSList.SerializeBinary(filename); err != nil {
					fmt.Printf("Ошибка сохранения односвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> односвязный список сохранен в бинарный файл %s\n", filename)
				}
			case "LOAD_BINARY":
				if err := globalSList.DeserializeBinary(filename); err != nil {
					fmt.Printf("Ошибка загрузки односвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> односвязный список загружен из бинарного файла %s\n", filename)
				}
			case "SAVE_TEXT":
				if err := globalSList.SerializeText(filename); err != nil {
					fmt.Printf("Ошибка сохранения односвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> односвязный список сохранен в текстовый файл %s\n", filename)
				}
			case "LOAD_TEXT":
				if err := globalSList.DeserializeText(filename); err != nil {
					fmt.Printf("Ошибка загрузки односвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> односвязный список загружен из текстового файла %s\n", filename)
				}
		}
	} else if strings.Contains(filename, "dlist") || strings.Contains(filename, "doubly") {
		// Для двусвязного списка
		switch parts[0] {
			case "SAVE_BINARY":
				if err := globalDList.SerializeBinary(filename); err != nil {
					fmt.Printf("Ошибка сохранения двусвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> двусвязный список сохранен в бинарный файл %s\n", filename)
				}
			case "LOAD_BINARY":
				if err := globalDList.DeserializeBinary(filename); err != nil {
					fmt.Printf("Ошибка загрузки двусвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> двусвязный список загружен из бинарного файла %s\n", filename)
				}
			case "SAVE_TEXT":
				if err := globalDList.SerializeText(filename); err != nil {
					fmt.Printf("Ошибка сохранения двусвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> двусвязный список сохранен в текстовый файл %s\n", filename)
				}
			case "LOAD_TEXT":
				if err := globalDList.DeserializeText(filename); err != nil {
					fmt.Printf("Ошибка загрузки двусвязного списка: %v\n", err)
				} else {
					fmt.Printf("-> двусвязный список загружен из текстового файла %s\n", filename)
				}
		}
	} else if strings.Contains(filename, "stack") {
		// Для стека
		switch parts[0] {
			case "SAVE_BINARY":
				if err := globalStack.SerializeBinary(filename); err != nil {
					fmt.Printf("Ошибка сохранения стека: %v\n", err)
				} else {
					fmt.Printf("-> стек сохранен в бинарный файл %s\n", filename)
				}
			case "LOAD_BINARY":
				if err := globalStack.DeserializeBinary(filename); err != nil {
					fmt.Printf("Ошибка загрузки стека: %v\n", err)
				} else {
					fmt.Printf("-> стек загружен из бинарного файла %s\n", filename)
				}
			case "SAVE_TEXT":
				if err := globalStack.SerializeText(filename); err != nil {
					fmt.Printf("Ошибка сохранения стека: %v\n", err)
				} else {
					fmt.Printf("-> стек сохранен в текстовый файл %s\n", filename)
				}
			case "LOAD_TEXT":
				if err := globalStack.DeserializeText(filename); err != nil {
					fmt.Printf("Ошибка загрузки стека: %v\n", err)
				} else {
					fmt.Printf("-> стек загружен из текстового файла %s\n", filename)
				}
		}
	} else if strings.Contains(filename, "queue") {
		// Для очереди
		switch parts[0] {
			case "SAVE_BINARY":
				if err := globalQueue.SerializeBinary(filename); err != nil {
					fmt.Printf("Ошибка сохранения очереди: %v\n", err)
				} else {
					fmt.Printf("-> очередь сохранена в бинарный файл %s\n", filename)
				}
			case "LOAD_BINARY":
				if err := globalQueue.DeserializeBinary(filename); err != nil {
					fmt.Printf("Ошибка загрузки очереди: %v\n", err)
				} else {
					fmt.Printf("-> очередь загружена из бинарного файла %s\n", filename)
				}
			case "SAVE_TEXT":
				if err := globalQueue.SerializeText(filename); err != nil {
					fmt.Printf("Ошибка сохранения очереди: %v\n", err)
				} else {
					fmt.Printf("-> очередь сохранена в текстовый файл %s\n", filename)
				}
			case "LOAD_TEXT":
				if err := globalQueue.DeserializeText(filename); err != nil {
					fmt.Printf("Ошибка загрузки очереди: %v\n", err)
				} else {
					fmt.Printf("-> очередь загружена из текстового файла %s\n", filename)
				}
		}
	} else if strings.Contains(filename, "hash") || strings.Contains(filename, "htable") {
		// Для хеш-таблицы
		switch parts[0] {
			case "SAVE_BINARY":
				if err := globalHashTable.SerializeBinary(filename); err != nil {
					fmt.Printf("Ошибка сохранения хеш-таблицы: %v\n", err)
				} else {
					fmt.Printf("-> хеш-таблица сохранена в бинарный файл %s\n", filename)
				}
			case "LOAD_BINARY":
				if err := globalHashTable.DeserializeBinary(filename); err != nil {
					fmt.Printf("Ошибка загрузки хеш-таблицы: %v\n", err)
				} else {
					fmt.Printf("-> хеш-таблица загружена из бинарного файла %s\n", filename)
				}
			case "SAVE_TEXT":
				if err := globalHashTable.SerializeText(filename); err != nil {
					fmt.Printf("Ошибка сохранения хеш-таблицы: %v\n", err)
				} else {
					fmt.Printf("-> хеш-таблица сохранена в текстовый файл %s\n", filename)
				}
			case "LOAD_TEXT":
				if err := globalHashTable.DeserializeText(filename); err != nil {
					fmt.Printf("Ошибка загрузки хеш-таблицы: %v\n", err)
				} else {
					fmt.Printf("-> хеш-таблица загружена из текстового файла %s\n", filename)
				}
		}
	} else {
		fmt.Println("Ошибка: не удалось определить тип структуры для файла", filename)
		fmt.Println("Используйте имена файлов с указанием типа: array_, slist_, dlist_, stack_, queue_, hash_")
	}
}

// Глобальная структура
var globalArray Array
var globalSList SinglyLinkedList
var globalDList DoublyLinkedList
var globalStack Stack
var globalQueue Queue
var globalHashTable = NewHashTable(11, DOUBLE_HASHING)

// ResetGlobals сбрасывает глобальные переменные для тестов
func ResetGlobals() {
	globalArray = Array{}
	globalSList = SinglyLinkedList{}
	globalDList = DoublyLinkedList{}
	globalStack = Stack{}
	globalQueue = Queue{}
	globalHashTable = NewHashTable(11, DOUBLE_HASHING)
}
