package main

import (
	"fmt"
)

type DLNode struct {
	key  string
	past *DLNode
	next *DLNode
}

type DoubleList struct {
	head *DLNode
	size int
}

func CreateDL(ls *DoubleList) {
	ls.head = nil
	ls.size = 0
}

func OutputDL(ls *DoubleList) {
	fmt.Printf("DoubleList [%d]: ", ls.size)

	if ls.head == nil {
		fmt.Println("List is empty")
		return
	}
	current := ls.head
	for i := 0; i < ls.size && current != nil; i++ {
		fmt.Printf("%s ", current.key)
		current = current.next
	}
	fmt.Println()
}

func RevOutputDL(ls *DoubleList) {
	fmt.Printf("DoubleList [%d] reverse: ", ls.size)

	if ls.head == nil {
		fmt.Println("List is empty")
		return
	}

	current := ls.head
	for current.next != nil {
		current = current.next
	}

	for current != nil {
		fmt.Printf("%s ", current.key)
		current = current.past
	}
	fmt.Println()
}

func DLFind(ls *DoubleList, key string) {
	if ls.head == nil {
		fmt.Println("List is empty")
		return
	}

	current := ls.head
	for i := 0; i < ls.size && current != nil; i++ {
		if current.key == key {
			fmt.Printf("Element [%d] = %s\n", i, current.key)
			return
		}
		current = current.next
	}
	fmt.Println("Element didn't find")
}

func DLPushFront(ls *DoubleList, key string) {
	newNode := &DLNode{key: key, past: nil, next: nil}
	newNode.next = ls.head

	if ls.head != nil {
		ls.head.past = newNode
	}
	ls.head = newNode
	ls.size++
	fmt.Printf("Элемент %s добавлен в начало\n", key)
}

func DLPushBack(ls *DoubleList, key string) {
	newNode := &DLNode{key: key, past: nil, next: nil}

	if ls.head == nil {
		ls.head = newNode
	} else {
		tail := ls.head
		for tail.next != nil {
			tail = tail.next
		}
		tail.next = newNode
		newNode.past = tail
		fmt.Printf("Элемент %s добавлен в конец\n", key)
	}
	ls.size++
}

func DLPushAt(ls *DoubleList, index int, key string) {
	if index < 0 || index > ls.size {
		fmt.Println("Error: Incorrect index")
		return
	}

	newNode := &DLNode{key: key, past: nil, next: nil}

	if ls.head == nil {
		if index == 0 {
			DLPushFront(ls, key)
		} else {
			fmt.Println("Error: List is empty, can only insert at index 0")
		}
		return
	}

	if index == 0 {
		DLPushFront(ls, key)
		return
	}

	if index == ls.size {
		DLPushBack(ls, key)
		return
	}

	current := ls.head
	for i := 0; current != nil && i < index; i++ {
		current = current.next
	}

	if current != nil {
		newNode.next = current
		newNode.past = current.past

		if current.past != nil {
			current.past.next = newNode
		}
		current.past = newNode

		ls.size++
		fmt.Printf("Элемент %s добавлен по индексу %d\n", key, index)
	}
}

func DLDelValue(ls *DoubleList, key string) {
	if ls.head == nil {
		fmt.Println("List is empty")
		return
	}
	if ls.head.key == key {
		DLDelFront(ls)
		return
	}

	current := ls.head
	for current != nil && current.key != key {
		current = current.next
	}

	if current != nil {
		if current.past != nil {
			current.past.next = current.next
		}
		if current.next != nil {
			current.next.past = current.past
		}
		ls.size--
	} else {
		fmt.Println("Element didn't find")
	}
}

func DLDelAt(ls *DoubleList, index int) {
	if ls.head == nil {
		fmt.Println("Error: List is empty")
		return
	}

	if index < 0 || index >= ls.size {
		fmt.Println("Error: incorrect index")
		return
	}

	if index == 0 {
		DLDelFront(ls)
		return
	}

	current := ls.head
	for i := 0; i < index && current != nil; i++ {
		current = current.next
	}

	if current != nil {
		if current.past != nil {
			current.past.next = current.next
		}
		if current.next != nil {
			current.next.past = current.past
		}
		ls.size--
	}
}

func DLDelFront(ls *DoubleList) {
    if ls.head == nil {
        fmt.Println("List is empty")
        return
    }

    if ls.head.next != nil {
        ls.head = ls.head.next
        ls.head.past = nil
    } else {
        ls.head = nil
    }
    ls.size--
}

func DLDelBack(ls *DoubleList) {
	if ls.head == nil {
		fmt.Println("List is empty")
		return
	}

	current := ls.head
	for current.next != nil {
		current = current.next
	}

	if current.past != nil {
		current.past.next = nil
	} else {
		ls.head = nil
	}
	ls.size--
}

func DLDelAll(ls *DoubleList) {
	if ls.head == nil {
		return
	}

	// Просто обнуляем указатели
	ls.head = nil
	ls.size = 0
}


func DLGetSize(ls *DoubleList) int {
	return ls.size
}

func DLGetAt(ls *DoubleList, index int) string {
	if index < 0 || index >= ls.size {
		fmt.Println("Out of range")
		return ""
	}
	current := ls.head
	for i := 0; current != nil && i < index; i++ {
		current = current.next
	}

	if current != nil {
		return current.key
	} else {
		fmt.Printf("%d didn't find\n", index)
		return ""
	}
}

func DLGetFront(ls *DoubleList) string {
	if ls.head == nil {
		fmt.Println("List is empty")
		return ""
	}
	return ls.head.key
}

func DLGetBack(ls *DoubleList) string {
	if ls.head == nil {
		fmt.Println("List is empty")
		return ""
	}

	current := ls.head
	for current.next != nil {
		current = current.next
	}
	return current.key
}
