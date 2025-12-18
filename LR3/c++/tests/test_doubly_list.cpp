#include <gtest/gtest.h>
#include "../include/DoublyLinkedList.h"

class DoublyLinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        list.pushBack(1);
        list.pushBack(2);
        list.pushBack(3);
    }

    DoublyLinkedList list;
};

// Базовые тесты
TEST_F(DoublyLinkedListTest, InitialSize) {
    auto vec = list.toVector();
    EXPECT_EQ(vec.size(), 3);
}

TEST_F(DoublyLinkedListTest, PushFront) {
    list.pushFront(0);
    auto vec = list.toVector();
    EXPECT_EQ(vec[0], 0);
}

TEST_F(DoublyLinkedListTest, PushBack) {
    list.pushBack(4);
    auto vec = list.toVector();
    EXPECT_EQ(vec[3], 4);
}

TEST_F(DoublyLinkedListTest, Contains) {
    EXPECT_TRUE(list.contains(2));
    EXPECT_FALSE(list.contains(99));
}

TEST_F(DoublyLinkedListTest, DeleteByValue) {
    bool removed = list.delByValue(2);
    EXPECT_TRUE(removed);
    EXPECT_FALSE(list.contains(2));

    removed = list.delByValue(99);
    EXPECT_FALSE(removed);
}

// Расширенные тесты
TEST_F(DoublyLinkedListTest, EdgeCases) {
    DoublyLinkedList emptyList;

    // Пустой список
    EXPECT_FALSE(emptyList.delFront());
    EXPECT_FALSE(emptyList.delBack());
    EXPECT_FALSE(emptyList.contains(1));
    EXPECT_EQ(emptyList.get(0), -1); // Ошибка индекса

    // Один элемент
    emptyList.pushFront(1);
    EXPECT_TRUE(emptyList.contains(1));
    EXPECT_TRUE(emptyList.delFront());

    // Вставка в пустой список
    emptyList.insertBefore(1, 2);
    emptyList.insertAfter(1, 2);
}

TEST_F(DoublyLinkedListTest, ComplexOperations) {
    // Сложные операции вставки
    list.insertBefore(2, 99);
    list.insertAfter(2, 88);

    auto vec = list.toVector();
    // Проверяем порядок
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 99);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 88);
    EXPECT_EQ(vec[4], 3);
}

TEST_F(DoublyLinkedListTest, DeleteOperations) {
    // Удаление первого элемента
    EXPECT_TRUE(list.delFront());
    auto vec = list.toVector();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 2);

    // Удаление последнего элемента
    EXPECT_TRUE(list.delBack());
    vec = list.toVector();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 2);
}

TEST_F(DoublyLinkedListTest, GetByIndex) {
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
    EXPECT_EQ(list.get(5), -1); // Невалидный индекс
}

TEST_F(DoublyLinkedListTest, MultipleOperations) {
    // Комбинация операций
    list.pushFront(0);
    list.pushBack(4);
    list.insertBefore(2, 99);
    list.insertAfter(2, 88);

    EXPECT_TRUE(list.delByValue(99));
    EXPECT_TRUE(list.delByValue(88));

    auto vec = list.toVector();
    EXPECT_EQ(vec.size(), 5);
}
