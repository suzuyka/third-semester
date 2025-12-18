#include <gtest/gtest.h>
#include "../include/SinglyLinkedList.h"

class SinglyLinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        list.pushBack(1);
        list.pushBack(2);
        list.pushBack(3);
    }

    SinglyLinkedList list;
};

TEST_F(SinglyLinkedListTest, InitialSize) {
    auto vec = list.toVector();
    EXPECT_EQ(vec.size(), 3);
}

TEST_F(SinglyLinkedListTest, PushFront) {
    list.pushFront(0);
    auto vec = list.toVector();
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(SinglyLinkedListTest, PushBack) {
    list.pushBack(4);
    auto vec = list.toVector();
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(SinglyLinkedListTest, Contains) {
    EXPECT_TRUE(list.contains(2));
    EXPECT_FALSE(list.contains(99));
}

TEST_F(SinglyLinkedListTest, DeleteByValue) {
    bool removed = list.delByValue(2);
    EXPECT_TRUE(removed);
    EXPECT_FALSE(list.contains(2));

    removed = list.delByValue(99);
    EXPECT_FALSE(removed);
}

TEST_F(SinglyLinkedListTest, InsertBefore) {
    list.insertBefore(2, 99);
    auto vec = list.toVector();
    EXPECT_EQ(vec[1], 99);
}

TEST_F(SinglyLinkedListTest, InsertAfter) {
    list.insertAfter(2, 99);
    auto vec = list.toVector();
    EXPECT_EQ(vec[2], 99);
}

TEST_F(SinglyLinkedListTest, GetByIndexValidAndInvalid) {
    // Валидные индексы
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);

    // Невалидный индекс
    testing::internal::CaptureStderr();
    int result = list.get(5);
    std::string errorOutput = testing::internal::GetCapturedStderr();
    EXPECT_EQ(result, -1);
    EXPECT_FALSE(errorOutput.empty()); // Проверяем что ошибка была выведена
}

TEST_F(SinglyLinkedListTest, GetByIndexEdgeCases) {
    // Пустой список
    SinglyLinkedList emptyList;
    testing::internal::CaptureStderr();
    EXPECT_EQ(emptyList.get(0), -1);
    std::string errorOutput = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(errorOutput.empty());

    // Отрицательный индекс
    testing::internal::CaptureStderr();
    EXPECT_EQ(list.get(-1), -1);
    errorOutput = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(errorOutput.empty());
}

TEST_F(SinglyLinkedListTest, InsertBeforeHeadCondition) {

    list.insertBefore(1, 99);

    auto vec = list.toVector();
    EXPECT_EQ(vec[0], 99);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(SinglyLinkedListTest, InsertBeforeNormalCase) {
    // Обычная вставка
    list.insertBefore(2, 99);

    auto vec = list.toVector();
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 99);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 3);
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(SinglyLinkedListTest, InsertBeforeLastElement) {
    // Вставка перед последним элементом
    list.insertBefore(3, 99);

    auto vec = list.toVector();
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 99);
    EXPECT_EQ(vec[3], 3);
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(SinglyLinkedListTest, DelBackMultipleScenarios) {
    // Удаление из списка с 3 элементами
    bool result = list.delBack();
    EXPECT_TRUE(result);

    auto vec = list.toVector();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);

    // Удаление из списка с 2 элементами
    result = list.delBack();
    EXPECT_TRUE(result);

    vec = list.toVector();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);

    // Удаление из списка с 1 элементом
    result = list.delBack();
    EXPECT_TRUE(result);

    vec = list.toVector();
    EXPECT_TRUE(vec.empty());

    // Удаление из пустого списка
    result = list.delBack();
    EXPECT_FALSE(result);
}

TEST_F(SinglyLinkedListTest, DelBackTwoElementsScenario) {

    SinglyLinkedList twoElementList;
    twoElementList.pushBack(1);
    twoElementList.pushBack(2);

    bool result = twoElementList.delBack();
    EXPECT_TRUE(result);

    auto vec = twoElementList.toVector();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST_F(SinglyLinkedListTest, DeserializeBinaryClearsList) {

    SinglyLinkedList listWithData;
    listWithData.pushBack(10);
    listWithData.pushBack(20);
    listWithData.pushBack(30);

    // Сериализуем тестовый список
    std::stringstream ss;
    list.serializeBinary(ss);

    // Десериализуем в список с данными - должен очиститься
    ss.seekg(0);
    listWithData.deserializeBinary(ss);

    // Проверяем что старые данные удалены, загружены новые
    auto vec = listWithData.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(SinglyLinkedListTest, DeserializeBinaryEmptyList) {
    // Десериализация в пустой список
    std::stringstream ss;
    list.serializeBinary(ss);

    SinglyLinkedList emptyList;
    ss.seekg(0);
    emptyList.deserializeBinary(ss);

    auto vec = emptyList.toVector();
    EXPECT_EQ(vec.size(), 3);
}

TEST_F(SinglyLinkedListTest, InsertBeforeEmptyList) {
    // Вставка в пустой список
    SinglyLinkedList emptyList;

    testing::internal::CaptureStderr();
    emptyList.insertBefore(1, 100);
    std::string output = testing::internal::GetCapturedStderr();

    // Список должен остаться пустым
    auto vec = emptyList.toVector();
    EXPECT_TRUE(vec.empty());
}

TEST_F(SinglyLinkedListTest, InsertBeforeNotFound) {
    // Вставка перед несуществующим элементом
    testing::internal::CaptureStderr();
    list.insertBefore(999, 100);

    // Список не должен измениться
    auto vec = list.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}
