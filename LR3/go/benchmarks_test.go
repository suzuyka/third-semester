package main

import (
	"os"
	"testing"
)

// Бенчмарки для массива
func BenchmarkArrayPush(b *testing.B) {
	arr := &Array{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.Push(i)
	}
}

func BenchmarkArrayInsert(b *testing.B) {
	arr := &Array{}
	for i := 0; i < 1000; i++ {
		arr.Push(i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.Insert(500, i)
	}
}

func BenchmarkArrayGet(b *testing.B) {
	arr := &Array{}
	for i := 0; i < 1000; i++ {
		arr.Push(i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		_ = arr.Get(i % 1000)
	}
}

// Бенчмарки для односвязного списка
func BenchmarkSinglyListPushBack(b *testing.B) {
	list := &SinglyLinkedList{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.PushBack(i)
	}
}

func BenchmarkSinglyListPushFront(b *testing.B) {
	list := &SinglyLinkedList{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.PushFront(i)
	}
}

func BenchmarkSinglyListFind(b *testing.B) {
	list := &SinglyLinkedList{}
	for i := 0; i < 1000; i++ {
		list.PushBack(i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.Contains(i % 1000)
	}
}

// Бенчмарки для двусвязного списка
func BenchmarkDoublyListPushBack(b *testing.B) {
	list := &DoublyLinkedList{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.PushBack(i)
	}
}

func BenchmarkDoublyListPushFront(b *testing.B) {
	list := &DoublyLinkedList{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.PushFront(i)
	}
}

// Бенчмарки для стека
func BenchmarkStackPush(b *testing.B) {
	stack := &Stack{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		stack.Push(i)
	}
}

func BenchmarkStackPushPop(b *testing.B) {
	stack := &Stack{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		stack.Push(i)
		stack.Pop()
	}
}

// Бенчмарки для очереди
func BenchmarkQueuePush(b *testing.B) {
	queue := &Queue{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		queue.Push(i)
	}
}

func BenchmarkQueuePushPop(b *testing.B) {
	queue := &Queue{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		queue.Push(i)
		queue.Pop()
	}
}

// Бенчмарки для хеш-таблицы
func BenchmarkHashTableInsert(b *testing.B) {
	ht := NewHashTable(1000, DOUBLE_HASHING)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ht.Insert(i, i*10)
	}
}

func BenchmarkHashTableGet(b *testing.B) {
	ht := NewHashTable(1000, DOUBLE_HASHING)
	for i := 0; i < 1000; i++ {
		ht.Insert(i, i*10)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ht.Get(i % 1000)
	}
}

func BenchmarkHashTableInsertDoubleHashing(b *testing.B) {
	ht := NewHashTable(1000, DOUBLE_HASHING)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ht.Insert(i, i*10)
	}
}

func BenchmarkHashTableInsertCuckooHashing(b *testing.B) {
	ht := NewHashTable(1000, CUCKOO_HASHING)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ht.Insert(i, i*10)
	}
}

func BenchmarkHashTableInsertFoldingHashing(b *testing.B) {
	ht := NewHashTable(1000, FOLDING_HASHING)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		ht.Insert(i, i*10)
	}
}

// Бенчмарк сравнения разных методов хеширования
func BenchmarkHashTableComparison(b *testing.B) {
	b.Run("DoubleHashing", func(b *testing.B) {
		ht := NewHashTable(1000, DOUBLE_HASHING)
		for i := 0; i < b.N; i++ {
			ht.Insert(i%100, i*10)
		}
	})

	b.Run("CuckooHashing", func(b *testing.B) {
		ht := NewHashTable(1000, CUCKOO_HASHING)
		for i := 0; i < b.N; i++ {
			ht.Insert(i%100, i*10)
		}
	})

	b.Run("FoldingHashing", func(b *testing.B) {
		ht := NewHashTable(1000, FOLDING_HASHING)
		for i := 0; i < b.N; i++ {
			ht.Insert(i%100, i*10)
		}
	})
}

// Бенчмарк сериализации
func BenchmarkArraySerialization(b *testing.B) {
	arr := &Array{}
	for i := 0; i < 1000; i++ {
		arr.Push(i)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.SerializeBinary("bench_array.bin")
	}

	// Очистка
	b.StopTimer()
	os.Remove("bench_array.bin")
}
