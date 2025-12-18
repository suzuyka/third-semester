package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

// =====================
//        Массив
// =====================

func saveArrayToFile(filename string, array *Array) {
	f, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка записи файла:", err)
		return
	}
	defer f.Close()

	for _, v := range array.data {
		fmt.Fprintln(f, v)
	}
}

func loadArrayFromFile(filename string, array *Array) {
	array.data = []int{}
	f, err := os.Open(filename)
	if err != nil {
		return // файл может не существовать
	}
	defer f.Close()

	var val int
	for {
		_, err := fmt.Fscan(f, &val)
		if err != nil {
			break
		}
		array.data = append(array.data, val)
	}
}

// =====================
//  Односвязный список
// =====================

// Сохранение списка в файл
func saveSinglyListToFile(filename string, list *SinglyLinkedList) {
	f, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка записи файла:", err)
		return
	}
	defer f.Close()

	for _, v := range list.ToSlice() {
		fmt.Fprintln(f, v)
	}
}

// Загрузка списка из файла
func loadSinglyListFromFile(filename string, list *SinglyLinkedList) {
	list.head = nil
	f, err := os.Open(filename)
	if err != nil {
		return // файл может не существовать
	}
	defer f.Close()

	var val int
	for {
		_, err := fmt.Fscan(f, &val)
		if err != nil {
			break
		}
		list.PushBack(val)
	}
}

// =====================
//   Двусвязный список
// =====================

// Сохранение списка в файл
func loadDListFromFile(filename string, list *DoublyLinkedList) {
	file, err := os.ReadFile(filename)
	if err != nil {
		return // если файла нет, просто не загружаем
	}
	list.head, list.tail = nil, nil // очистка списка перед загрузкой
	lines := strings.Split(strings.TrimSpace(string(file)), "\n")
	for _, line := range lines {
		if line == "" {
			continue
		}
		val, err := strconv.Atoi(line)
		if err == nil {
			list.PushBack(val)
		}
	}
}

// Загрузка списка из файла
func saveDListToFile(filename string, list *DoublyLinkedList) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Ошибка сохранения:", err)
		return
	}
	defer file.Close()

	curr := list.head
	for curr != nil {
		fmt.Fprintln(file, curr.data)
		curr = curr.next
	}
}

// ==================== Работа со стеком ====================
func saveStackToFile(filename string, s *Stack) {
	lines := []string{}
	for _, v := range s.toSlice() {
		lines = append(lines, strconv.Itoa(v))
	}
	data := strings.Join(lines, "\n")
	_ = os.WriteFile(filename, []byte(data), 0644)
}

func loadStackFromFile(filename string, s *Stack) {
	bytes, err := os.ReadFile(filename)
	if err != nil {
		s.top = nil
		return
	}
	lines := strings.Split(strings.TrimSpace(string(bytes)), "\n")
	data := []int{}
	for _, line := range lines {
		if line == "" {
			continue
		}
		val, err := strconv.Atoi(line)
		if err == nil {
			data = append(data, val)
		}
	}
	s.fromSlice(data)
}

// ==================== Работа с очередью ====================
func saveQueueToFile(filename string, q *Queue) {
	lines := []string{}
	for _, v := range q.toSlice() {
		lines = append(lines, strconv.Itoa(v))
	}
	data := strings.Join(lines, "\n")
	_ = os.WriteFile(filename, []byte(data), 0644)
}

func loadQueueFromFile(filename string, q *Queue) {
	bytes, err := os.ReadFile(filename)
	if err != nil {
		q.front, q.rear = nil, nil
		return
	}
	lines := strings.Split(strings.TrimSpace(string(bytes)), "\n")
	data := []int{}
	for _, line := range lines {
		if line == "" {
			continue
		}
		val, err := strconv.Atoi(line)
		if err == nil {
			data = append(data, val)
		}
	}
	q.fromSlice(data)
}


// =====================
//     Хеш-таблица
// =====================

// Сохранение хеш-таблицы в файл
func saveHashTableToFile(filename string, ht *HashTable) {
	data := strings.Join(ht.ToSlice(), "\n")
	_ = os.WriteFile(filename, []byte(data), 0644)
}

// Загрузка хеш-таблицы из файла
func loadHashTableFromFile(filename string, ht *HashTable) {
	bytes, err := os.ReadFile(filename)
	if err != nil {
		return // файл может не существовать
	}
	lines := strings.Split(strings.TrimSpace(string(bytes)), "\n")
	ht.FromSlice(lines)
}
