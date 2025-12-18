package main

import (
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestSinglyLinkedListPushBack(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	assert.Equal(t, 1, list.Get(0))
	assert.Equal(t, 2, list.Get(1))
	assert.Equal(t, 3, list.Get(2))
}

func TestSinglyLinkedListPushFront(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushFront(1)
	list.PushFront(2)
	list.PushFront(3)

	assert.Equal(t, 3, list.Get(0))
	assert.Equal(t, 2, list.Get(1))
	assert.Equal(t, 1, list.Get(2))
}

func TestSinglyLinkedListInsertBefore(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack(1)
	list.PushBack(3)

	result := list.InsertBefore(3, 2)
	assert.True(t, result)
	assert.Equal(t, 2, list.Get(1))
}

func TestSinglyLinkedListDelete(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	result := list.Delete(2)
	assert.True(t, result)
	assert.False(t, list.Contains(2))
}

func TestSinglyLinkedListContains(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)

	assert.True(t, list.Contains(1))
	assert.True(t, list.Contains(2))
	assert.False(t, list.Contains(3))
}

func TestSinglyLinkedListEdgeCases(t *testing.T) {
	list := &SinglyLinkedList{}

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

func TestSinglyLinkedListToSlice(t *testing.T) {
	list := &SinglyLinkedList{}

	// Пустой список
	assert.Equal(t, []int{}, list.ToSlice())

	// Заполненный список
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)
	assert.Equal(t, []int{1, 2, 3}, list.ToSlice())
}

func TestSinglyLinkedListFromSlice(t *testing.T) {
	list := &SinglyLinkedList{}

	// Восстановление из среза
	data := []int{1, 2, 3, 4, 5}
	list.FromSlice(data)
	assert.Equal(t, data, list.ToSlice())

	// Восстановление из пустого среза
	list.FromSlice([]int{})
	assert.Equal(t, []int{}, list.ToSlice())
}

func TestSinglyLinkedListComplexOperations(t *testing.T) {
	list := &SinglyLinkedList{}

	// Комплексные операции
	list.PushBack(1)
	list.PushFront(0)
	list.InsertAfter(1, 2)
	list.InsertBefore(1, 99)

	assert.Equal(t, []int{0, 99, 1, 2}, list.ToSlice())

	list.Delete(99)
	list.DelFront()
	list.DelBack()

	assert.Equal(t, []int{1}, list.ToSlice())
}
