package main

import (
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestQueuePushPop(t *testing.T) {
	queue := &Queue{}
	queue.Push(1)
	queue.Push(2)
	queue.Push(3)

	val, ok := queue.Pop()
	assert.True(t, ok)
	assert.Equal(t, 1, val)

	val, ok = queue.Pop()
	assert.True(t, ok)
	assert.Equal(t, 2, val)

	val, ok = queue.Pop()
	assert.True(t, ok)
	assert.Equal(t, 3, val)

	// Пустая очередь
	val, ok = queue.Pop()
	assert.False(t, ok)
}

func TestQueueEdgeCases(t *testing.T) {
	queue := &Queue{}

	// Тест пустой очереди
	val, ok := queue.Pop()
	assert.False(t, ok)
	assert.Equal(t, -1, val)

	// Печать пустой очереди
	assert.NotPanics(t, func() {
		queue.Print()
	})
}

func TestQueueToFromSlice(t *testing.T) {
	queue := &Queue{}

	// Тест toSlice с пустой очередью
	assert.Equal(t, []int{}, queue.toSlice())

	// Тест fromSlice
	data := []int{1, 2, 3, 4, 5}
	queue.fromSlice(data)
	assert.Equal(t, data, queue.toSlice())

	// Проверяем, что очередь работает правильно после fromSlice
	val, ok := queue.Pop()
	assert.True(t, ok)
	assert.Equal(t, 1, val)
}

func TestQueueMultipleOperations(t *testing.T) {
	queue := &Queue{}

	// Множественные операции push/pop
	queue.Push(1)
	queue.Push(2)
	queue.Push(3)

	assert.Equal(t, []int{1, 2, 3}, queue.toSlice())

	val, ok := queue.Pop()
	assert.True(t, ok)
	assert.Equal(t, 1, val)

	queue.Push(4)
	assert.Equal(t, []int{2, 3, 4}, queue.toSlice())
}

func TestQueuePrint(t *testing.T) {
	queue := &Queue{}

	// Тест печати пустой очереди
	assert.NotPanics(t, func() {
		queue.Print()
	})

	// Тест печати заполненной очереди
	queue.Push(1)
	queue.Push(2)
	queue.Push(3)
	assert.NotPanics(t, func() {
		queue.Print()
	})
}

func TestQueueCommandOutput(t *testing.T) {
	queue := &Queue{}

	// Тест вывода QPUSH
	handleQueueCommand(queue, []string{"QPUSH", "42"})

	// Тест вывода QPOP
	handleQueueCommand(queue, []string{"QPOP"})

	// Тест вывода PRINTQ
	handleQueueCommand(queue, []string{"PRINTQ"})

	// Тест неизвестной команды
	handleQueueCommand(queue, []string{"UNKNOWN_CMD"})
}
