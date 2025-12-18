package main

import (
	"os"
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestHashTableInsertGet(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)
	ht.Insert(1, 100)
	ht.Insert(2, 200)

	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	val, ok = ht.Get(2)
	assert.True(t, ok)
	assert.Equal(t, 200, val)

	// Несуществующий ключ
	val, ok = ht.Get(3)
	assert.False(t, ok)
}

func TestHashTableRemove(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)
	ht.Insert(1, 100)

	result := ht.Remove(1)
	assert.True(t, result)

	// Повторное удаление
	result = ht.Remove(1)
	assert.False(t, result)
}

func TestHashTableEdgeCases(t *testing.T) {
	ht := NewHashTable(5, DOUBLE_HASHING)

	// Тест пустой таблицы
	val, ok := ht.Get(1)
	assert.False(t, ok)
	assert.Equal(t, -1, val)

	assert.False(t, ht.Remove(1))

	// Печать пустой таблицы
	assert.NotPanics(t, func() {
		ht.Print()
	})
}

func TestHashTableToFromSlice(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)

	// Тест ToSlice с пустой таблицей
	assert.Equal(t, []string{}, ht.ToSlice())

	// Тест FromSlice
	data := []string{"1 100", "2 200", "3 300"}
	ht.FromSlice(data)

	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	val, ok = ht.Get(2)
	assert.True(t, ok)
	assert.Equal(t, 200, val)
}

func TestHashTableClear(t *testing.T) {
	ht := NewHashTable(11, DOUBLE_HASHING)
	ht.Insert(1, 100)
	ht.Insert(2, 200)

	// Проверяем что элементы есть до очистки
	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	ht.Clear()

	// Проверяем что элементов нет после очистки
	val, ok = ht.Get(1)
	assert.False(t, ok)

	val, ok = ht.Get(2)
	assert.False(t, ok)
}

func TestHashTableDifferentTypes(t *testing.T) {
	// Тест DOUBLE_HASHING
	ht1 := NewHashTable(11, DOUBLE_HASHING)
	ht1.Insert(1, 100)
	ht1.Insert(2, 200)
	val, ok := ht1.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	// Тест CUCKOO_HASHING
	ht2 := NewHashTable(11, CUCKOO_HASHING)
	ht2.Insert(1, 100)
	ht2.Insert(2, 200)
	val, ok = ht2.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	// Тест FOLDING_HASHING
	ht3 := NewHashTable(11, FOLDING_HASHING)
	ht3.Insert(1, 100)
	ht3.Insert(2, 200)
	val, ok = ht3.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)
}

func TestHashTableRehash(t *testing.T) {
	ht := NewHashTable(3, DOUBLE_HASHING)

	// Добавляем элементы чтобы вызвать рехэширование
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)
	ht.Insert(4, 400)

	// Проверяем, что все элементы доступны после рехэширования
	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	val, ok = ht.Get(4)
	assert.True(t, ok)
	assert.Equal(t, 400, val)
}

func TestHashTableCollisions(t *testing.T) {
	ht := NewHashTable(5, DOUBLE_HASHING)

	// Создаем коллизии
	ht.Insert(1, 100)
	ht.Insert(6, 200)

	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	val, ok = ht.Get(6)
	assert.True(t, ok)
	assert.Equal(t, 200, val)
}

func TestHashTableLoadFactor(t *testing.T) {
	ht := NewHashTable(10, DOUBLE_HASHING)

	// Начальный коэффициент загрузки
	initialLoad := ht.loadFactor()
	assert.Equal(t, 0.0, initialLoad)

	// Добавляем элементы
	ht.Insert(1, 100)
	ht.Insert(2, 200)

	newLoad := ht.loadFactor()
	assert.True(t, newLoad > 0.0)
}

func TestHashTableCuckooHashing(t *testing.T) {
	ht := NewHashTable(11, CUCKOO_HASHING)

	// Тест вставки с вытеснением (кукушкин метод)
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)

	// Проверяем что все элементы на месте
	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	val, ok = ht.Get(2)
	assert.True(t, ok)
	assert.Equal(t, 200, val)

	val, ok = ht.Get(3)
	assert.True(t, ok)
	assert.Equal(t, 300, val)
}

func TestHashTableCuckooRehash(t *testing.T) {
	ht := NewHashTable(3, CUCKOO_HASHING)

	// Добавляем элементы чтобы вызвать рехэширование
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)
	ht.Insert(4, 400)

	// Проверяем, что все элементы доступны после рехэширования
	val, ok := ht.Get(4)
	assert.True(t, ok)
	assert.Equal(t, 400, val)
}

func TestHashTableRemoveDifferentTypes(t *testing.T) {
	// Тест FOLDING_HASHING
	ht1 := NewHashTable(11, FOLDING_HASHING)
	ht1.Insert(1, 100)
	assert.True(t, ht1.Remove(1))
	assert.False(t, ht1.Remove(999)) // несуществующий ключ

	// Тест CUCKOO_HASHING
	ht2 := NewHashTable(11, CUCKOO_HASHING)
	ht2.Insert(1, 100)
	ht2.Insert(2, 200)
	assert.True(t, ht2.Remove(1))
	assert.True(t, ht2.Remove(2))
	assert.False(t, ht2.Remove(999)) // несуществующий ключ
}

func TestHashTableFoldingHashVerbose(t *testing.T) {
	ht := NewHashTable(11, FOLDING_HASHING)

	index := ht.foldingHash(123456, true)
	assert.True(t, index >= 0 && index < ht.size)

	index = ht.foldingHash(789, false)
	assert.True(t, index >= 0 && index < ht.size)
}

func TestHashTableCuckooDisplacement(t *testing.T) {
	// Тест вытеснения элементов в кукушкином хешировании
	ht := NewHashTable(5, CUCKOO_HASHING)

	// Создаем ситуацию для вытеснения
	ht.Insert(1, 100)
	ht.Insert(6, 200)
	ht.Insert(11, 300)

	// Проверяем, что все элементы на месте после вытеснений
	val, ok := ht.Get(1)
	assert.True(t, ok)
	assert.Equal(t, 100, val)

	val, ok = ht.Get(6)
	assert.True(t, ok)
	assert.Equal(t, 200, val)

	val, ok = ht.Get(11)
	assert.True(t, ok)
	assert.Equal(t, 300, val)
}

func TestHashTableCuckooMaxIterations(t *testing.T) {
	// Тест достижения максимального количества итераций
	ht := NewHashTable(3, CUCKOO_HASHING)

	// Создаем много коллизий чтобы вызвать рехэширование
	ht.Insert(1, 100)
	ht.Insert(4, 400)
	ht.Insert(7, 700)
	ht.Insert(10, 1000)

	// Проверяем, что все элементы доступны
	val, ok := ht.Get(10)
	assert.True(t, ok)
	assert.Equal(t, 1000, val)
}

func TestHashTableDoubleHashingRehash(t *testing.T) {

	// Тест рехэширования в double hashing
	ht := NewHashTable(3, DOUBLE_HASHING)

	// Заполняем таблицу чтобы вызвать рехэширование
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)
	ht.Insert(4, 400)

	// Проверяем, что размер увеличился и элементы на месте
	assert.True(t, ht.size > 3)

	val, ok := ht.Get(4)
	assert.True(t, ok)
	assert.Equal(t, 400, val)
}

func TestHashTableFoldingRehash(t *testing.T) {

	// Тест рехэширования в folding hashing
	ht := NewHashTable(3, FOLDING_HASHING)

	// Заполняем таблицу чтобы вызвать рехэширование
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)
	ht.Insert(4, 400)

	// Проверяем, что элементы доступны после рехэширования
	val, ok := ht.Get(4)
	assert.True(t, ok)
	assert.Equal(t, 400, val)
}

func TestHashTableSerializationTypes(t *testing.T) {
	// Тест сериализации разных типов хеширования

	// DOUBLE_HASHING
	ht1 := NewHashTable(11, DOUBLE_HASHING)
	ht1.Insert(1, 100)
	err := ht1.SerializeText("test_double.txt")
	assert.NoError(t, err)

	// CUCKOO_HASHING
	ht2 := NewHashTable(11, CUCKOO_HASHING)
	ht2.Insert(2, 200)
	err = ht2.SerializeText("test_cuckoo.txt")
	assert.NoError(t, err)

	// FOLDING_HASHING
	ht3 := NewHashTable(11, FOLDING_HASHING)
	ht3.Insert(3, 300)
	err = ht3.SerializeText("test_folding.txt")
	assert.NoError(t, err)

	// Проверяем, что файлы создались и содержат правильные типы
	data, err := os.ReadFile("test_double.txt")
	assert.NoError(t, err)
	assert.Contains(t, string(data), "TYPE DOUBLE")

	data, err = os.ReadFile("test_cuckoo.txt")
	assert.NoError(t, err)
	assert.Contains(t, string(data), "TYPE CUCKOO")

	data, err = os.ReadFile("test_folding.txt")
	assert.NoError(t, err)
	assert.Contains(t, string(data), "TYPE FOLDING")

	// Очистка
	os.Remove("test_double.txt")
	os.Remove("test_cuckoo.txt")
	os.Remove("test_folding.txt")
}

func TestHashTableRehashRecursion(t *testing.T) {
	// Тест рекурсивного вызова Insert после рехэширования
	ht := NewHashTable(2, DOUBLE_HASHING)

	// Добавляем элементы чтобы вызвать multiple rehashes
	ht.Insert(1, 100)
	ht.Insert(2, 200)
	ht.Insert(3, 300)
	ht.Insert(4, 400)
	ht.Insert(5, 500)

	// Проверяем, что все элементы доступны
	for i := 1; i <= 5; i++ {
		val, ok := ht.Get(i)
		assert.True(t, ok)
		assert.Equal(t, i*100, val)
	}
}

func TestHashTableCuckooComplexDisplacement(t *testing.T) {
	// Тест сложного сценария вытеснения в кукушкином хешировании
	ht := NewHashTable(7, CUCKOO_HASHING)

	// Ключи специально подобраны для создания цепочки вытеснений
	keys := []int{1, 8, 15, 22, 29}

	for i, key := range keys {
		ht.Insert(key, key*10)

		// Проверяем, что все предыдущие элементы все еще доступны
		for j := 0; j <= i; j++ {
			val, ok := ht.Get(keys[j])
			assert.True(t, ok, "Key %d should be accessible after inserting key %d", keys[j], key)
			assert.Equal(t, keys[j]*10, val)
		}
	}
}


