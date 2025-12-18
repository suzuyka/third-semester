package main

import (
	"fmt"
	"strconv"
)

// Узел стека
type StackNode struct {
	data int
	next *StackNode
}

// Стек
type Stack struct {
	top *StackNode
}

// Push — добавление элемента
func (s *Stack) Push(value int) {
	newNode := &StackNode{data: value, next: s.top}
	s.top = newNode
}

// Pop — удаление элемента
func (s *Stack) Pop() (int, bool) {
	if s.top == nil {
		return -1, false
	}
	val := s.top.data
	s.top = s.top.next
	return val, true
}

// Print — печать элементов стека
func (s *Stack) Print() {
	if s.top == nil {
		fmt.Println("стек пуст")
		return
	}
	// проходим стек и собираем значения
	curr := s.top
	values := []int{}
	for curr != nil {
		values = append(values, curr.data)
		curr = curr.next
	}
	// выводим в порядке добавления (снизу вверх)
	for i := len(values) - 1; i >= 0; i-- {
		fmt.Print(values[i], " ")
	}
	fmt.Println()
}

// containsSlice нужен для сохранения в файл
func (s *Stack) toSlice() []int {
	values := []int{}
	curr := s.top
	for curr != nil {
		values = append([]int{curr.data}, values...) // добавляем в начало
		curr = curr.next
	}
	// Убедимся что не возвращаем nil
	if values == nil {
		return []int{}
	}
	return values
}



// загрузка из среза
func (s *Stack) fromSlice(data []int) {
	s.top = nil
	for _, v := range data {
		s.Push(v)
	}
}

// Обработка команд для стека
func handleStackCommand(stack *Stack, parts []string) {
	if len(parts) < 1 {
		fmt.Println("Ошибка: пустая команда для стека")
		return
	}

	switch parts[0] {
		case "SPUSH":
			if len(parts) < 2 {
				fmt.Println("Ошибка: укажите значение")
				return
			}
			val, err := strconv.Atoi(parts[1]) // было parts[2]
			if err != nil {
				fmt.Println("Ошибка: неверное значение")
				return
			}
			stack.Push(val)
			fmt.Println("-> добавлен", val)

		case "SPOP":
			val, ok := stack.Pop()
			if !ok {
				fmt.Println("Ошибка: стек пуст")
				return
			}
			fmt.Println("-> удалён верхний элемент", val)

		case "PRINTS":
			fmt.Print("-> ")
			stack.Print()

		default:
			fmt.Println("Неизвестная команда:", parts[0])
	}
}
