package main

import (
	"os"
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestArraySerialization(t *testing.T) {
	arr := &Array{}
	arr.Push(1)
	arr.Push(2)
	arr.Push(3)

	// Тест бинарной сериализации
	err := arr.SerializeBinary("test_array.bin")
	assert.NoError(t, err)

	newArr := &Array{}
	err = newArr.DeserializeBinary("test_array.bin")
	assert.NoError(t, err)
	assert.Equal(t, arr.data, newArr.data)

	// Тест текстовой сериализации
	err = arr.SerializeText("test_array.txt")
	assert.NoError(t, err)

	textArr := &Array{}
	err = textArr.DeserializeText("test_array.txt")
	assert.NoError(t, err)
	assert.Equal(t, arr.data, textArr.data)

	// Очистка
	os.Remove("test_array.bin")
	os.Remove("test_array.txt")
}

func TestSinglyLinkedListSerialization(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	err := list.SerializeBinary("test_slist.bin")
	assert.NoError(t, err)

	newList := &SinglyLinkedList{}
	err = newList.DeserializeBinary("test_slist.bin")
	assert.NoError(t, err)
	assert.Equal(t, list.ToSlice(), newList.ToSlice())

	// Текстовая сериализация
	err = list.SerializeText("test_slist.txt")
	assert.NoError(t, err)

	textList := &SinglyLinkedList{}
	err = textList.DeserializeText("test_slist.txt")
	assert.NoError(t, err)
	assert.Equal(t, list.ToSlice(), textList.ToSlice())

	// Очистка
	os.Remove("test_slist.bin")
	os.Remove("test_slist.txt")
}

func TestDoublyLinkedListSerialization(t *testing.T) {
	list := &DoublyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	err := list.SerializeBinary("test_dlist.bin")
	assert.NoError(t, err)

	newList := &DoublyLinkedList{}
	err = newList.DeserializeBinary("test_dlist.bin")
	assert.NoError(t, err)
	assert.Equal(t, list.ToSlice(), newList.ToSlice())

	// Очистка
	os.Remove("test_dlist.bin")
}

func TestQueueSerialization(t *testing.T) {
	queue := &Queue{}
	queue.Push(1)
	queue.Push(2)
	queue.Push(3)

	err := queue.SerializeBinary("test_queue.bin")
	assert.NoError(t, err)

	newQueue := &Queue{}
	err = newQueue.DeserializeBinary("test_queue.bin")
	assert.NoError(t, err)
	assert.Equal(t, queue.toSlice(), newQueue.toSlice())

	// Очистка
	os.Remove("test_queue.bin")
}

func TestHashTableSerialization(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)

	// Бинарная сериализация
	err := ht.SerializeBinary("test_hashtable.bin")
	assert.NoError(t, err)

	newHt := NewHashTable(11, DOUBLE_HASHING)
	err = newHt.DeserializeBinary("test_hashtable.bin")
	assert.NoError(t, err)

	val, ok := newHt.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	// Текстовая сериализация
	err = ht.SerializeText("test_hashtable.txt")
	assert.NoError(t, err)

	textHt := NewHashTable(11, DOUBLE_HASHING)
	err = textHt.DeserializeText("test_hashtable.txt")
	assert.NoError(t, err)

	val, ok = textHt.Get(2)
	assert.True(t, ok)
	assert.Equal(t, 200, val)

	// Очистка
	os.Remove("test_hashtable.bin")
	os.Remove("test_hashtable.txt")
}

func TestDoublyLinkedListTextSerialization(t *testing.T) {
	list := &DoublyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	// Текстовая сериализация
	err := list.SerializeText("test_dlist.txt")
	assert.NoError(t, err)

	newList := &DoublyLinkedList{}
	err = newList.DeserializeText("test_dlist.txt")
	assert.NoError(t, err)
	assert.Equal(t, list.ToSlice(), newList.ToSlice())

	// Очистка
	os.Remove("test_dlist.txt")
}

func TestQueueTextSerialization(t *testing.T) {
	queue := &Queue{}
	queue.Push(1)
	queue.Push(2)
	queue.Push(3)

	// Текстовая сериализация
	err := queue.SerializeText("test_queue.txt")
	assert.NoError(t, err)

	newQueue := &Queue{}
	err = newQueue.DeserializeText("test_queue.txt")
	assert.NoError(t, err)
	assert.Equal(t, queue.toSlice(), newQueue.toSlice())

	// Очистка
	os.Remove("test_queue.txt")
}

func TestSerializeErrorReturns(t *testing.T) {
	// Создаем невалидный путь
	invalidPath := "/invalid/path/that/cannot/be/created/file.bin"

	// Тест Array SerializeBinary error return
	arr := &Array{}
	arr.Push(1)
	err := arr.SerializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест Array DeserializeBinary error return
	err = arr.DeserializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест Array SerializeText error return
	err = arr.SerializeText(invalidPath)
	assert.Error(t, err)

	// Тест Array DeserializeText error return
	err = arr.DeserializeText(invalidPath)
	assert.Error(t, err)

	// Тест SinglyLinkedList SerializeBinary error return
	slist := &SinglyLinkedList{}
	slist.PushBack(1)
	err = slist.SerializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест SinglyLinkedList DeserializeBinary error return
	err = slist.DeserializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест SinglyLinkedList SerializeText error return
	err = slist.SerializeText(invalidPath)
	assert.Error(t, err)

	// Тест SinglyLinkedList DeserializeText error return
	err = slist.DeserializeText(invalidPath)
	assert.Error(t, err)

	// Тест DoublyLinkedList SerializeBinary error return
	dlist := &DoublyLinkedList{}
	dlist.PushBack(1)
	err = dlist.SerializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест DoublyLinkedList DeserializeBinary error return
	err = dlist.DeserializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест DoublyLinkedList SerializeText error return
	err = dlist.SerializeText(invalidPath)
	assert.Error(t, err)

	// Тест DoublyLinkedList DeserializeText error return
	err = dlist.DeserializeText(invalidPath)
	assert.Error(t, err)

	// Тест Stack SerializeBinary error return
	stack := &Stack{}
	stack.Push(1)
	err = stack.SerializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест Stack DeserializeBinary error return
	err = stack.DeserializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест Stack SerializeText error return
	err = stack.SerializeText(invalidPath)
	assert.Error(t, err)

	// Тест Stack DeserializeText error return
	err = stack.DeserializeText(invalidPath)
	assert.Error(t, err)

	// Тест Queue SerializeBinary error return
	queue := &Queue{}
	queue.Push(1)
	err = queue.SerializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест Queue DeserializeBinary error return
	err = queue.DeserializeBinary(invalidPath)
	assert.Error(t, err)

	// Тест Queue SerializeText error return
	err = queue.SerializeText(invalidPath)
	assert.Error(t, err)

	// Тест Queue DeserializeText error return
	err = queue.DeserializeText(invalidPath)
	assert.Error(t, err)
}

func TestHashTableSerializeErrorReturns(t *testing.T) {

	// Тесты для HashTable error returns
	invalidPath := "/invalid/path/hashtable.bin"

	// HashTable SerializeBinary error
	ht := NewHashTable(11, DOUBLE_HASHING)
	ht.Insert(1, 100)
	err := ht.SerializeBinary(invalidPath)
	assert.Error(t, err)

	// HashTable DeserializeBinary error
	err = ht.DeserializeBinary(invalidPath)
	assert.Error(t, err)

	// HashTable SerializeText error
	err = ht.SerializeText(invalidPath)
	assert.Error(t, err)

	// HashTable DeserializeText error
	err = ht.DeserializeText(invalidPath)
	assert.Error(t, err)
}

func TestEdgeCaseSerializationErrors(t *testing.T) {

	// Тест с директорией вместо файла
	dirPath := "/tmp"

	arr := &Array{}
	arr.Push(1)
	err := arr.SerializeBinary(dirPath)
	assert.Error(t, err)

	// Тест с файлом без прав на запись
	readOnlyPath := "/readonly/file.bin"
	err = arr.SerializeBinary(readOnlyPath)
}

