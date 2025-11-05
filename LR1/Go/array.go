package main

import (
	"fmt"
)

const MAX_CAPACITY = 1000

type Array struct {
	data     []string
	size     int
	capacity int
}

// MCreate - создает массив
func MCreate(arr *Array) {
	initCapacity := 10
	arr.data = make([]string, initCapacity)
	arr.size = 0
	arr.capacity = initCapacity
}

// MResize - увеличивает capacity массива при необходимости
func MResize(arr *Array) {
	if arr.size >= arr.capacity {
		newCapacity := arr.capacity * 2
		if newCapacity > MAX_CAPACITY {
			newCapacity = MAX_CAPACITY
		}
		
		newData := make([]string, newCapacity)
		copy(newData, arr.data)
		
		arr.data = newData
		arr.capacity = newCapacity
	}
}

// MDelIndex - удаляет элемент по индексу
func MDelIndex(arr *Array, index int) {
	if index >= arr.size || index < 0 {
		fmt.Println("Error: Out of range")
		return
	}
	
	// Сдвигаем элементы влево
	for i := index; i < arr.size-1; i++ {
		arr.data[i] = arr.data[i+1]
	}
	arr.size--
	
	// Очищаем последний элемент
	if arr.size < len(arr.data) {
		arr.data[arr.size] = ""
	}
}

// OutputM - выводит весь массив
func OutputM(arr *Array) {
	fmt.Printf("Array [%d]: ", arr.size)
	for i := 0; i < arr.size; i++ {
		fmt.Printf("%s ", arr.data[i])
	}
	if arr.size == 0 {
		fmt.Print("Empty array")
	}
	fmt.Println()
}

// OutputMIndex - выводит элемент по индексу
func OutputMIndex(arr *Array, index int) {
	if index >= 0 && index < arr.size {
		fmt.Printf("Array element [%d] = %s\n", index, arr.data[index])
	} else {
		fmt.Println("Error: Index out of range")
	}
}

// MInsert - вставляет элемент по индексу
func MInsert(arr *Array, index int, key string) {
	if index >= MAX_CAPACITY {
		fmt.Println("Too large index")
		return
	}
	if index < 0 {
		fmt.Println("Error: incorrect index")
		return
	}
	
	// Увеличиваем capacity если нужно
	if index >= arr.capacity {
		newCapacity := arr.capacity
		for index >= newCapacity {
			newCapacity = newCapacity * 2
			if newCapacity > MAX_CAPACITY {
				newCapacity = MAX_CAPACITY
				break
			}
		}
		
		newData := make([]string, newCapacity)
		copy(newData, arr.data)
		arr.data = newData
		arr.capacity = newCapacity
	}
	
	if index > arr.size {
		// Заполняем промежуточные элементы пустыми строками
		for i := arr.size; i < index; i++ {
			if i < len(arr.data) {
				arr.data[i] = ""
			}
		}
		if index < len(arr.data) {
			arr.data[index] = key
		}
		arr.size = index + 1
	} else {
		// Сдвигаем элементы вправо и вставляем
		MResize(arr)
		if arr.size < len(arr.data) {
			copy(arr.data[index+1:], arr.data[index:arr.size])
		}
		arr.data[index] = key
		arr.size++
	}
}

// MReplace - заменяет элемент по индексу
func MReplace(arr *Array, index int, key string) {
	MInsert(arr, index, key)
}

// MPushBack - добавляет элемент в конец
func MPushBack(arr *Array, key string) {
	MResize(arr)
	if arr.size < len(arr.data) {
		arr.data[arr.size] = key
		arr.size++
	}
}

// MGetSize - возвращает размер массива
func MGetSize(arr *Array) int {
	return arr.size
}

// MGetValue - возвращает значение по индексу
func MGetValue(arr *Array, index int) string {
	if index < 0 || index >= arr.size {
		fmt.Println("Out of range")
		return ""
	}
	return arr.data[index]
}
