#include <benchmark/benchmark.h>
#include "../include/Array.h"
#include "../include/Stack.h"
#include "../include/Queue.h"
#include "../include/RedBlackTree.h"
#include "../include/HashTable.h"
#include "../include/SinglyLinkedList.h"
#include "../include/DoublyLinkedList.h"

#include <sstream>

// === BENCHMARK ДЛЯ ARRAY ===
static void BM_ArrayPush(benchmark::State& state) {
    for (auto _ : state) {
        Array arr;
        for (int i = 0; i < state.range(0); i++) {
            arr.push(i);
        }
    }
}
BENCHMARK(BM_ArrayPush)->Range(8, 8<<10); // от 8 до 8192 элементов

static void BM_ArrayInsertAt(benchmark::State& state) {
    Array arr;
    for (int i = 0; i < 1000; i++) {
        arr.push(i);
    }

    for (auto _ : state) {
        arr.insertAt(500, 999);
        state.PauseTiming();
        arr.delAt(500);
        state.ResumeTiming();
    }
}
BENCHMARK(BM_ArrayInsertAt);

// === BENCHMARK ДЛЯ STACK ===
static void BM_StackPushPop(benchmark::State& state) {
    Stack stack;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); i++) {
            stack.push(i);
        }
        for (int i = 0; i < state.range(0); i++) {
            stack.pop();
        }
    }
}
BENCHMARK(BM_StackPushPop)->Range(8, 8<<10);

// === BENCHMARK ДЛЯ QUEUE ===
static void BM_QueuePushPop(benchmark::State& state) {
    Queue queue;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); i++) {
            queue.push(i);
        }
        for (int i = 0; i < state.range(0); i++) {
            queue.pop();
        }
    }
}
BENCHMARK(BM_QueuePushPop)->Range(8, 8<<10);

// === BENCHMARK ДЛЯ SINGLY LINKED LIST ===
static void BM_SinglyListPushBack(benchmark::State& state) {
    SinglyLinkedList list;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); i++) {
            list.pushBack(i);
        }
        state.PauseTiming();
        list = SinglyLinkedList(); // очистка
        state.ResumeTiming();
    }
}
BENCHMARK(BM_SinglyListPushBack)->Range(8, 8<<10);

static void BM_SinglyListFind(benchmark::State& state) {
    SinglyLinkedList list;
    for (int i = 0; i < 1000; i++) {
        list.pushBack(i);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(list.contains(500));
    }
}
BENCHMARK(BM_SinglyListFind);

// === BENCHMARK ДЛЯ DOUBLY LINKED LIST ===
static void BM_DoublyListPushBack(benchmark::State& state) {
    DoublyLinkedList list;
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); i++) {
            list.pushBack(i);
        }
        state.PauseTiming();
        list = DoublyLinkedList(); // очистка
        state.ResumeTiming();
    }
}
BENCHMARK(BM_DoublyListPushBack)->Range(8, 8<<10);

// === BENCHMARK ДЛЯ RED-BLACK TREE ===
static void BM_TreeInsert(benchmark::State& state) {
    for (auto _ : state) {
        RedBlackTree tree;
        for (int i = 0; i < state.range(0); i++) {
            tree.insert(i);
        }
    }
}
BENCHMARK(BM_TreeInsert)->Range(8, 8<<10);

static void BM_TreeFind(benchmark::State& state) {
    RedBlackTree tree;
    for (int i = 0; i < 1000; i++) {
        tree.insert(i);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(tree.contains(500));
    }
}
BENCHMARK(BM_TreeFind);

// === BENCHMARK ДЛЯ HASH TABLE ===
static void BM_HashTableInsert(benchmark::State& state) {
    for (auto _ : state) {
        HashTable ht(101, HashType::DOUBLE_HASHING);
        for (int i = 0; i < state.range(0); i++) {
            ht.insert(i, i * 10);
        }
    }
}
BENCHMARK(BM_HashTableInsert)->Range(8, 8<<10);

static void BM_HashTableFind(benchmark::State& state) {
    HashTable ht(101, HashType::DOUBLE_HASHING);
    for (int i = 0; i < 1000; i++) {
        ht.insert(i, i * 10);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(ht.get(500));
    }
}
BENCHMARK(BM_HashTableFind);

// === СРАВНЕНИЕ РАЗНЫХ ТИПОВ ХЕШИРОВАНИЯ ===
static void BM_HashTableDoubleHashing(benchmark::State& state) {
    for (auto _ : state) {
        HashTable ht(101, HashType::DOUBLE_HASHING);
        for (int i = 0; i < state.range(0); i++) {
            ht.insert(i, i * 10);
        }
    }
}
BENCHMARK(BM_HashTableDoubleHashing)->Range(8, 8<<10);

static void BM_HashTableCuckooHashing(benchmark::State& state) {
    for (auto _ : state) {
        HashTable ht(101, HashType::CUCKOO_HASHING);
        for (int i = 0; i < state.range(0); i++) {
            ht.insert(i, i * 10);
        }
    }
}
BENCHMARK(BM_HashTableCuckooHashing)->Range(8, 8<<10);

static void BM_HashTableFoldingHashing(benchmark::State& state) {
    for (auto _ : state) {
        HashTable ht(101, HashType::FOLDING_HASHING);
        for (int i = 0; i < state.range(0); i++) {
            ht.insert(i, i * 10);
        }
    }
}
BENCHMARK(BM_HashTableFoldingHashing)->Range(8, 8<<10);

// === BENCHMARK СЕРИАЛИЗАЦИИ ===
static void BM_ArraySerialization(benchmark::State& state) {
    Array arr;
    for (int i = 0; i < 1000; i++) {
        arr.push(i);
    }

    for (auto _ : state) {
        std::stringstream ss;
        arr.serializeBinary(ss);
    }
}
BENCHMARK(BM_ArraySerialization);

static void BM_StackSerialization(benchmark::State& state) {
    Stack stack;
    for (int i = 0; i < 1000; i++) {
        stack.push(i);
    }

    for (auto _ : state) {
        std::stringstream ss;
        stack.serializeBinary(ss);
    }
}
BENCHMARK(BM_StackSerialization);

BENCHMARK_MAIN();
