package main

import (
    "fmt"
)

type Stack struct {
    data     []string
    size     int
    capacity int
}

func CreateS(st *Stack) {
    initCapacity := 10
    st.data = make([]string, initCapacity)
    st.size = 0
    st.capacity = initCapacity
}

func OutputS(st *Stack) {
    fmt.Printf("Stack[%d]: ", st.size)
    for i := 0; i < st.size; i++ {
        fmt.Printf("%s ", st.data[i])
    }
    fmt.Println()
}

func SResize(st *Stack) {
    if st.size >= st.capacity-1 {
        st.capacity *= 2
        newData := make([]string, st.capacity)
        copy(newData, st.data)
        st.data = newData
    }
}

func SPush(st *Stack, key string) {
    SResize(st)
    st.data[st.size] = key
    st.size++
}

func SPop(st *Stack) string {
    if st.size == 0 {
        fmt.Println("Error: Stack is empty")
        return ""
    }
    temp := st.data[st.size-1]
    st.size--
    return temp
}

func SDelAll(st *Stack) {
    if st != nil {
        st.data = nil
        st.size = 0
        st.capacity = 0
    }
}

func SPeek(st *Stack) string {
    if isEmptyStack(st) {
        fmt.Println("Stack is empty")
        return ""
    }
    return st.data[st.size-1]
}

func SGetSize(st *Stack) int {
    return st.size
}

func isEmptyStack(st *Stack) bool {
    return st.size == 0
}
