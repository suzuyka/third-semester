package main

import (
	"bufio"
	"encoding/binary"
	"fmt"
	"os"
	"strconv"
)

// ===================== Бинарная сериализация =====================

// Массив
func (a *Array) SerializeBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	binary.Write(file, binary.LittleEndian, int32(len(a.data)))
	for _, v := range a.data {
		binary.Write(file, binary.LittleEndian, int32(v))
	}
	return nil
}

func (a *Array) DeserializeBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var length int32
	binary.Read(file, binary.LittleEndian, &length)

	a.data = make([]int, length)
	for i := 0; i < int(length); i++ {
		var val int32
		binary.Read(file, binary.LittleEndian, &val)
		a.data[i] = int(val)
	}
	return nil
}

// Односвязный список
func (l *SinglyLinkedList) SerializeBinary(filename string) error {
	data := l.ToSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	binary.Write(file, binary.LittleEndian, int32(len(data)))
	for _, v := range data {
		binary.Write(file, binary.LittleEndian, int32(v))
	}
	return nil
}

func (l *SinglyLinkedList) DeserializeBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var length int32
	binary.Read(file, binary.LittleEndian, &length)

	l.head = nil
	for i := 0; i < int(length); i++ {
		var val int32
		binary.Read(file, binary.LittleEndian, &val)
		l.PushBack(int(val))
	}
	return nil
}

// Двусвязный список
func (l *DoublyLinkedList) SerializeBinary(filename string) error {
	data := l.ToSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	binary.Write(file, binary.LittleEndian, int32(len(data)))
	for _, v := range data {
		binary.Write(file, binary.LittleEndian, int32(v))
	}
	return nil
}

func (l *DoublyLinkedList) DeserializeBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var length int32
	binary.Read(file, binary.LittleEndian, &length)

	l.head = nil
	l.tail = nil
	for i := 0; i < int(length); i++ {
		var val int32
		binary.Read(file, binary.LittleEndian, &val)
		l.PushBack(int(val))
	}
	return nil
}

// Стек
func (s *Stack) SerializeBinary(filename string) error {
	data := s.toSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	binary.Write(file, binary.LittleEndian, int32(len(data)))
	for _, v := range data {
		binary.Write(file, binary.LittleEndian, int32(v))
	}
	return nil
}

func (s *Stack) DeserializeBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var length int32
	binary.Read(file, binary.LittleEndian, &length)

	s.top = nil
	for i := 0; i < int(length); i++ {
		var val int32
		binary.Read(file, binary.LittleEndian, &val)
		s.Push(int(val))
	}
	return nil
}

// Очередь
func (q *Queue) SerializeBinary(filename string) error {
	data := q.toSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	binary.Write(file, binary.LittleEndian, int32(len(data)))
	for _, v := range data {
		binary.Write(file, binary.LittleEndian, int32(v))
	}
	return nil
}

func (q *Queue) DeserializeBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var length int32
	binary.Read(file, binary.LittleEndian, &length)

	q.front = nil
	q.rear = nil
	for i := 0; i < int(length); i++ {
		var val int32
		binary.Read(file, binary.LittleEndian, &val)
		q.Push(int(val))
	}
	return nil
}

// ===================== Текстовая сериализация =====================

// Массив
func (a *Array) SerializeText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	for _, v := range a.data {
		fmt.Fprintln(file, v)
	}
	return nil
}

func (a *Array) DeserializeText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	a.data = []int{}

	for scanner.Scan() {
		val, err := strconv.Atoi(scanner.Text())
		if err == nil {
			a.data = append(a.data, val)
		}
	}
	return scanner.Err()
}

// Односвязный список
func (l *SinglyLinkedList) SerializeText(filename string) error {
	data := l.ToSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	for _, v := range data {
		fmt.Fprintln(file, v)
	}
	return nil
}

func (l *SinglyLinkedList) DeserializeText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	l.head = nil

	for scanner.Scan() {
		val, err := strconv.Atoi(scanner.Text())
		if err == nil {
			l.PushBack(val)
		}
	}
	return scanner.Err()
}

// Двусвязный список
func (l *DoublyLinkedList) SerializeText(filename string) error {
	data := l.ToSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	for _, v := range data {
		fmt.Fprintln(file, v)
	}
	return nil
}

func (l *DoublyLinkedList) DeserializeText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	l.head = nil
	l.tail = nil

	for scanner.Scan() {
		val, err := strconv.Atoi(scanner.Text())
		if err == nil {
			l.PushBack(val)
		}
	}
	return scanner.Err()
}

// Стек
func (s *Stack) SerializeText(filename string) error {
	data := s.toSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	for _, v := range data {
		fmt.Fprintln(file, v)
	}
	return nil
}

func (s *Stack) DeserializeText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	s.top = nil

	for scanner.Scan() {
		val, err := strconv.Atoi(scanner.Text())
		if err == nil {
			s.Push(val)
		}
	}
	return scanner.Err()
}

// Очередь
func (q *Queue) SerializeText(filename string) error {
	data := q.toSlice()
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	for _, v := range data {
		fmt.Fprintln(file, v)
	}
	return nil
}

func (q *Queue) DeserializeText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	q.front = nil
	q.rear = nil

	for scanner.Scan() {
		val, err := strconv.Atoi(scanner.Text())
		if err == nil {
			q.Push(val)
		}
	}
	return scanner.Err()
}
