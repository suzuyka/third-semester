package main

import (
	"os"
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestArrayFileIO(t *testing.T) {
	arr := &Array{}
	arr.Push(1)
	arr.Push(2)
	arr.Push(3)

	// Сохранение в файл
	saveArrayToFile("test_array_io.txt", arr)

	// Загрузка из файла
	newArr := &Array{}
	loadArrayFromFile("test_array_io.txt", newArr)

	assert.Equal(t, arr.data, newArr.data)

	// Очистка
	os.Remove("test_array_io.txt")
}

func TestSinglyLinkedListFileIO(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	// Сохранение в файл
	saveSinglyListToFile("test_slist_io.txt", list)

	// Загрузка из файла
	newList := &SinglyLinkedList{}
	loadSinglyListFromFile("test_slist_io.txt", newList)

	assert.Equal(t, list.ToSlice(), newList.ToSlice())

	// Очистка
	os.Remove("test_slist_io.txt")
}

func TestDoublyLinkedListFileIO(t *testing.T) {
	list := &DoublyLinkedList{}
	list.PushBack(1)
	list.PushBack(2)
	list.PushBack(3)

	// Сохранение в файл
	saveDListToFile("test_dlist_io.txt", list)

	// Загрузка из файла
	newList := &DoublyLinkedList{}
	loadDListFromFile("test_dlist_io.txt", newList)

	assert.Equal(t, list.ToSlice(), newList.ToSlice())

	// Очистка
	os.Remove("test_dlist_io.txt")
}

func TestStackFileIO(t *testing.T) {
	stack := &Stack{}
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)

	// Сохранение в файл
	saveStackToFile("test_stack_io.txt", stack)

	// Загрузка из файла
	newStack := &Stack{}
	loadStackFromFile("test_stack_io.txt", newStack)

	assert.Equal(t, stack.toSlice(), newStack.toSlice())

	// Очистка
	os.Remove("test_stack_io.txt")
}

func TestQueueFileIO(t *testing.T) {
	queue := &Queue{}
	queue.Push(1)
	queue.Push(2)
	queue.Push(3)

	// Сохранение в файл
	saveQueueToFile("test_queue_io.txt", queue)

	// Загрузка из файла
	newQueue := &Queue{}
	loadQueueFromFile("test_queue_io.txt", newQueue)

	assert.Equal(t, queue.toSlice(), newQueue.toSlice())

	// Очистка
	os.Remove("test_queue_io.txt")
}

func TestHashTableFileIO(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)

	// Сохранение в файл
	saveHashTableToFile("test_hashtable_io.txt", ht)

	// Загрузка из файла
	newHt := NewHashTable(11, DOUBLE_HASHING)
	loadHashTableFromFile("test_hashtable_io.txt", newHt)

	val, ok := newHt.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	// Очистка
	os.Remove("test_hashtable_io.txt")
}

func TestArrayFileIOErrors(t *testing.T) {
	arr := &Array{}

	// Тест сохранения в невалидный путь
	saveArrayToFile("/invalid/path/array.txt", arr)

	// Тест загрузки из несуществующего файла
	loadArrayFromFile("nonexistent_file.txt", arr)
	assert.Equal(t, []int{}, arr.data)
}

func TestSinglyLinkedListFileIOErrors(t *testing.T) {
	list := &SinglyLinkedList{}

	// Тест сохранения в невалидный путь
	saveSinglyListToFile("/invalid/path/slist.txt", list)

	// Тест загрузки из несуществующего файла
	loadSinglyListFromFile("nonexistent_file.txt", list)
	assert.Equal(t, []int{}, list.ToSlice())
}

func TestDoublyLinkedListFileIOErrors(t *testing.T) {
	list := &DoublyLinkedList{}

	// Тест сохранения в невалидный путь
	saveDListToFile("/invalid/path/dlist.txt", list)

	// Тест загрузки из несуществующего файла
	loadDListFromFile("nonexistent_file.txt", list)
	assert.Equal(t, []int{}, list.ToSlice())
}

func TestStackFileIOErrors(t *testing.T) {
	stack := &Stack{}

	// Тест сохранения в невалидный путь
	saveStackToFile("/invalid/path/stack.txt", stack)

	// Тест загрузки из несуществующего файла
	loadStackFromFile("nonexistent_file.txt", stack)
	assert.Equal(t, []int{}, stack.toSlice())
}

func TestQueueFileIOErrors(t *testing.T) {
	queue := &Queue{}

	// Тест сохранения в невалидный путь
	saveQueueToFile("/invalid/path/queue.txt", queue)

	// Тест загрузки из несуществующего файла
	loadQueueFromFile("nonexistent_file.txt", queue)
	assert.Equal(t, []int{}, queue.toSlice())
}

func TestHashTableFileIOErrors(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)

	// Тест сохранения в невалидный путь
	saveHashTableToFile("/invalid/path/hashtable.txt", ht)

	// Тест загрузки из несуществующего файла
	loadHashTableFromFile("nonexistent_file.txt", ht)

	// Проверяем что таблица пуста
	val, ok := ht.Get(1)
	assert.False(t, ok)
	assert.Equal(t, -1, val)
}

// Тест обработки поврежденных данных
func TestFileIOCorruptedData(t *testing.T) {

	// Создаем файл с поврежденными данными
	corruptedData := "1\nabc\n3\n"
	err := os.WriteFile("corrupted.txt", []byte(corruptedData), 0644)
	assert.NoError(t, err)
	defer os.Remove("corrupted.txt")

	// Тест загрузки массива из поврежденного файла
	arr := &Array{}
	loadArrayFromFile("corrupted.txt", arr)

	assert.Equal(t, []int{1}, arr.data)

	// Тест загрузки списка из поврежденного файла
	list := &SinglyLinkedList{}
	loadSinglyListFromFile("corrupted.txt", list)
	assert.Equal(t, []int{1}, list.ToSlice())
}
