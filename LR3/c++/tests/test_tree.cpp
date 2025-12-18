#include <gtest/gtest.h>
#include "../include/RedBlackTree.h"
#include <vector>
#include <algorithm>

class RedBlackTreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(1);
        tree.insert(9);
    }

    RedBlackTree tree;
};

// Базовые тесты
TEST_F(RedBlackTreeTest, InsertAndContains) {
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_FALSE(tree.contains(99));
}

TEST_F(RedBlackTreeTest, ValidateTree) {
    EXPECT_TRUE(tree.validate());
}

TEST_F(RedBlackTreeTest, ToVector) {
    auto vec = tree.toVector();
    // Должен быть отсортирован (in-order)
    for (size_t i = 1; i < vec.size(); i++) {
        EXPECT_LE(vec[i-1], vec[i]);
    }
}

TEST_F(RedBlackTreeTest, Remove) {
    tree.remove(3);
    EXPECT_FALSE(tree.contains(3));
    EXPECT_TRUE(tree.validate()); // Дерево должно оставаться валидным
}

// ---- РАСШИРЕННЫЕ ТЕСТЫ ----

TEST_F(RedBlackTreeTest, EmptyTree) {
    RedBlackTree emptyTree;
    EXPECT_FALSE(emptyTree.contains(1));
    EXPECT_TRUE(emptyTree.validate()); // Пустое дерево должно быть валидным

    auto vec = emptyTree.toVector();
    EXPECT_TRUE(vec.empty());
}

TEST_F(RedBlackTreeTest, SingleElement) {
    RedBlackTree singleTree;
    singleTree.insert(42);

    EXPECT_TRUE(singleTree.contains(42));
    EXPECT_FALSE(singleTree.contains(43));
    EXPECT_TRUE(singleTree.validate());

    auto vec = singleTree.toVector();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 42);
}

TEST_F(RedBlackTreeTest, DuplicateInsert) {
    // Вставка дубликатов
    tree.insert(5); // Дубликат
    tree.insert(3); // Дубликат

    EXPECT_TRUE(tree.validate());
    // Дерево должно остаться валидным после вставки дубликатов
}

TEST_F(RedBlackTreeTest, MultipleRemoves) {
    // Удаляем несколько элементов
    tree.remove(3);
    EXPECT_FALSE(tree.contains(3));
    EXPECT_TRUE(tree.validate());

    tree.remove(7);
    EXPECT_FALSE(tree.contains(7));
    EXPECT_TRUE(tree.validate());

    tree.remove(5); // Удаляем корень
    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.validate());

    // Проверяем оставшиеся элементы
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(9));
}

TEST_F(RedBlackTreeTest, RemoveNonExistent) {
    testing::internal::CaptureStdout();
    tree.remove(999); // Несуществующий элемент
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("не найден") != std::string::npos);
    EXPECT_TRUE(tree.validate()); // Дерево должно остаться валидным
}

TEST_F(RedBlackTreeTest, ComplexInsertSequence) {
    RedBlackTree complexTree;

    // Вставляем в разном порядке для тестирования балансировки
    std::vector<int> values = {10, 5, 15, 3, 7, 12, 17, 1, 4, 6, 8, 11, 13, 16, 18};

    for (int val : values) {
        complexTree.insert(val);
        EXPECT_TRUE(complexTree.contains(val));
    }

    EXPECT_TRUE(complexTree.validate());

    auto vec = complexTree.toVector();
    EXPECT_EQ(vec.size(), values.size());

    // Проверяем что вектор отсортирован
    for (size_t i = 1; i < vec.size(); i++) {
        EXPECT_LE(vec[i-1], vec[i]);
    }
}

TEST_F(RedBlackTreeTest, RemoveAllElements) {
    // Удаляем все элементы по одному
    std::vector<int> elements = {1, 3, 5, 7, 9};

    for (int elem : elements) {
        EXPECT_TRUE(tree.contains(elem));
        tree.remove(elem);
        EXPECT_FALSE(tree.contains(elem));
        EXPECT_TRUE(tree.validate());
    }

    // Дерево должно быть пустым, но валидным
    auto vec = tree.toVector();
    EXPECT_TRUE(vec.empty());
}

TEST_F(RedBlackTreeTest, PrintDoesNotCrash) {
    testing::internal::CaptureStdout();
    tree.print();
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем что вывод не пустой и содержит числа
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("5") != std::string::npos ||
    output.find("3") != std::string::npos ||
    output.find("7") != std::string::npos);
}

TEST_F(RedBlackTreeTest, LargeTree) {
    RedBlackTree largeTree;

    // Вставляем много элементов
    for (int i = 1; i <= 50; i++) {
        largeTree.insert(i);
    }

    EXPECT_TRUE(largeTree.validate());

    // Проверяем несколько случайных элементов
    EXPECT_TRUE(largeTree.contains(1));
    EXPECT_TRUE(largeTree.contains(25));
    EXPECT_TRUE(largeTree.contains(50));
    EXPECT_FALSE(largeTree.contains(51));

    auto vec = largeTree.toVector();
    EXPECT_EQ(vec.size(), 50);

    // Проверяем сортировку
    for (size_t i = 1; i < vec.size(); i++) {
        EXPECT_LE(vec[i-1], vec[i]);
    }

    // Удаляем некоторые элементы
    largeTree.remove(25);
    largeTree.remove(50);
    largeTree.remove(1);

    EXPECT_FALSE(largeTree.contains(25));
    EXPECT_FALSE(largeTree.contains(50));
    EXPECT_FALSE(largeTree.contains(1));
    EXPECT_TRUE(largeTree.validate());
}

TEST_F(RedBlackTreeTest, ReverseOrderInsert) {
    RedBlackTree reverseTree;

    // Вставляем в обратном порядке
    for (int i = 10; i >= 1; i--) {
        reverseTree.insert(i);
    }

    EXPECT_TRUE(reverseTree.validate());

    auto vec = reverseTree.toVector();
    EXPECT_EQ(vec.size(), 10);

    // Проверяем сортировку
    for (size_t i = 1; i < vec.size(); i++) {
        EXPECT_LE(vec[i-1], vec[i]);
    }

    // Проверяем все элементы
    for (int i = 1; i <= 10; i++) {
        EXPECT_TRUE(reverseTree.contains(i));
    }
}

TEST_F(RedBlackTreeTest, MixedOperations) {
    RedBlackTree mixedTree;

    // Смешанные операции вставки и удаления
    mixedTree.insert(10);
    mixedTree.insert(5);
    mixedTree.insert(15);
    EXPECT_TRUE(mixedTree.validate());

    mixedTree.remove(5);
    EXPECT_FALSE(mixedTree.contains(5));
    EXPECT_TRUE(mixedTree.validate());

    mixedTree.insert(3);
    mixedTree.insert(7);
    mixedTree.insert(12);
    mixedTree.insert(17);
    EXPECT_TRUE(mixedTree.validate());

    mixedTree.remove(10); // Удаляем корень
    EXPECT_FALSE(mixedTree.contains(10));
    EXPECT_TRUE(mixedTree.validate());

    // Проверяем оставшиеся элементы
    EXPECT_TRUE(mixedTree.contains(3));
    EXPECT_TRUE(mixedTree.contains(7));
    EXPECT_TRUE(mixedTree.contains(12));
    EXPECT_TRUE(mixedTree.contains(15));
    EXPECT_TRUE(mixedTree.contains(17));
}

TEST_F(RedBlackTreeTest, EdgeCaseRemovals) {
    RedBlackTree edgeTree;

    // Создаем специфические случаи для удаления
    edgeTree.insert(10);
    edgeTree.insert(5);
    edgeTree.insert(15);
    edgeTree.insert(3);
    edgeTree.insert(7);
    edgeTree.insert(12);
    edgeTree.insert(17);

    EXPECT_TRUE(edgeTree.validate());

    // Удаляем лист
    edgeTree.remove(3);
    EXPECT_FALSE(edgeTree.contains(3));
    EXPECT_TRUE(edgeTree.validate());

    // Удаляем узел с одним потомком
    edgeTree.remove(7);
    EXPECT_FALSE(edgeTree.contains(7));
    EXPECT_TRUE(edgeTree.validate());

    // Удаляем узел с двумя потомками
    edgeTree.remove(15);
    EXPECT_FALSE(edgeTree.contains(15));
    EXPECT_TRUE(edgeTree.validate());

    // Удаляем корень
    edgeTree.remove(10);
    EXPECT_FALSE(edgeTree.contains(10));
    EXPECT_TRUE(edgeTree.validate());
}

TEST_F(RedBlackTreeTest, ValidateEmptyTree) {
    RedBlackTree emptyTree;
    testing::internal::CaptureStdout();
    bool isValid = emptyTree.validate();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(isValid);
    EXPECT_TRUE(output.find("пустое дерево") != std::string::npos);
}

TEST_F(RedBlackTreeTest, ValidateInvalidTree) {
    EXPECT_TRUE(tree.validate());

    // Проверим что после множества операций дерево остается валидным
    for (int i = 10; i < 20; i++) {
        tree.insert(i);
        EXPECT_TRUE(tree.validate());
    }

    for (int i = 5; i < 15; i++) {
        tree.remove(i);
        EXPECT_TRUE(tree.validate());
    }
}

TEST_F(RedBlackTreeTest, GetNodeInfo) {
    testing::internal::CaptureStdout();
    tree.print();
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем что вывод содержит информацию о цветах
    EXPECT_TRUE(output.find("RED") != std::string::npos ||
    output.find("BLACK") != std::string::npos);
}
