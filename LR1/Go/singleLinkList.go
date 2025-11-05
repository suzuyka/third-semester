package main

import (
	"fmt"
)

type SLNode struct {
	key  string
	next *SLNode
}

type SingleLL struct {
	head *SLNode
	size int
}

func CreateSL(ls *SingleLL, key string) {
	if ls.size != 0 {
		fmt.Println("Error: An existing list")
		return
	}
	newNode := &SLNode{key: key, next: nil}
	ls.head = newNode
	ls.size++
}

func OutputSL(ls *SingleLL) {
	fmt.Printf("Single Link List[%d]: ", ls.size)
	current := ls.head
	for current != nil {
		fmt.Printf("%s ", current.key)
		current = current.next
	}
	if ls.size == 0 {
		fmt.Print("Empty list")
	}
	fmt.Println()
}

func FPushFront(ls *SingleLL, key string) {
	if ls.head == nil {
		CreateSL(ls, key)
		return
	}
	newNode := &SLNode{key: key, next: nil}
	newNode.next = ls.head
	ls.head = newNode
	ls.size++
}

func FPushBack(ls *SingleLL, key string) {
	if ls.head == nil {
		CreateSL(ls, key)
		return
	}
	current := ls.head
	for current.next != nil {
		current = current.next
	}
	newNode := &SLNode{key: key, next: nil}
	current.next = newNode
	ls.size++
}

func FPushAt(ls *SingleLL, index int, value string) {
	if index < 0 {
		fmt.Println("Ошибка: Индекс не может быть отрицательным")
		return
	}

	newNode := &SLNode{key: value, next: nil}
	if index == 0 {
		newNode.next = ls.head
		ls.head = newNode
		ls.size++
		fmt.Printf("Элемент '%s' добавлен по индексу %d\n", value, index)
		return
	}

	current := ls.head
	currentIndex := 0

	for current != nil && currentIndex < index-1 {
		current = current.next
		currentIndex++
	}

	if current == nil {
		fmt.Printf("Ошибка: Индекс %d выходит за пределы списка\n", index)
		return
	}

	newNode.next = current.next
	current.next = newNode
	ls.size++

	fmt.Printf("Элемент '%s' добавлен по индексу %d\n", value, index)
}

func FGetValue(ls *SingleLL, key string) string {
	if ls.head == nil {
		fmt.Println("Error: List is not existing or empty")
		return ""
	}
	current := ls.head
	for current != nil && current.key != key {
		current = current.next
	}
	if current == nil {
		fmt.Printf("Element %s didn't find\n", key)
		return ""
	}
	return current.key
}

func FGetIndex(ls *SingleLL, index int) string {
	if ls.head == nil {
		fmt.Println("List is empty")
		return ""
	}
	if index < 0 {
		fmt.Println("Incorrect index")
		return ""
	}
	current := ls.head
	currentIndex := 0

	for current != nil && currentIndex < index {
		current = current.next
		currentIndex++
	}
	if current != nil {
		return current.key
	} else {
		fmt.Println("Element didn't find")
		return ""
	}
}

func FDelValue(ls *SingleLL, key string) {
    if ls.head == nil {
        fmt.Println("Error: List is empty")
        return
    }
    if ls.head.key == key {
        ls.head = ls.head.next
        ls.size--
        fmt.Printf("Элемент '%s' удален\n", key)
        return
    }
	current := ls.head
	for current.next != nil && current.next.key != key {
		current = current.next
	}

	if current.next != nil {
		current.next = current.next.next
		ls.size--
		fmt.Printf("Элемент '%s' удален\n", key)
	} else {
		fmt.Printf("Элемент '%s' не найден\n", key)
	}
}

func FDelAt(ls *SingleLL, index int) {
	if ls.head == nil {
		fmt.Println("Ошибка: List is empty")
		return
	}
	if index < 0 || index >= ls.size {
		fmt.Println("Ошибка: Incorrect index")
		return
	}

	current := ls.head
	var prev *SLNode = nil

	for indCur := 0; current != nil && indCur < index; indCur++ {
		prev = current
		current = current.next
	}

	if current != nil {
		if prev == nil {

			ls.head = current.next
		} else {

			prev.next = current.next
		}

		ls.size--
		fmt.Printf("Элемент с индексом %d удален\n", index)
	}
}

func FDelList(ls *SingleLL) {
	if ls.head == nil {
		return
	}
	// Просто обнуляем указатели
	ls.head = nil
	ls.size = 0
}

func FGetSize(ls *SingleLL) int {
	return ls.size
}
