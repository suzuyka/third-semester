package main

import (
	"fmt"
)

type QNode struct {
	key  string
	past *QNode
	next *QNode
}

type Queue struct {
	front *QNode
	back  *QNode
	size  int
}

func CreateQ(q *Queue) {
	q.front = nil
	q.back = nil
	q.size = 0
}

func OutputQ(q *Queue) {
	fmt.Printf("Queue [%d]: ", q.size)
	if q.front == nil {
		fmt.Print("Error: Empty Queue")
		fmt.Println()
		return
	}
	current := q.front
	for i := 0; i < q.size && current != nil; i++ {
		fmt.Printf("%s ", current.key)
		current = current.next
	}
	fmt.Println()
}

func QPush(q *Queue, key string) {
	newNode := &QNode{key: key, past: nil, next: nil}

	if q.back == nil {
		q.front = newNode
		q.back = newNode
	} else {
		newNode.past = q.back
		q.back.next = newNode
		q.back = newNode
	}
	q.size++
}

func QPop(q *Queue) {
    if q.front == nil {
        fmt.Println("Error: Queue is empty")
        return
    }
    q.front = q.front.next

    if q.front != nil {
        q.front.past = nil
    } else {
        q.back = nil
    }
    q.size--
}

func QGetSize(q *Queue) int {
	return q.size
}

func QGetIndex(q *Queue, index int) string {
	if q.size == 0 {
		return ""
	}
	if index < 0 || index >= q.size {
		fmt.Println("Out of range")
		return ""
	}
	current := q.front
	currentIndex := 0
	for current != nil && currentIndex < index {
		current = current.next
		currentIndex++
	}

	if current != nil {
		return current.key
	}
	return ""
}

func QDelAll(q *Queue) {
	if q != nil {
		// Просто обнуляем указатели
		q.front = nil
		q.back = nil
		q.size = 0
	}
}
