package main

import "fmt"

// Узел односвязного списка
type FNode struct {
	data int
	next *FNode
}

// Сам список
type SinglyLinkedList struct {
	head *FNode
}

// Добавление в хвост
func (l *SinglyLinkedList) PushBack(value int) {
	newNode := &FNode{data: value}
	if l.head == nil {
		l.head = newNode
		return
	}
	curr := l.head
	for curr.next != nil {
		curr = curr.next
	}
	curr.next = newNode
}

// Добавление в голову
func (l *SinglyLinkedList) PushFront(value int) {
	newNode := &FNode{data: value, next: l.head}
	l.head = newNode
}

// Вставка перед target
func (l *SinglyLinkedList) InsertBefore(target, value int) bool {
	if l.head == nil {
		return false
	}
	if l.head.data == target {
		l.PushFront(value)
		return true
	}
	curr := l.head
	for curr.next != nil && curr.next.data != target {
		curr = curr.next
	}
	if curr.next == nil {
		return false
	}
	newNode := &FNode{data: value, next: curr.next}
	curr.next = newNode
	return true
}

// Вставка после target
func (l *SinglyLinkedList) InsertAfter(target, value int) bool {
	curr := l.head
	for curr != nil && curr.data != target {
		curr = curr.next
	}
	if curr == nil {
		return false
	}
	newNode := &FNode{data: value, next: curr.next}
	curr.next = newNode
	return true
}

// Удаление по значению
func (l *SinglyLinkedList) Delete(value int) bool {
	if l.head == nil {
		return false
	}
	if l.head.data == value {
		l.head = l.head.next
		return true
	}
	curr := l.head
	for curr.next != nil && curr.next.data != value {
		curr = curr.next
	}
	if curr.next == nil {
		return false
	}
	curr.next = curr.next.next
	return true
}

// Получение по индексу
func (l *SinglyLinkedList) Get(index int) int {
	curr := l.head
	i := 0
	for curr != nil {
		if i == index {
			return curr.data
		}
		curr = curr.next
		i++
	}
	fmt.Println("Ошибка: индекс вне диапазона")
	return -1
}

// Поиск элемента
func (l *SinglyLinkedList) Contains(value int) bool {
	curr := l.head
	for curr != nil {
		if curr.data == value {
			return true
		}
		curr = curr.next
	}
	return false
}

// Вывод
func (l *SinglyLinkedList) Print() {
	curr := l.head
	for curr != nil {
		fmt.Print(curr.data, " ")
		curr = curr.next
	}
	fmt.Println()
}

// Преобразовать в срез (для записи в файл)
func (l *SinglyLinkedList) ToSlice() []int {
	var result []int
	curr := l.head
	for curr != nil {
		result = append(result, curr.data)
		curr = curr.next
	}
	// Возвращаем пустой срез вместо nil
	if result == nil {
		return []int{}
	}
	return result
}

// Восстановить список из среза
func (l *SinglyLinkedList) FromSlice(data []int) {
	l.head = nil
	for _, v := range data {
		l.PushBack(v)
	}
}

// Удаление из головы
func (l *SinglyLinkedList) DelFront() bool {
	if l.head == nil {
		return false
	}
	l.head = l.head.next
	return true
}

// Удаление из хвоста
func (l *SinglyLinkedList) DelBack() bool {
	if l.head == nil {
		return false
	}
	if l.head.next == nil {
		l.head = nil
		return true
	}
	curr := l.head
	for curr.next.next != nil {
		curr = curr.next
	}
	curr.next = nil
	return true
}
