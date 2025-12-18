package main

import (
	"fmt"
	"strconv"
)

// Узел очереди
type QueueNode struct {
	data int
	next *QueueNode
}

// Очередь
type Queue struct {
	front *QueueNode // начало
	rear  *QueueNode // конец
}

// Добавить в очередь (в хвост)
func (q *Queue) Push(value int) {
	newNode := &QueueNode{data: value}
	if q.rear == nil {
		q.front = newNode
		q.rear = newNode
	} else {
		q.rear.next = newNode
		q.rear = newNode
	}
}

// Удалить из очереди (с головы)
func (q *Queue) Pop() (int, bool) {
	if q.front == nil {
		return -1, false
	}
	val := q.front.data
	q.front = q.front.next
	if q.front == nil {
		q.rear = nil
	}
	return val, true
}

// Печать очереди
func (q *Queue) Print() {
	curr := q.front
	if curr == nil {
		fmt.Println("очередь пуста")
		return
	}
	for curr != nil {
		fmt.Print(curr.data, " ")
		curr = curr.next
	}
	fmt.Println()
}

// Преобразовать в срез (для сохранения в файл)
func (q *Queue) toSlice() []int {
	values := []int{}
	curr := q.front
	for curr != nil {
		values = append(values, curr.data)
		curr = curr.next
	}
	// Убедимся что не возвращаем nil
	if values == nil {
		return []int{}
	}
	return values
}

// Загрузить очередь из среза
func (q *Queue) fromSlice(data []int) {
	q.front = nil
	q.rear = nil
	for _, v := range data {
		q.Push(v)
	}
}

// Обработка команд
func handleQueueCommand(queue *Queue, parts []string) {
	if len(parts) < 1 {
		fmt.Println("Ошибка: пустая команда для очереди")
		return
	}

	switch parts[0] {
		case "QPUSH":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1]) // было parts[2]
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			queue.Push(val)
			fmt.Println("-> добавлен", val)

		case "QPOP":
			val, ok := queue.Pop()
			if !ok {
				fmt.Println("Ошибка: очередь пуста")
				return
			}
			fmt.Println("-> удалён первый элемент", val)

		case "PRINTQ":
			fmt.Print("-> ")
			queue.Print()

		default:
			fmt.Println("Неизвестная команда:", parts[0])
	}
}
