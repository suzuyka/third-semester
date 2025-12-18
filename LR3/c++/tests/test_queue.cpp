#include <gtest/gtest.h>
#include "../include/Queue.h"

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        queue.push(1);
        queue.push(2);
        queue.push(3);
    }

    Queue queue;
};

TEST_F(QueueTest, PushAndFront) {
    EXPECT_EQ(queue.front(), 1);
    queue.push(4);
    // Front должен остаться тем же
    EXPECT_EQ(queue.front(), 1);
}

TEST_F(QueueTest, Pop) {
    queue.pop();
    EXPECT_EQ(queue.front(), 2);
}

TEST_F(QueueTest, Empty) {
    Queue emptyQueue;
    EXPECT_TRUE(emptyQueue.empty());
    EXPECT_FALSE(queue.empty());
}

TEST_F(QueueTest, PrintAndVector) {
    // Тестируем toVector
    auto vec = queue.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);

    // Тестируем print
    testing::internal::CaptureStdout();
    queue.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(QueueTest, Serialization) {
    // Тестируем сериализацию
    std::stringstream ss;
    queue.serializeBinary(ss);

    Queue queue2;
    queue2.deserializeBinary(ss);

    auto vec = queue2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(QueueTest, TextSerialization) {
    // Тестируем текстовую сериализацию
    std::stringstream ss;
    queue.serializeText(ss);

    Queue queue2;
    queue2.deserializeText(ss);

    auto vec = queue2.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(QueueTest, EdgeCases) {
    Queue emptyQueue;

    // Попытка pop из пустой очереди
    testing::internal::CaptureStderr();
    emptyQueue.pop();
    std::string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());

    // Попытка front из пустой очереди
    testing::internal::CaptureStderr();
    int value = emptyQueue.front();
    error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(value, -1);

    // toVector пустой очереди
    auto vec = emptyQueue.toVector();
    EXPECT_TRUE(vec.empty());
}
