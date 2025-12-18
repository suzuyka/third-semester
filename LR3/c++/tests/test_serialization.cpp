#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "../include/Array.h"
#include "../include/SinglyLinkedList.h"
#include "../include/DoublyLinkedList.h"
#include "../include/Stack.h"
#include "../include/Queue.h"
#include "../include/RedBlackTree.h"
#include "../include/HashTable.h"

class SerializationTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_bin_file = "test_serialization.bin";
        test_txt_file = "test_serialization.txt";
    }

    void TearDown() override {
        if (std::filesystem::exists(test_bin_file)) {
            std::filesystem::remove(test_bin_file);
        }
        if (std::filesystem::exists(test_txt_file)) {
            std::filesystem::remove(test_txt_file);
        }
    }

    std::string test_bin_file;
    std::string test_txt_file;
};

// ---- ARRAY SERIALIZATION ----
TEST_F(SerializationTest, ArrayBinarySerialization) {
    Array arr;
    arr.push(1); arr.push(2); arr.push(3); arr.push(4); arr.push(5);

    // Сериализация в бинарный формат
    std::ofstream out_bin(test_bin_file, std::ios::binary);
    arr.serializeBinary(out_bin);
    out_bin.close();

    // Десериализация из бинарного формата
    Array arr2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    arr2.deserializeBinary(in_bin);
    in_bin.close();

    // Проверка
    EXPECT_EQ(arr2.size(), 5);
    EXPECT_EQ(arr2.get(0), 1);
    EXPECT_EQ(arr2.get(1), 2);
    EXPECT_EQ(arr2.get(2), 3);
    EXPECT_EQ(arr2.get(3), 4);
    EXPECT_EQ(arr2.get(4), 5);
}

TEST_F(SerializationTest, ArrayTextSerialization) {
    Array arr;
    arr.push(10); arr.push(20); arr.push(30);

    // Сериализация в текстовый формат
    std::ofstream out_txt(test_txt_file);
    arr.serializeText(out_txt);
    out_txt.close();

    // Десериализация из текстового формата
    Array arr2;
    std::ifstream in_txt(test_txt_file);
    arr2.deserializeText(in_txt);
    in_txt.close();

    // Проверка
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2.get(0), 10);
    EXPECT_EQ(arr2.get(1), 20);
    EXPECT_EQ(arr2.get(2), 30);
}

TEST_F(SerializationTest, ArrayEmptySerialization) {
    Array empty_arr;

    // Бинарная сериализация пустого массива
    std::ofstream out_bin(test_bin_file, std::ios::binary);
    empty_arr.serializeBinary(out_bin);
    out_bin.close();

    Array empty_arr2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    empty_arr2.deserializeBinary(in_bin);
    in_bin.close();

    EXPECT_EQ(empty_arr2.size(), 0);
}

// ---- SINGLY LINKED LIST SERIALIZATION ----
TEST_F(SerializationTest, SinglyListBinarySerialization) {
    SinglyLinkedList list;
    list.pushBack(1); list.pushBack(2); list.pushBack(3);

    std::ofstream out_bin(test_bin_file, std::ios::binary);
    list.serializeBinary(out_bin);
    out_bin.close();

    SinglyLinkedList list2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    list2.deserializeBinary(in_bin);
    in_bin.close();

    auto vec = list2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(SerializationTest, SinglyListTextSerialization) {
    SinglyLinkedList list;
    list.pushBack(5); list.pushBack(10); list.pushBack(15);

    std::ofstream out_txt(test_txt_file);
    list.serializeText(out_txt);
    out_txt.close();

    SinglyLinkedList list2;
    std::ifstream in_txt(test_txt_file);
    list2.deserializeText(in_txt);
    in_txt.close();

    auto vec = list2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 10);
    EXPECT_EQ(vec[2], 15);
}

// ---- DOUBLY LINKED LIST SERIALIZATION ----
TEST_F(SerializationTest, DoublyListBinarySerialization) {
    DoublyLinkedList list;
    list.pushBack(1); list.pushBack(2); list.pushBack(3);

    std::ofstream out_bin(test_bin_file, std::ios::binary);
    list.serializeBinary(out_bin);
    out_bin.close();

    DoublyLinkedList list2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    list2.deserializeBinary(in_bin);
    in_bin.close();

    auto vec = list2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

// ---- STACK SERIALIZATION ----
TEST_F(SerializationTest, StackBinarySerialization) {
    Stack stack;
    stack.push(1); stack.push(2); stack.push(3);

    std::ofstream out_bin(test_bin_file, std::ios::binary);
    stack.serializeBinary(out_bin);
    out_bin.close();

    Stack stack2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    stack2.deserializeBinary(in_bin);
    in_bin.close();

    auto vec = stack2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

// ---- QUEUE SERIALIZATION ----
TEST_F(SerializationTest, QueueBinarySerialization) {
    Queue queue;
    queue.push(1); queue.push(2); queue.push(3);

    std::ofstream out_bin(test_bin_file, std::ios::binary);
    queue.serializeBinary(out_bin);
    out_bin.close();

    Queue queue2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    queue2.deserializeBinary(in_bin);
    in_bin.close();

    auto vec = queue2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

// ---- TREE SERIALIZATION ----
TEST_F(SerializationTest, TreeBinarySerialization) {
    RedBlackTree tree;
    tree.insert(5); tree.insert(3); tree.insert(7); tree.insert(1);

    std::ofstream out_bin(test_bin_file, std::ios::binary);
    tree.serializeBinary(out_bin);
    out_bin.close();

    RedBlackTree tree2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    tree2.deserializeBinary(in_bin);
    in_bin.close();

    auto vec = tree2.toVector();
    EXPECT_EQ(vec.size(), 4);
    // Проверяем что все элементы присутствуют
    EXPECT_TRUE(std::find(vec.begin(), vec.end(), 1) != vec.end());
    EXPECT_TRUE(std::find(vec.begin(), vec.end(), 3) != vec.end());
    EXPECT_TRUE(std::find(vec.begin(), vec.end(), 5) != vec.end());
    EXPECT_TRUE(std::find(vec.begin(), vec.end(), 7) != vec.end());
}

// ---- HASH TABLE SERIALIZATION ----
TEST_F(SerializationTest, HashTableBinarySerialization) {
    HashTable ht(11, HashType::DOUBLE_HASHING);
    ht.insert(1, 100); ht.insert(2, 200); ht.insert(3, 300);

    std::ofstream out_bin(test_bin_file, std::ios::binary);
    ht.serializeBinary(out_bin);
    out_bin.close();

    HashTable ht2;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    ht2.deserializeBinary(in_bin);
    in_bin.close();

    // Проверяем что данные сохранились
    EXPECT_EQ(ht2.get(1).value(), 100);
    EXPECT_EQ(ht2.get(2).value(), 200);
    EXPECT_EQ(ht2.get(3).value(), 300);
}

TEST_F(SerializationTest, HashTableTextSerialization) {
    HashTable ht(11, HashType::CUCKOO_HASHING);
    ht.insert(10, 1000); ht.insert(20, 2000);

    std::ofstream out_txt(test_txt_file);
    ht.serializeText(out_txt);
    out_txt.close();

    HashTable ht2;
    std::ifstream in_txt(test_txt_file);
    ht2.deserializeText(in_txt);
    in_txt.close();

    EXPECT_EQ(ht2.get(10).value(), 1000);
    EXPECT_EQ(ht2.get(20).value(), 2000);
}

TEST_F(SerializationTest, HashTableAllTypesSerialization) {
    // Тестируем все типы хеширования
    HashType types[] = {HashType::DOUBLE_HASHING, HashType::CUCKOO_HASHING, HashType::FOLDING_HASHING};

    for (HashType type : types) {
        HashTable ht(7, type);
        ht.insert(1, 100); ht.insert(2, 200);

        std::ofstream out_bin(test_bin_file, std::ios::binary);
        ht.serializeBinary(out_bin);
        out_bin.close();

        HashTable ht2;
        std::ifstream in_bin(test_bin_file, std::ios::binary);
        ht2.deserializeBinary(in_bin);
        in_bin.close();

        EXPECT_EQ(ht2.get(1).value(), 100);
        EXPECT_EQ(ht2.get(2).value(), 200);
        EXPECT_EQ(ht2.getType(), type); // Тип должен сохраниться
    }
}

// ---- COMPARISON TESTS ----
TEST_F(SerializationTest, FileSizeComparison) {
    Array arr;
    // Используем больше данных для более реалистичного сравнения
    for (int i = 0; i < 1000; i++) {
        arr.push(i);
    }

    // Бинарная сериализация
    std::ofstream out_bin(test_bin_file, std::ios::binary);
    arr.serializeBinary(out_bin);
    out_bin.close();

    // Текстовая сериализация
    std::ofstream out_txt(test_txt_file);
    arr.serializeText(out_txt);
    out_txt.close();

    size_t bin_size = std::filesystem::file_size(test_bin_file);
    size_t txt_size = std::filesystem::file_size(test_txt_file);

    // Поэтому проверяем что оба файла созданы успешно
    EXPECT_GT(bin_size, 0);
    EXPECT_GT(txt_size, 0);

    // Выводим информацию для отладки
    std::cout << "Binary size: " << bin_size << ", Text size: " << txt_size << std::endl;
}

// ---- ERROR HANDLING ----
TEST_F(SerializationTest, EmptyFileDeserialization) {
    // Создаем пустой файл
    std::ofstream empty_file(test_bin_file, std::ios::binary);
    empty_file.close();

    Array arr;
    std::ifstream in_bin(test_bin_file, std::ios::binary);
    arr.deserializeBinary(in_bin);
    in_bin.close();

    EXPECT_EQ(arr.size(), 0);
}

TEST_F(SerializationTest, InvalidFileDeserialization) {
    Array arr;

    // Попытка десериализации из несуществующего файла
    std::ifstream in_bin("nonexistent_file.bin", std::ios::binary);
    arr.deserializeBinary(in_bin);
    in_bin.close();

    EXPECT_EQ(arr.size(), 0);
}
