package main

import (
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestDoublyLinkedListPushBack(t *testing.T) {
	list := &DoublyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	assert.Equal(t, 1, list.Get(0))
	assert.Equal(t, 2, list.Get(1))
	assert.Equal(t, 3, list.Get(2))
}

func TestDoublyLinkedListPushFront(t *testing.T) {
	list := &DoublyLinkedList{}
	list.PushFront(1)
	list.PushFront(2)
	list.PushFront(3)

	assert.Equal(t, 3, list.Get(0))
	assert.Equal(t, 2, list.Get(1))
	assert.Equal(t, 1, list.Get(2))
}

func TestDoublyLinkedListDelFrontBack(t *testing.T) {
	list := &DoublyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	assert.True(t, list.DelFront())
	assert.Equal(t, 2, list.Get(0))

	assert.True(t, list.DelBack())
	assert.Equal(t, 2, list.Get(0))
	assert.Equal(t, 1, len(list.ToSlice()))
}

func TestDoublyLinkedListEdgeCases(t *testing.T) {
	list := &DoublyLinkedList{}

	// Тест пустого списка
	assert.Equal(t, -1, list.Get(0))
	assert.False(t, list.Contains(1))
	assert.False(t, list.Delete(1))
	assert.False(t, list.InsertBefore(1, 2))
	assert.False(t, list.InsertAfter(1, 2))
	assert.False(t, list.DelFront())
	assert.False(t, list.DelBack())

	// Печать пустого списка
	assert.NotPanics(t, func() {
		list.Print()
	})
}

func TestDoublyLinkedListToFromSlice(t *testing.T) {
	list := &DoublyLinkedList{}

	// Тест ToSlice с пустым списком
	assert.Equal(t, []int{}, list.ToSlice())

	// Тест FromSlice
	data := []int{1, 2, 3, 4, 5}
	list.FromSlice(data)
	assert.Equal(t, data, list.ToSlice())

	// Очистка через FromSlice с пустым срезом
	list.FromSlice([]int{})
	assert.Equal(t, []int{}, list.ToSlice())
}

func TestDoublyLinkedListComplexOperations(t *testing.T) {
	list := &DoublyLinkedList{}

	// Комплексные операции
	list.PushBack(1)
	list.PushFront(0)
	list.InsertAfter(1, 2)
	list.InsertBefore(1, 99)

	assert.Equal(t, []int{0, 99, 1, 2}, list.ToSlice())
	assert.True(t, list.Contains(99))

	list.Delete(99)
	list.DelFront()
	list.DelBack()

	assert.Equal(t, []int{1}, list.ToSlice())
}
