package main

import (
	"os"
	"bytes"
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestArrayPush(t *testing.T) {
	arr := &Array{}
	arr.Push(1)
	arr.Push(2)

	assert.Equal(t, 2, len(arr.data))
	assert.Equal(t, 1, arr.data[0])
	assert.Equal(t, 2, arr.data[1])
}

func TestArrayInsert(t *testing.T) {
	arr := &Array{}
	arr.Push(1)
	arr.Push(3)

	// Вставка в середину
	result := arr.Insert(1, 2)
	assert.True(t, result)
	assert.Equal(t, []int{1, 2, 3}, arr.data)

	// Вставка в недопустимую позицию
	result = arr.Insert(10, 4)
	assert.False(t, result)
}

func TestArrayGet(t *testing.T) {
	arr := &Array{}
	arr.Push(10)
	arr.Push(20)

	assert.Equal(t, 10, arr.Get(0))
	assert.Equal(t, 20, arr.Get(1))
	assert.Equal(t, -1, arr.Get(5)) // несуществующий индекс
}

func TestArraySet(t *testing.T) {
	arr := &Array{}
	arr.Push(1)
	arr.Push(2)

	result := arr.Set(1, 99)
	assert.True(t, result)
	assert.Equal(t, 99, arr.Get(1))

	result = arr.Set(5, 100) // несуществующий индекс
	assert.False(t, result)
}

func TestArrayDelete(t *testing.T) {
	arr := &Array{}
	arr.Push(1)
	arr.Push(2)
	arr.Push(3)

	result := arr.Delete(1) // удаляем средний элемент
	assert.True(t, result)
	assert.Equal(t, []int{1, 3}, arr.data)

	result = arr.Delete(5) // несуществующий индекс
	assert.False(t, result)
}

func TestArrayEdgeCases(t *testing.T) {
	arr := &Array{}

	// Тест пустого массива
	assert.Equal(t, -1, arr.Get(0))
	assert.False(t, arr.Set(0, 1))
	assert.False(t, arr.Delete(0))

	// Тест вставки в пустой массив
	assert.True(t, arr.Insert(0, 1))
	assert.Equal(t, []int{1}, arr.data)
}

func TestArrayMultipleOperations(t *testing.T) {
	arr := &Array{}

	// Последовательные операции
	arr.Push(1)
	arr.Push(2)
	arr.Push(3)
	assert.Equal(t, []int{1, 2, 3}, arr.data)

	arr.Insert(1, 99)
	assert.Equal(t, []int{1, 99, 2, 3}, arr.data)

	arr.Set(2, 88)
	assert.Equal(t, []int{1, 99, 88, 3}, arr.data)

	arr.Delete(1)
	assert.Equal(t, []int{1, 88, 3}, arr.data)
}

func TestArrayPrint(t *testing.T) {
	arr := &Array{}
	arr.Push(1)
	arr.Push(2)

	assert.NotPanics(t, func() {
		arr.Print()
	})
}

func TestHandleSListCommand(t *testing.T) {
	list := &SinglyLinkedList{}

	// Тест FPUSH
	handleSListCommand(list, []string{"FPUSH", "10"})
	assert.Equal(t, []int{10}, list.ToSlice())

	// Тест FPUSHFRONT
	handleSListCommand(list, []string{"FPUSHFRONT", "5"})
	assert.Equal(t, []int{5, 10}, list.ToSlice())

	// Тест FDEL
	handleSListCommand(list, []string{"FDEL", "5"})
	assert.Equal(t, []int{10}, list.ToSlice())

	// Тест ошибок
	handleSListCommand(list, []string{"FPUSH"}) // недостаточно аргументов
	handleSListCommand(list, []string{"UNKNOWN"}) // неизвестная команда
}

func TestHandleDListCommand(t *testing.T) {
	list := &DoublyLinkedList{}

	// Тест LPUSH
	handleDListCommand(list, []string{"LPUSH", "10"})
	assert.Equal(t, []int{10}, list.ToSlice())

	// Тест LPUSHFRONT
	handleDListCommand(list, []string{"LPUSHFRONT", "5"})
	assert.Equal(t, []int{5, 10}, list.ToSlice())

	// Тест ошибок
	handleDListCommand(list, []string{"LPUSH"}) // недостаточно аргументов
}

func TestHandleStackCommand(t *testing.T) {
	stack := &Stack{}

	// Тест SPUSH
	handleStackCommand(stack, []string{"SPUSH", "10"})
	assert.Equal(t, []int{10}, stack.toSlice())

	// Тест SPOP
	handleStackCommand(stack, []string{"SPOP"})
	assert.Equal(t, []int{}, stack.toSlice())

	// Тест ошибок
	handleStackCommand(stack, []string{"SPUSH"}) // недостаточно аргументов
}

func TestHandleQueueCommand(t *testing.T) {
	queue := &Queue{}

	// Тест QPUSH
	handleQueueCommand(queue, []string{"QPUSH", "10"})
	assert.Equal(t, []int{10}, queue.toSlice())

	// Тест QPOP
	handleQueueCommand(queue, []string{"QPOP"})
	assert.Equal(t, []int{}, queue.toSlice())

	// Тест ошибок
	handleQueueCommand(queue, []string{"QPUSH"}) // недостаточно аргументов
}

func TestHandleHashTableCommand(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)

	// Тест HINSERT
	handleHashTableCommand(ht, []string{"HINSERT", "1", "100"})
	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	// Тест HGET
	handleHashTableCommand(ht, []string{"HGET", "1"})

	// Тест HDEL
	handleHashTableCommand(ht, []string{"HDEL", "1"})
	_, ok = ht.Get(1)
	assert.False(t, ok)

	// Тест HCLEAR
	handleHashTableCommand(ht, []string{"HINSERT", "2", "200"})
	handleHashTableCommand(ht, []string{"HCLEAR"})
	_, ok = ht.Get(2)
	assert.False(t, ok)

	// Тест HSETTYPE
	handleHashTableCommand(ht, []string{"HSETTYPE", "CUCKOO"})
	assert.Equal(t, CUCKOO_HASHING, ht.htype)

	// Тест ошибок
	handleHashTableCommand(ht, []string{"HINSERT"}) // недостаточно аргументов
}

func TestExecuteCommand(t *testing.T) {
	// Тест команд массива
	executeCommand("MPUSH 10")
	executeCommand("PRINTM")

	// Тест команд списков
	executeCommand("FPUSH 20")
	executeCommand("LPUSH 30")

	// Тест команд стека и очереди
	executeCommand("SPUSH 40")
	executeCommand("QPUSH 50")

	// Тест команд хеш-таблицы
	executeCommand("HINSERT 1 100")

	// Тест неизвестной команды
	executeCommand("UNKNOWN_COMMAND")

	// Тест пустой команды
	executeCommand("")
}

func TestHandleArrayCommandFull(t *testing.T) {
	arr := &Array{}

	// Тест MINDEX
	handleArrayCommand(arr, []string{"MINDEX", "0", "10"})
	assert.Equal(t, []int{10}, arr.data)

	// Тест MGET
	handleArrayCommand(arr, []string{"MGET", "0"})

	// Тест MSET
	handleArrayCommand(arr, []string{"MSET", "0", "99"})
	assert.Equal(t, 99, arr.Get(0))

	// Тест MDEL
	handleArrayCommand(arr, []string{"MDEL", "0"})
	assert.Equal(t, []int{}, arr.data)

	// Тест ошибок MINDEX
	handleArrayCommand(arr, []string{"MINDEX"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MINDEX", "abc", "10"}) 	// неверные параметры

	// Тест ошибок MGET
	handleArrayCommand(arr, []string{"MGET"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MGET", "abc"}) 		// неверный индекс

	// Тест ошибок MSET
	handleArrayCommand(arr, []string{"MSET"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MSET", "abc", "10"}) 		// неверные параметры

	// Тест ошибок MDEL
	handleArrayCommand(arr, []string{"MDEL"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MDEL", "abc"}) 		// неверный индекс
}

func TestHandleSListCommandFull(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack(1)
	list.PushBack(3)

	// Тест FINSERTBEFORE
	handleSListCommand(list, []string{"FINSERTBEFORE", "3", "2"})
	assert.Equal(t, []int{1, 2, 3}, list.ToSlice())

	// Тест FINSERTAFTER
	handleSListCommand(list, []string{"FINSERTAFTER", "3", "4"})
	assert.Equal(t, []int{1, 2, 3, 4}, list.ToSlice())

	// Тест FGET
	handleSListCommand(list, []string{"FGET", "0"})

	// Тест FCONTAINS
	handleSListCommand(list, []string{"FCONTAINS", "2"})
	handleSListCommand(list, []string{"FCONTAINS", "999"})

	// Тест FDELFRONT
	handleSListCommand(list, []string{"FDELFRONT"})
	assert.Equal(t, []int{2, 3, 4}, list.ToSlice())

	// Тест FDELBACK
	handleSListCommand(list, []string{"FDELBACK"})
	assert.Equal(t, []int{2, 3}, list.ToSlice())

	// Тест PRINTF
	handleSListCommand(list, []string{"PRINTF"})

	// Тест ошибок FINSERTBEFORE
	handleSListCommand(list, []string{"FINSERTBEFORE"}) 	// недостаточно аргументов

	// Тест ошибок FINSERTAFTER
	handleSListCommand(list, []string{"FINSERTAFTER"}) 	// недостаточно аргументов

	// Тест ошибок FGET
	handleSListCommand(list, []string{"FGET"}) 		// недостаточно аргументов

	// Тест ошибок FCONTAINS
	handleSListCommand(list, []string{"FCONTAINS"}) 	// недостаточно аргументов
}

func TestHandleDListCommandFull(t *testing.T) {
	list := &DoublyLinkedList{}
	list.PushBack(1)
	list.PushBack(3)

	// Тест LINSERTBEFORE
	handleDListCommand(list, []string{"LINSERTBEFORE", "3", "2"})
	assert.Equal(t, []int{1, 2, 3}, list.ToSlice())

	// Тест LINSERTAFTER
	handleDListCommand(list, []string{"LINSERTAFTER", "3", "4"})
	assert.Equal(t, []int{1, 2, 3, 4}, list.ToSlice())

	// Тест LGET
	handleDListCommand(list, []string{"LGET", "0"})

	// Тест LCONTAINS
	handleDListCommand(list, []string{"LCONTAINS", "2"})
	handleDListCommand(list, []string{"LCONTAINS", "999"})

	// Тест LDELFRONT
	handleDListCommand(list, []string{"LDELFRONT"})
	assert.Equal(t, []int{2, 3, 4}, list.ToSlice())

	// Тест LDELBACK
	handleDListCommand(list, []string{"LDELBACK"})
	assert.Equal(t, []int{2, 3}, list.ToSlice())

	// Тест PRINTL
	handleDListCommand(list, []string{"PRINTL"})

	// Тест ошибок LINSERTBEFORE
	handleDListCommand(list, []string{"LINSERTBEFORE"}) 			// недостаточно аргументов
	handleDListCommand(list, []string{"LINSERTBEFORE", "abc", "2"}) 	// неверные параметры

	// Тест ошибок LINSERTAFTER
	handleDListCommand(list, []string{"LINSERTAFTER"}) 			// недостаточно аргументов
	handleDListCommand(list, []string{"LINSERTAFTER", "abc", "2"}) 		// неверные параметры

	// Тест ошибок LGET
	handleDListCommand(list, []string{"LGET"}) 				// недостаточно аргументов
	handleDListCommand(list, []string{"LGET", "abc"}) 			// неверный индекс

	// Тест ошибок LCONTAINS
	handleDListCommand(list, []string{"LCONTAINS"}) 			// недостаточно аргументов
	handleDListCommand(list, []string{"LCONTAINS", "abc"}) 			// неверное значение

	// Тест ошибок LDEL
	handleDListCommand(list, []string{"LDEL"}) 				// недостаточно аргументов
	handleDListCommand(list, []string{"LDEL", "abc"}) 			// неверное значение
}

func TestHandleSerializationCommand(t *testing.T) {
	// Подготовим данные для тестирования
	globalArray.Push(1)
	globalArray.Push(2)
	globalSList.PushBack(3)
	globalSList.PushBack(4)
	globalDList.PushBack(5)
	globalDList.PushBack(6)
	globalStack.Push(7)
	globalQueue.Push(8)
	globalHashTable.Insert(9, 900)

	// Тест сериализации массива
	handleSerializationCommand([]string{"SAVE_BINARY", "test_array.bin"})
	handleSerializationCommand([]string{"LOAD_BINARY", "test_array.bin"})
	handleSerializationCommand([]string{"SAVE_TEXT", "test_array.txt"})
	handleSerializationCommand([]string{"LOAD_TEXT", "test_array.txt"})

	// Тест сериализации односвязного списка
	handleSerializationCommand([]string{"SAVE_BINARY", "test_slist.bin"})
	handleSerializationCommand([]string{"LOAD_BINARY", "test_slist.bin"})
	handleSerializationCommand([]string{"SAVE_TEXT", "test_slist.txt"})
	handleSerializationCommand([]string{"LOAD_TEXT", "test_slist.txt"})

	// Тест сериализации двусвязного списка
	handleSerializationCommand([]string{"SAVE_BINARY", "test_dlist.bin"})
	handleSerializationCommand([]string{"LOAD_BINARY", "test_dlist.bin"})
	handleSerializationCommand([]string{"SAVE_TEXT", "test_dlist.txt"})
	handleSerializationCommand([]string{"LOAD_TEXT", "test_dlist.txt"})

	// Тест сериализации стека
	handleSerializationCommand([]string{"SAVE_BINARY", "test_stack.bin"})
	handleSerializationCommand([]string{"LOAD_BINARY", "test_stack.bin"})
	handleSerializationCommand([]string{"SAVE_TEXT", "test_stack.txt"})
	handleSerializationCommand([]string{"LOAD_TEXT", "test_stack.txt"})

	// Тест сериализации очереди
	handleSerializationCommand([]string{"SAVE_BINARY", "test_queue.bin"})
	handleSerializationCommand([]string{"LOAD_BINARY", "test_queue.bin"})
	handleSerializationCommand([]string{"SAVE_TEXT", "test_queue.txt"})
	handleSerializationCommand([]string{"LOAD_TEXT", "test_queue.txt"})

	// Тест сериализации хеш-таблицы
	handleSerializationCommand([]string{"SAVE_BINARY", "test_hash.bin"})
	handleSerializationCommand([]string{"LOAD_BINARY", "test_hash.bin"})
	handleSerializationCommand([]string{"SAVE_TEXT", "test_hash.txt"})
	handleSerializationCommand([]string{"LOAD_TEXT", "test_hash.txt"})

	// Тест ошибок
	handleSerializationCommand([]string{"SAVE_BINARY"}) // недостаточно аргументов
	handleSerializationCommand([]string{"LOAD_BINARY"}) // недостаточно аргументов

	// Тест неизвестного типа файла
	handleSerializationCommand([]string{"SAVE_BINARY", "test_unknown.xyz"})

	// Очистка
	os.Remove("test_array.bin")
	os.Remove("test_array.txt")
	os.Remove("test_slist.bin")
	os.Remove("test_slist.txt")
	os.Remove("test_dlist.bin")
	os.Remove("test_dlist.txt")
	os.Remove("test_stack.bin")
	os.Remove("test_stack.txt")
	os.Remove("test_queue.bin")
	os.Remove("test_queue.txt")
	os.Remove("test_hash.bin")
	os.Remove("test_hash.txt")

	// Очищаем глобальные переменные для следующих тестов
	globalArray = Array{}
	globalSList = SinglyLinkedList{}
	globalDList = DoublyLinkedList{}
	globalStack = Stack{}
	globalQueue = Queue{}
	globalHashTable = NewHashTable(11, DOUBLE_HASHING)
}

func TestExecuteCommandSerialization(t *testing.T) {
	// Тест команд сериализации через executeCommand
	executeCommand("SAVE_BINARY test_exec_array.bin")
	executeCommand("LOAD_BINARY test_exec_array.bin")
	executeCommand("SAVE_TEXT test_exec_array.txt")
	executeCommand("LOAD_TEXT test_exec_array.txt")

	// Очистка
	os.Remove("test_exec_array.bin")
	os.Remove("test_exec_array.txt")
}

func TestHandleArrayCommandErrors(t *testing.T) {
	arr := &Array{}

	// Тест ошибок в MPUSH
	handleArrayCommand(arr, []string{"MPUSH"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MPUSH", "abc"}) 		// неверное значение

	// Тест ошибок в MINDEX
	handleArrayCommand(arr, []string{"MINDEX"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MINDEX", "abc", "10"}) 	// неверные параметры
	handleArrayCommand(arr, []string{"MINDEX", "0", "def"}) 	// неверные параметры

	// Тест ошибок в MGET
	handleArrayCommand(arr, []string{"MGET"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MGET", "abc"}) 		// неверный индекс

	// Тест ошибок в MSET
	handleArrayCommand(arr, []string{"MSET"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MSET", "abc", "10"}) 		// неверные параметры
	handleArrayCommand(arr, []string{"MSET", "0", "def"}) 		// неверные параметры

	// Тест ошибок в MDEL
	handleArrayCommand(arr, []string{"MDEL"}) 			// недостаточно аргументов
	handleArrayCommand(arr, []string{"MDEL", "abc"}) 		// неверный индекс

	// Тест неизвестной команды
	handleArrayCommand(arr, []string{"UNKNOWN_COMMAND"})
}

func TestHandleSListCommandErrors(t *testing.T) {
	list := &SinglyLinkedList{}

	// Тест ошибок в FPUSH
	handleSListCommand(list, []string{"FPUSH"}) 				// недостаточно аргументов
	handleSListCommand(list, []string{"FPUSH", "abc"}) 			// неверное значение

	// Тест ошибок в FPUSHFRONT
	handleSListCommand(list, []string{"FPUSHFRONT"}) 			// недостаточно аргументов
	handleSListCommand(list, []string{"FPUSHFRONT", "abc"}) 		// неверное значение

	// Тест ошибок в FINSERTBEFORE
	handleSListCommand(list, []string{"FINSERTBEFORE"}) 			// недостаточно аргументов
	handleSListCommand(list, []string{"FINSERTBEFORE", "abc", "10"}) 	// неверные параметры

	// Тест ошибок в FINSERTAFTER
	handleSListCommand(list, []string{"FINSERTAFTER"}) 			// недостаточно аргументов
	handleSListCommand(list, []string{"FINSERTAFTER", "abc", "10"}) 	// неверные параметры

	// Тест ошибок в FDEL
	handleSListCommand(list, []string{"FDEL"}) 				// недостаточно аргументов
	handleSListCommand(list, []string{"FDEL", "abc"}) 			// неверное значение

	// Тест ошибок в FGET
	handleSListCommand(list, []string{"FGET"}) 				// недостаточно аргументов
	handleSListCommand(list, []string{"FGET", "abc"}) 			// неверный индекс

	// Тест ошибок в FCONTAINS
	handleSListCommand(list, []string{"FCONTAINS"}) 			// недостаточно аргументов
	handleSListCommand(list, []string{"FCONTAINS", "abc"}) 			// неверное значение

	// Тест пустой команды
	handleSListCommand(list, []string{})
}

func TestHandleDListCommandErrors(t *testing.T) {
	list := &DoublyLinkedList{}

	// Тест ошибок в LPUSH
	handleDListCommand(list, []string{"LPUSH"}) 				// недостаточно аргументов
	handleDListCommand(list, []string{"LPUSH", "abc"}) 			// неверное значение

	// Тест ошибок в LPUSHFRONT
	handleDListCommand(list, []string{"LPUSHFRONT"}) 			// недостаточно аргументов
	handleDListCommand(list, []string{"LPUSHFRONT", "abc"}) 		// неверное значение

	// Тест ошибок в LINSERTBEFORE
	handleDListCommand(list, []string{"LINSERTBEFORE"}) 			// недостаточно аргументов
	handleDListCommand(list, []string{"LINSERTBEFORE", "abc", "10"}) 	// неверные параметры
	handleDListCommand(list, []string{"LINSERTBEFORE", "1", "def"}) 	// неверные параметры

	// Тест ошибок в LINSERTAFTER
	handleDListCommand(list, []string{"LINSERTAFTER"}) 			// недостаточно аргументов
	handleDListCommand(list, []string{"LINSERTAFTER", "abc", "10"}) 	// неверные параметры
	handleDListCommand(list, []string{"LINSERTAFTER", "1", "def"}) 		// неверные параметры

	// Тест ошибок в LDEL
	handleDListCommand(list, []string{"LDEL"}) 				// недостаточно аргументов
	handleDListCommand(list, []string{"LDEL", "abc"}) 			// неверное значение

	// Тест ошибок в LGET
	handleDListCommand(list, []string{"LGET"}) 				// недостаточно аргументов
	handleDListCommand(list, []string{"LGET", "abc"}) 			// неверный индекс

	// Тест ошибок в LCONTAINS
	handleDListCommand(list, []string{"LCONTAINS"}) 			// недостаточно аргументов
	handleDListCommand(list, []string{"LCONTAINS", "abc"}) 			// неверное значение

	// Тест пустой команды
	handleDListCommand(list, []string{})
}

func TestHandleStackCommandErrors(t *testing.T) {
	stack := &Stack{}

	// Тест пустой команды
	handleStackCommand(stack, []string{})

	// Тест ошибок в SPUSH
	handleStackCommand(stack, []string{"SPUSH"}) 			// недостаточно аргументов
	handleStackCommand(stack, []string{"SPUSH", "abc"}) 		// неверное значение

	// Тест ошибок в SPOP (пустой стек)
	handleStackCommand(stack, []string{"SPOP"})

	// Тест неизвестной команды
	handleStackCommand(stack, []string{"UNKNOWN_COMMAND"})
}

func TestHandleQueueCommandErrors(t *testing.T) {
	queue := &Queue{}

	// Тест пустой команды
	handleQueueCommand(queue, []string{})

	// Тест ошибок в QPUSH
	handleQueueCommand(queue, []string{"QPUSH"}) 			// недостаточно аргументов
	handleQueueCommand(queue, []string{"QPUSH", "abc"}) 		// неверное значение

	// Тест ошибок в QPOP (пустая очередь)
	handleQueueCommand(queue, []string{"QPOP"})

	// Тест неизвестной команды
	handleQueueCommand(queue, []string{"UNKNOWN_COMMAND"})
}

func TestHandleHashTableCommandErrors(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)

	// Тест пустой команды
	handleHashTableCommand(ht, []string{})

	// Тест ошибок в HINSERT
	handleHashTableCommand(ht, []string{"HINSERT"}) 		// недостаточно аргументов
	handleHashTableCommand(ht, []string{"HINSERT", "abc", "100"}) 	// неверные параметры
	handleHashTableCommand(ht, []string{"HINSERT", "1", "def"}) 	// неверные параметры

	// Тест ошибок в HGET
	handleHashTableCommand(ht, []string{"HGET"}) 			// недостаточно аргументов
	handleHashTableCommand(ht, []string{"HGET", "abc"}) 		// неверный ключ

	// Тест ошибок в HDEL
	handleHashTableCommand(ht, []string{"HDEL"}) 			// недостаточно аргументов
	handleHashTableCommand(ht, []string{"HDEL", "abc"}) 		// неверный ключ

	// Тест ошибок в HSETTYPE
	handleHashTableCommand(ht, []string{"HSETTYPE"}) 		// недостаточно аргументов
	handleHashTableCommand(ht, []string{"HSETTYPE", "INVALID"}) 	// неверный тип

	// Тест неизвестной команды
	handleHashTableCommand(ht, []string{"UNKNOWN_COMMAND"})
}

func TestExecuteCommandEdgeCases(t *testing.T) {
	// Тест пустой команды
	executeCommand("")

	// Тест команды с лишними пробелами
	executeCommand("  MPUSH  10  ")

	// Тест неизвестной команды сериализации
	executeCommand("UNKNOWN_SERIALIZATION test.txt")
}

func TestStackQueuePrintMethods(t *testing.T) {

	// Тест методов Print
	stack := &Stack{}
	// Тест пустого стека
	assert.NotPanics(t, func() {
		stack.Print()
	})

	// Тест стека с элементами
	stack.Push(1)
	stack.Push(2)
	stack.Push(3)
	assert.NotPanics(t, func() {
		stack.Print()
	})

	queue := &Queue{}
	// Тест пустой очереди
	assert.NotPanics(t, func() {
		queue.Print()
	})

	// Тест очереди с элементами
	queue.Push(1)
	queue.Push(2)
	queue.Push(3)
	assert.NotPanics(t, func() {
		queue.Print()
	})
}

func TestHashTablePrintMethods(t *testing.T) {
	// Тест методов Print для хеш-таблицы

	ht := NewHashTable(11, DOUBLE_HASHING)
	// Тест пустой таблицы
	assert.NotPanics(t, func() {
		ht.Print()
	})

	// Тест таблицы с элементами
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	assert.NotPanics(t, func() {
		ht.Print()
	})
}

func TestListPrintMethods(t *testing.T) {

	// Тест методов Print для списков
	slist := &SinglyLinkedList{}

	// Тест пустого списка
	assert.NotPanics(t, func() {
		slist.Print()
	})

	// Тест списка с элементами
	slist.PushBack(1)
	slist.PushBack(2)
	assert.NotPanics(t, func() {
		slist.Print()
	})

	dlist := &DoublyLinkedList{}
	// Тест пустого списка
	assert.NotPanics(t, func() {
		dlist.Print()
	})

	// Тест списка с элементами
	dlist.PushBack(1)
	dlist.PushBack(2)
	assert.NotPanics(t, func() {
		dlist.Print()
	})
}

func TestArrayPrintMethod(t *testing.T) {

	// Тест метода Print для массива
	arr := &Array{}
	// Тест пустого массива
	assert.NotPanics(t, func() {
		arr.Print()
	})

	// Тест массива с элементами
	arr.Push(1)
	arr.Push(2)
	assert.NotPanics(t, func() {
		arr.Print()
	})
}

func captureOutput(f func()) string {
	// Перехватываем вывод в консоль
	var buf bytes.Buffer
	oldStdout := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	f()

	w.Close()
	os.Stdout = oldStdout
	buf.ReadFrom(r)
	return buf.String()
}

func TestArrayCommandOutputs(t *testing.T) {
	arr := &Array{}

	// Тест пустой команды
	output := captureOutput(func() {
		handleArrayCommand(arr, []string{})
	})
	assert.Contains(t, output, "Ошибка: пустая команда для массива")

	// Тест ошибки удаления (индекс вне диапазона)
	output = captureOutput(func() {
		handleArrayCommand(arr, []string{"MDEL", "10"})
	})
	assert.Contains(t, output, "Удаление не выполнено (индекс вне диапазона)")

	// Тест успешного удаления
	arr.Push(1)
	output = captureOutput(func() {
		handleArrayCommand(arr, []string{"MDEL", "0"})
	})
	assert.Contains(t, output, "-> удалён элемент по индексу 0")
}

func TestSinglyListCommandOutputs(t *testing.T) {
	list := &SinglyLinkedList{}

	// Тест ошибок пустого списка
	output := captureOutput(func() {
		handleSListCommand(list, []string{"FDELFRONT"})
	})
	assert.Contains(t, output, "Ошибка: список пуст")

	output = captureOutput(func() {
		handleSListCommand(list, []string{"FDELBACK"})
	})
	assert.Contains(t, output, "Ошибка: список пуст")

	// Тест элемента "не найден"
	list.PushBack(1)
	output = captureOutput(func() {
		handleSListCommand(list, []string{"FINSERTBEFORE", "999", "2"})
	})
	assert.Contains(t, output, "Элемент 999 не найден")

	output = captureOutput(func() {
		handleSListCommand(list, []string{"FINSERTAFTER", "999", "2"})
	})
	assert.Contains(t, output, "Элемент 999 не найден")

	output = captureOutput(func() {
		handleSListCommand(list, []string{"FDEL", "999"})
	})
	assert.Contains(t, output, "Элемент 999 не найден")

	// Тест успешных операций
	output = captureOutput(func() {
		handleSListCommand(list, []string{"FDELFRONT"})
	})
	assert.Contains(t, output, "-> удалён первый элемент")
}

func TestDoublyListCommandOutputs(t *testing.T) {
	list := &DoublyLinkedList{}

	// Тест успешного удаления и "не найден"
	list.PushBack(1)
	output := captureOutput(func() {
		handleDListCommand(list, []string{"LDEL", "1"})
	})
	assert.Contains(t, output, "-> удалён 1")

	output = captureOutput(func() {
		handleDListCommand(list, []string{"LDEL", "999"})
	})
	assert.Contains(t, output, "Элемент 999 не найден")

	// Тест неизвестной команды
	output = captureOutput(func() {
		handleDListCommand(list, []string{"UNKNOWN_CMD"})
	})
	assert.Contains(t, output, "Неизвестная команда: UNKNOWN_CMD")

	// Тест PRINTL
	list.PushBack(1)
	list.PushBack(2)
	output = captureOutput(func() {
		handleDListCommand(list, []string{"PRINTL"})
	})
	assert.Contains(t, output, "->")
}

func TestHashTableCommandOutputs(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)

	// Тест ключ не найден
	output := captureOutput(func() {
		handleHashTableCommand(ht, []string{"HGET", "999"})
	})
	assert.Contains(t, output, "-> ключ 999 не найден")

	output = captureOutput(func() {
		handleHashTableCommand(ht, []string{"HDEL", "999"})
	})
	assert.Contains(t, output, "-> ключ 999 не найден")

	// Тест PRINTH
	output = captureOutput(func() {
		handleHashTableCommand(ht, []string{"PRINTH"})
	})
	assert.Contains(t, output, "-> Хеш-таблица:")

	// Тест установки типов
	output = captureOutput(func() {
		handleHashTableCommand(ht, []string{"HSETTYPE", "DOUBLE"})
	})
	assert.Contains(t, output, "-> установлен тип: DOUBLE_HASHING")

	output = captureOutput(func() {
		handleHashTableCommand(ht, []string{"HSETTYPE", "FOLDING"})
	})
	assert.Contains(t, output, "-> установлен тип: FOLDING_HASHING")

	output = captureOutput(func() {
		handleHashTableCommand(ht, []string{"HSETTYPE", "CUCKOO"})
	})
	assert.Contains(t, output, "-> установлен тип: CUCKOO_HASHING")
}

func TestSerializationCommandOutputs(t *testing.T) {
	// Подготовим данные
	globalArray.Push(1)
	globalSList.PushBack(2)

	// Тест успешной сериализации массива
	output := captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_BINARY", "test_array_output.bin"})
	})
	assert.Contains(t, output, "-> массив сохранен в бинарный файл")

	output = captureOutput(func() {
		handleSerializationCommand([]string{"LOAD_BINARY", "test_array_output.bin"})
	})
	assert.Contains(t, output, "-> массив загружен из бинарного файла")

	output = captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_TEXT", "test_array_output.txt"})
	})
	assert.Contains(t, output, "-> массив сохранен в текстовый файл")

	output = captureOutput(func() {
		handleSerializationCommand([]string{"LOAD_TEXT", "test_array_output.txt"})
	})
	assert.Contains(t, output, "-> массив загружен из текстового файла")

	// Тест успешной сериализации односвязного списка
	output = captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_BINARY", "test_slist_output.bin"})
	})
	assert.Contains(t, output, "-> односвязный список сохранен в бинарный файл")

	output = captureOutput(func() {
		handleSerializationCommand([]string{"LOAD_BINARY", "test_slist_output.bin"})
	})
	assert.Contains(t, output, "-> односвязный список загружен из бинарного файла")

	output = captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_TEXT", "test_slist_output.txt"})
	})
	assert.Contains(t, output, "-> односвязный список сохранен в текстовый файл")

	output = captureOutput(func() {
		handleSerializationCommand([]string{"LOAD_TEXT", "test_slist_output.txt"})
	})
	assert.Contains(t, output, "-> односвязный список загружен из текстового файла")

	// Очистка
	os.Remove("test_array_output.bin")
	os.Remove("test_array_output.txt")
	os.Remove("test_slist_output.bin")
	os.Remove("test_slist_output.txt")

	// Сбрасываем глобальные переменные
	globalArray = Array{}
	globalSList = SinglyLinkedList{}
}

// Тест вывода для всех структур данных
func TestAllStructuresSerializationOutputs(t *testing.T) {

	// Подготовим данные для всех структур
	globalArray.Push(1)
	globalSList.PushBack(2)
	globalDList.PushBack(3)
	globalStack.Push(4)
	globalQueue.Push(5)
	globalHashTable.Insert(6, 600)

	// Тест двусвязного списка
	output := captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_BINARY", "test_dlist.bin"})
	})
	assert.Contains(t, output, "-> двусвязный список сохранен в бинарный файл")

	// Тест стека
	output = captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_BINARY", "test_stack.bin"})
	})
	assert.Contains(t, output, "-> стек сохранен в бинарный файл")

	// Тест очереди
	output = captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_BINARY", "test_queue.bin"})
	})
	assert.Contains(t, output, "-> очередь сохранена в бинарный файл")

	// Тест хеш-таблицы
	output = captureOutput(func() {
		handleSerializationCommand([]string{"SAVE_BINARY", "test_hash.bin"})
	})
	assert.Contains(t, output, "-> хеш-таблица сохранена в бинарный файл")

	// Очистка
	os.Remove("test_dlist.bin")
	os.Remove("test_stack.bin")
	os.Remove("test_queue.bin")
	os.Remove("test_hash.bin")

	// Сбрасываем глобальные переменные
	ResetGlobals()
}
