package main

import "fmt"

// Узел двусвязного списка
type LNode struct {
	data int
	prev *LNode
	next *LNode
}

// Сам список
type DoublyLinkedList struct {
	head *LNode
	tail *LNode
}

// Добавление в хвост
func (l *DoublyLinkedList) PushBack(value int) {
	newNode := &LNode{data: value}
	if l.tail == nil {
		l.head = newNode
		l.tail = newNode
		return
	}
	l.tail.next = newNode
	newNode.prev = l.tail
	l.tail = newNode
}

// Добавление в голову
func (l *DoublyLinkedList) PushFront(value int) {
	newNode := &LNode{data: value}
	if l.head == nil {
		l.head = newNode
		l.tail = newNode
		return
	}
	newNode.next = l.head
	l.head.prev = newNode
	l.head = newNode
}

// Вставка перед target
func (l *DoublyLinkedList) InsertBefore(target, value int) bool {
	curr := l.head
	for curr != nil && curr.data != target {
		curr = curr.next
	}
	if curr == nil {
		return false
	}
	newNode := &LNode{data: value, prev: curr.prev, next: curr}
	if curr.prev != nil {
		curr.prev.next = newNode
	} else {
		l.head = newNode
	}
	curr.prev = newNode
	return true
}

// Вставка после target
func (l *DoublyLinkedList) InsertAfter(target, value int) bool {
	curr := l.head
	for curr != nil && curr.data != target {
		curr = curr.next
	}
	if curr == nil {
		return false
	}
	newNode := &LNode{data: value, prev: curr, next: curr.next}
	if curr.next != nil {
		curr.next.prev = newNode
	} else {
		l.tail = newNode
	}
	curr.next = newNode
	return true
}

// Удаление по значению
func (l *DoublyLinkedList) Delete(value int) bool {
	curr := l.head
	for curr != nil && curr.data != value {
		curr = curr.next
	}
	if curr == nil {
		return false
	}
	if curr.prev != nil {
		curr.prev.next = curr.next
	} else {
		l.head = curr.next
	}
	if curr.next != nil {
		curr.next.prev = curr.prev
	} else {
		l.tail = curr.prev
	}
	return true
}

// Получение по индексу
func (l *DoublyLinkedList) Get(index int) int {
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
func (l *DoublyLinkedList) Contains(value int) bool {
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
func (l *DoublyLinkedList) Print() {
	curr := l.head
	for curr != nil {
		fmt.Print(curr.data, " ")
		curr = curr.next
	}
	fmt.Println()
}

// Преобразовать в срез (для записи в файл)
func (l *DoublyLinkedList) ToSlice() []int {
	var result []int
	curr := l.head
	for curr != nil {
		result = append(result, curr.data)
		curr = curr.next
	}
	if result == nil {
		return []int{}
	}
	return result
}

// Восстановить список из среза
func (l *DoublyLinkedList) FromSlice(data []int) {
	l.head = nil
	l.tail = nil
	for _, v := range data {
		l.PushBack(v)
	}
}

// Удаление из головы
func (l *DoublyLinkedList) DelFront() bool {
	if l.head == nil {
		return false
	}
	if l.head.next == nil {
		l.head = nil
		l.tail = nil
		return true
	}
	l.head = l.head.next
	l.head.prev = nil
	return true
}

// Удаление из хвоста
func (l *DoublyLinkedList) DelBack() bool {
	if l.tail == nil {
		return false
	}
	if l.tail.prev == nil {
		l.head = nil
		l.tail = nil
		return true
	}
	l.tail = l.tail.prev
	l.tail.next = nil
	return true
}
