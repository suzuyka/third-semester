package main

import (
	"bufio"
	"encoding/binary"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Типы хеширования
type HashType int

const (
	DOUBLE_HASHING HashType = iota
	CUCKOO_HASHING
	FOLDING_HASHING
)

// Элемент хеш-таблицы
type HashEntry struct {
	key   int
	value int
	occupied bool
}

// Хеш-таблица
type HashTable struct {
	table []HashEntry
	size  int
	htype HashType
}

// Создание новой хеш-таблицы
func NewHashTable(size int, htype HashType) *HashTable {
	return &HashTable{
		table: make([]HashEntry, size),
		size:  size,
		htype: htype,
	}
}

// Основные хеш-функции
func (ht *HashTable) hashFunc1(key int) int {
	return key % ht.size
}

func (ht *HashTable) hashFunc2(key int) int {
	return 1 + (key % (ht.size - 1))
}

// Хеш-функция методом свёртки
func (ht *HashTable) foldingHash(key int, verbose bool) int {
	originalKey := key
	sum := 0
	var parts []int

	// Разбиваем по три цифры
	for key > 0 {
		part := key % 1000
		parts = append([]int{part}, parts...)
		sum += part
		key /= 1000
	}

	index := sum % ht.size

	if verbose {
		fmt.Printf("[Folding hash] Ключ: %d → части: ", originalKey)
		for i, part := range parts {
			fmt.Print(part)
			if i != len(parts)-1 {
				fmt.Print(" + ")
			}
		}
		fmt.Printf(" = %d → индекс: %d\n", sum, index)
	}

	return index
}

// Подсчёт коэффициента загрузки
func (ht *HashTable) loadFactor() float64 {
	filled := 0
	for i := 0; i < ht.size; i++ {
		if ht.table[i].occupied {
			filled++
		}
	}
	return float64(filled) / float64(ht.size)
}

// Рехэширование таблицы
func (ht *HashTable) rehash() {
	oldTable := ht.table
	oldSize := ht.size

	ht.size *= 2
	ht.table = make([]HashEntry, ht.size)

	for i := 0; i < oldSize; i++ {
		if oldTable[i].occupied {
			ht.Insert(oldTable[i].key, oldTable[i].value) // ИСПРАВЛЕНО: Insert
		}
	}
}

// Рехэширование для кукушкиного метода
func (ht *HashTable) cuckooRehash() {
	oldTable := ht.table
	oldSize := ht.size

	ht.size *= 2
	ht.table = make([]HashEntry, ht.size)

	for i := 0; i < oldSize; i++ {
		if oldTable[i].occupied {
			ht.insertCuckoo(oldTable[i].key, oldTable[i].value)
		}
	}
}

// Вставка для кукушкиного метода
func (ht *HashTable) insertCuckoo(key, value int) {
	keyToInsert := key
	valueToInsert := value
	const maxIter = 100 // защита от зацикливания

	for i := 0; i < maxIter; i++ {
		pos1 := ht.hashFunc1(keyToInsert)
		if !ht.table[pos1].occupied {
			ht.table[pos1] = HashEntry{key: keyToInsert, value: valueToInsert, occupied: true}
			return
		}

		// Вытесняем существующий элемент
		keyToInsert, ht.table[pos1].key = ht.table[pos1].key, keyToInsert
		valueToInsert, ht.table[pos1].value = ht.table[pos1].value, valueToInsert

		pos2 := ht.hashFunc2(keyToInsert)
		if !ht.table[pos2].occupied {
			ht.table[pos2] = HashEntry{key: keyToInsert, value: valueToInsert, occupied: true}
			return
		}

		// Снова вытесняем
		keyToInsert, ht.table[pos2].key = ht.table[pos2].key, keyToInsert
		valueToInsert, ht.table[pos2].value = ht.table[pos2].value, valueToInsert
	}

	// Если зациклились - расширяем таблицу
	ht.cuckooRehash()
	ht.insertCuckoo(keyToInsert, valueToInsert)
}

// Вставка элемента
func (ht *HashTable) Insert(key, value int) {
	if ht.loadFactor() > 0.7 {
		ht.rehash()
	}

	switch ht.htype {
		case FOLDING_HASHING:
			index := ht.foldingHash(key, true)
			if !ht.table[index].occupied || ht.table[index].key == key {
				ht.table[index] = HashEntry{key: key, value: value, occupied: true}
				return
			} else {
				ht.rehash()
				ht.Insert(key, value)
			}

		case DOUBLE_HASHING:
			h1 := ht.hashFunc1(key)
			h2 := ht.hashFunc2(key)

			for i := 0; i < ht.size; i++ {
				index := (h1 + i*h2) % ht.size
				if !ht.table[index].occupied || ht.table[index].key == key {
					ht.table[index] = HashEntry{key: key, value: value, occupied: true}
					return
				}
			}

			ht.rehash()
			ht.Insert(key, value)

		case CUCKOO_HASHING:
			ht.insertCuckoo(key, value)
	}
}

// Удаление элемента
func (ht *HashTable) Remove(key int) bool {
	switch ht.htype {
		case FOLDING_HASHING:
			index := ht.foldingHash(key, false)
			if index >= 0 && index < ht.size && ht.table[index].occupied && ht.table[index].key == key {
				ht.table[index].occupied = false
				return true
			}
			return false

		case CUCKOO_HASHING:
			i1 := ht.hashFunc1(key)
			i2 := ht.hashFunc2(key)
			if ht.table[i1].occupied && ht.table[i1].key == key {
				ht.table[i1].occupied = false
				return true
			}
			if ht.table[i2].occupied && ht.table[i2].key == key {
				ht.table[i2].occupied = false
				return true
			}
			return false

		default: // DOUBLE_HASHING
			h1 := ht.hashFunc1(key)
			h2 := ht.hashFunc2(key)
			for i := 0; i < ht.size; i++ {
				index := (h1 + i*h2) % ht.size
				if ht.table[index].occupied && ht.table[index].key == key {
					ht.table[index].occupied = false
					return true
				}
				if !ht.table[index].occupied {
					break
				}
			}
			return false
	}
}

// Поиск элемента
func (ht *HashTable) Get(key int) (int, bool) {
	switch ht.htype {
		case FOLDING_HASHING:
			index := ht.foldingHash(key, false)
			if index >= 0 && index < ht.size && ht.table[index].occupied && ht.table[index].key == key {
				return ht.table[index].value, true
			}
			return -1, false

		case CUCKOO_HASHING:
			i1 := ht.hashFunc1(key)
			i2 := ht.hashFunc2(key)
			if ht.table[i1].occupied && ht.table[i1].key == key {
				return ht.table[i1].value, true
			}
			if ht.table[i2].occupied && ht.table[i2].key == key {
				return ht.table[i2].value, true
			}
			return -1, false

		default: // DOUBLE_HASHING
			h1 := ht.hashFunc1(key)
			h2 := ht.hashFunc2(key)
			for i := 0; i < ht.size; i++ {
				index := (h1 + i*h2) % ht.size
				if !ht.table[index].occupied {
					return -1, false
				}
				if ht.table[index].occupied && ht.table[index].key == key {
					return ht.table[index].value, true
				}
			}
			return -1, false
	}
}

// Печать таблицы
func (ht *HashTable) Print() {
	for i := 0; i < ht.size; i++ {
		fmt.Printf("%d: ", i)
		if ht.table[i].occupied {
			fmt.Printf("(%d, %d)", ht.table[i].key, ht.table[i].value)
		}
		fmt.Println()
	}
}

// Преобразование в срез
func (ht *HashTable) ToSlice() []string {
	var result []string
	for i := 0; i < ht.size; i++ {
		if ht.table[i].occupied {
			result = append(result, fmt.Sprintf("%d %d", ht.table[i].key, ht.table[i].value))
		}
	}
	if result == nil {
		return []string{}
	}
	return result
}

// Загрузка из среза
func (ht *HashTable) FromSlice(data []string) {
	ht.table = make([]HashEntry, ht.size)
	for _, line := range data {
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			key, err1 := strconv.Atoi(parts[0])
			value, err2 := strconv.Atoi(parts[1])
			if err1 == nil && err2 == nil {
				ht.Insert(key, value)
			}
		}
	}
}

// Очистка таблицы
func (ht *HashTable) Clear() {
	ht.table = make([]HashEntry, ht.size)
}

// Бинарная сериализация
func (ht *HashTable) SerializeBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Записываем данные
	binary.Write(file, binary.LittleEndian, int32(ht.size))
	binary.Write(file, binary.LittleEndian, int32(ht.htype))

	// Записываем данные таблицы
	for i := 0; i < ht.size; i++ {
		occupied := ht.table[i].occupied
		binary.Write(file, binary.LittleEndian, occupied)
		if occupied {
			binary.Write(file, binary.LittleEndian, int32(ht.table[i].key))
			binary.Write(file, binary.LittleEndian, int32(ht.table[i].value))
		}
	}

	return nil
}

// Бинарная десериализация
func (ht *HashTable) DeserializeBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Читаем данные
	var size int32
	var htype int32
	binary.Read(file, binary.LittleEndian, &size)
	binary.Read(file, binary.LittleEndian, &htype)

	ht.size = int(size)
	ht.htype = HashType(htype)
	ht.table = make([]HashEntry, ht.size)

	// Читаем данные таблицы
	for i := 0; i < ht.size; i++ {
		var occupied bool
		binary.Read(file, binary.LittleEndian, &occupied)

		if occupied {
			var key, value int32
			binary.Read(file, binary.LittleEndian, &key)
			binary.Read(file, binary.LittleEndian, &value)
			ht.table[i] = HashEntry{key: int(key), value: int(value), occupied: true}
		} else {
			ht.table[i] = HashEntry{occupied: false}
		}
	}

	return nil
}

// Текстовая сериализация
func (ht *HashTable) SerializeText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Записываем данные
	fmt.Fprintf(file, "TYPE ")
	switch ht.htype {
		case DOUBLE_HASHING:
			fmt.Fprintln(file, "DOUBLE")
		case CUCKOO_HASHING:
			fmt.Fprintln(file, "CUCKOO")
		case FOLDING_HASHING:
			fmt.Fprintln(file, "FOLDING")
	}
	fmt.Fprintf(file, "SIZE %d\n", ht.size)

	// Записываем данные
	for i := 0; i < ht.size; i++ {
		if ht.table[i].occupied {
			fmt.Fprintf(file, "%d %d\n", ht.table[i].key, ht.table[i].value)
		}
	}

	return nil
}

// Текстовая десериализация
func (ht *HashTable) DeserializeText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	ht.Clear()

	// Читаем данные
	if scanner.Scan() {
		line := scanner.Text()
		if strings.HasPrefix(line, "TYPE ") {
			typeStr := strings.TrimPrefix(line, "TYPE ")
			switch typeStr {
				case "DOUBLE":
					ht.htype = DOUBLE_HASHING
				case "CUCKOO":
					ht.htype = CUCKOO_HASHING
				case "FOLDING":
					ht.htype = FOLDING_HASHING
			}
		}
	}

	if scanner.Scan() {
		line := scanner.Text()
		if strings.HasPrefix(line, "SIZE ") {
			sizeStr := strings.TrimPrefix(line, "SIZE ")
			if size, err := strconv.Atoi(sizeStr); err == nil {
				ht.size = size
				ht.table = make([]HashEntry, ht.size)
			}
		}
	}

	// Читаем данные
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Fields(line)
		if len(parts) >= 2 {
			key, err1 := strconv.Atoi(parts[0])
			value, err2 := strconv.Atoi(parts[1])
			if err1 == nil && err2 == nil {
				ht.Insert(key, value)
			}
		}
	}

	return scanner.Err()
}
