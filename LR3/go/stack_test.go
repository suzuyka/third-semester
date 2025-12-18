package main

import (
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestStackPushPop(t *testing.T) {
	stack := &Stack{}
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)

	val, ok := stack.Pop()
	assert.True(t, ok)
	assert.Equal(t, 3, val)

	val, ok = stack.Pop()
	assert.True(t, ok)
	assert.Equal(t, 2, val)

	val, ok = stack.Pop()
	assert.True(t, ok)
	assert.Equal(t, 1, val)

	// Пустой стек
	val, ok = stack.Pop()
	assert.False(t, ok)
}

func TestStackEdgeCases(t *testing.T) {
	stack := &Stack{}

	// Тест пустого стека
	val, ok := stack.Pop()
	assert.False(t, ok)
	assert.Equal(t, -1, val)

	// Печать пустого стека
	assert.NotPanics(t, func() {
		stack.Print()
	})
}

func TestStackToFromSlice(t *testing.T) {
	stack := &Stack{}

	// Тест toSlice с пустым стеком
	assert.Equal(t, []int{}, stack.toSlice())

	// Тест fromSlice
	data := []int{1, 2, 3, 4, 5}
	stack.fromSlice(data)

	// Проверяем, что стек работает правильно после fromSlice
	val, ok := stack.Pop()
	assert.True(t, ok)
	assert.Equal(t, 5, val)
}

func TestStackMultipleOperations(t *testing.T) {
	stack := &Stack{}

	// Множественные операции push/pop
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)

	assert.Equal(t, []int{1, 2, 3}, stack.toSlice())

	val, ok := stack.Pop()
	assert.True(t, ok)
	assert.Equal(t, 3, val)

	stack.Push(4)
	assert.Equal(t, []int{1, 2, 4}, stack.toSlice())
}

func TestStackPrint(t *testing.T) {
	stack := &Stack{}

	// Тест печати пустого стека
	assert.NotPanics(t, func() {
		stack.Print()
	})

	// Тест печати заполненного стека
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)
	assert.NotPanics(t, func() {
		stack.Print()
	})
}

func TestStackCommandOutput(t *testing.T) {
	stack := &Stack{}

	// Тест вывода SPUSH
	handleStackCommand(stack, []string{"SPUSH", "42"})

	// Тест вывода SPOP
	handleStackCommand(stack, []string{"SPOP"})

	// Тест вывода PRINTS
	handleStackCommand(stack, []string{"PRINTS"})

	// Тест неизвестной команды
	handleStackCommand(stack, []string{"UNKNOWN_CMD"})
}
