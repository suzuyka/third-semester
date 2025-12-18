#include <gtest/gtest.h>
#include "../include/Stack.h"

class StackTest : public ::testing::Test {
protected:
    void SetUp() override {
        stack.push(1);
        stack.push(2);
        stack.push(3);
    }

    Stack stack;
};

TEST_F(StackTest, PushAndTop) {
    EXPECT_EQ(stack.top(), 3);
    stack.push(4);
    EXPECT_EQ(stack.top(), 4);
}

TEST_F(StackTest, Pop) {
    stack.pop();
    EXPECT_EQ(stack.top(), 2);
}

TEST_F(StackTest, Empty) {
    Stack emptyStack;
    EXPECT_TRUE(emptyStack.empty());
    EXPECT_FALSE(stack.empty());
}

TEST_F(StackTest, PopEmptyStack) {
    Stack emptyStack;
    testing::internal::CaptureStderr();
    emptyStack.pop();
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(output.empty());
}

TEST_F(StackTest, PrintAndVector) {
    // Тестируем toVector
    auto vec = stack.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);

    // Тестируем print
    testing::internal::CaptureStdout();
    stack.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(StackTest, Serialization) {
    // Тестируем сериализацию
    std::stringstream ss;
    stack.serializeBinary(ss);

    Stack stack2;
    stack2.deserializeBinary(ss);

    auto vec = stack2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(StackTest, TextSerialization) {
    // Тестируем текстовую сериализацию
    std::stringstream ss;
    stack.serializeText(ss);

    Stack stack2;
    stack2.deserializeText(ss);

    auto vec = stack2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(StackTest, EdgeCases) {
    Stack emptyStack;

    // Попытка pop из пустого стека
    testing::internal::CaptureStderr();
    emptyStack.pop();
    std::string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());

    // Попытка top из пустого стека
    testing::internal::CaptureStderr();
    int value = emptyStack.top();
    error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(value, -1);

    // toVector пустого стека
    auto vec = emptyStack.toVector();
    EXPECT_TRUE(vec.empty());
}
