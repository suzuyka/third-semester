#include <gtest/gtest.h>
#include "../include/Array.h"

class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        arr.push(1);
        arr.push(2);
        arr.push(3);
    }

    Array arr;
};

TEST_F(ArrayTest, InitialSize) {
    EXPECT_EQ(arr.size(), 3);
}

TEST_F(ArrayTest, PushAndGet) {
    EXPECT_EQ(arr.get(0), 1);
    EXPECT_EQ(arr.get(1), 2);
    EXPECT_EQ(arr.get(2), 3);
}

TEST_F(ArrayTest, InsertAt) {
    arr.insertAt(1, 99);
    EXPECT_EQ(arr.get(1), 99);
    EXPECT_EQ(arr.get(2), 2);
    EXPECT_EQ(arr.size(), 4);
}

TEST_F(ArrayTest, DeleteAt) {
    arr.delAt(1);
    EXPECT_EQ(arr.get(1), 3);
    EXPECT_EQ(arr.size(), 2);
}

TEST_F(ArrayTest, SetElement) {
    arr.set(1, 50);
    EXPECT_EQ(arr.get(1), 50);
}

TEST_F(ArrayTest, BoundaryConditions) { // Проверка обработки невалидных индексов

    EXPECT_EQ(arr.get(-1), -1);
    EXPECT_EQ(arr.get(10), -1);

    arr.delAt(-1);
    arr.delAt(10);
    arr.insertAt(-1, 100);
    arr.insertAt(100, 200);
}

TEST_F(ArrayTest, PrintDoesNotCrash) {
    testing::internal::CaptureStdout();
    arr.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(ArrayTest, SerializationMethods) {
    
    // Тестируем текстовую сериализацию
    std::stringstream ss_text;
    arr.serializeText(ss_text);

    Array arr2;
    arr2.deserializeText(ss_text);

    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2.get(0), 1);
    EXPECT_EQ(arr2.get(1), 2);
    EXPECT_EQ(arr2.get(2), 3);

    // Тестируем бинарную сериализацию
    std::stringstream ss_bin;
    arr.serializeBinary(ss_bin);

    Array arr3;
    arr3.deserializeBinary(ss_bin);

    EXPECT_EQ(arr3.size(), 3);
    EXPECT_EQ(arr3.get(0), 1);
    EXPECT_EQ(arr3.get(1), 2);
    EXPECT_EQ(arr3.get(2), 3);
}
