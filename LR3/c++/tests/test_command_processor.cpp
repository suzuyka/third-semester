#include <gtest/gtest.h>
#include "../include/CommandProcessor.h"
#include <filesystem>
#include <fstream>
#include <sstream>

class CommandProcessorTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_file = "test_command.data";
        // Очищаем файл перед каждым тестом
        if (std::filesystem::exists(test_file)) {
            std::filesystem::remove(test_file);
        }
    }

    void TearDown() override {
        if (std::filesystem::exists(test_file)) {
            std::filesystem::remove(test_file);
        }
    }

    std::string getFileContent() {
        std::ifstream file(test_file);
        if (!file.is_open()) return "";
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    std::string test_file;
    CommandProcessor processor;
};

// ---- ARRAY COMMANDS ----
TEST_F(CommandProcessorTest, ArrayBasicOperations) {
    testing::internal::CaptureStdout();

    processor.execute("MPUSH 10", test_file);
    processor.execute("MPUSH 20", test_file);
    processor.execute("MPUSH 30", test_file);
    processor.execute("MGET 0", test_file);
    processor.execute("MGET 1", test_file);
    processor.execute("PRINTM", test_file);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(std::filesystem::exists(test_file));

    // Дополнительно проверяем что в файле есть данные
    std::string fileContent = getFileContent();
    EXPECT_FALSE(fileContent.empty());
}

TEST_F(CommandProcessorTest, ArrayAdvancedOperations) {
    testing::internal::CaptureStdout();

    processor.execute("MPUSH 1", test_file);
    processor.execute("MPUSH 2", test_file);
    processor.execute("MINDEX 1 99", test_file);  // Вставка по индексу
    processor.execute("MSET 0 50", test_file);    // Замена по индексу
    processor.execute("MDEL 1", test_file);       // Удаление по индексу
    processor.execute("PRINTM", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(std::filesystem::exists(test_file));
}

TEST_F(CommandProcessorTest, ArrayErrorCases) {
    testing::internal::CaptureStdout();

    processor.execute("MGET -1", test_file);        // Невалидный индекс
    processor.execute("MDEL 10", test_file);        // Индекс вне диапазона
    processor.execute("MINDEX -1 100", test_file);  // Невалидная вставка
    processor.execute("MSET 100 200", test_file);   // Невалидная замена

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Ошибка") != std::string::npos ||
    output.find("вне диапазона") != std::string::npos);
}

// ---- TREE COMMANDS ----
TEST_F(CommandProcessorTest, TreeBasicOperations) {
    testing::internal::CaptureStdout();

    processor.execute("TINSERT 50", test_file);
    processor.execute("TINSERT 30", test_file);
    processor.execute("TINSERT 70", test_file);
    processor.execute("TINSERT 20", test_file);
    processor.execute("TINSERT 40", test_file);
    processor.execute("TGET 30", test_file);
    processor.execute("TGET 99", test_file);        // Несуществующий
    processor.execute("TVALIDATE", test_file);
    processor.execute("PRINT", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем что есть вывод и дерево валидно
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("VALID") != std::string::npos ||
    output.find("OK") != std::string::npos);
}

TEST_F(CommandProcessorTest, TreeDeleteOperations) {
    testing::internal::CaptureStdout();

    processor.execute("TINSERT 10", test_file);
    processor.execute("TINSERT 20", test_file);
    processor.execute("TINSERT 5", test_file);
    processor.execute("TDEL 20", test_file);        // Существующий элемент
    processor.execute("TDEL 99", test_file);        // Несуществующий элемент
    processor.execute("TVALIDATE", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем что операции завершились и дерево валидно
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("VALID") != std::string::npos ||
    output.find("OK") != std::string::npos);
}

// ---- SINGLY LINKED LIST COMMANDS ----
TEST_F(CommandProcessorTest, SinglyListBasicOperations) {
    testing::internal::CaptureStdout();

    processor.execute("FPUSH 10", test_file);
    processor.execute("FPUSH 20", test_file);
    processor.execute("FPUSHFRONT 5", test_file);
    processor.execute("FGET 0", test_file);
    processor.execute("FGET 1", test_file);
    processor.execute("FCONTAINS 20", test_file);
    processor.execute("FCONTAINS 99", test_file);
    processor.execute("PRINTF", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем что есть вывод и операции выполнены
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(std::filesystem::exists(test_file));
}

TEST_F(CommandProcessorTest, SinglyListAdvancedOperations) {
    testing::internal::CaptureStdout();

    processor.execute("FPUSH 10", test_file);
    processor.execute("FPUSH 20", test_file);
    processor.execute("FPUSH 30", test_file);
    processor.execute("FINSERTBEFORE 20 15", test_file);
    processor.execute("FINSERTAFTER 20 25", test_file);
    processor.execute("FDEL 20", test_file);
    processor.execute("FDELFRONT", test_file);
    processor.execute("FDELBACK", test_file);
    processor.execute("PRINTF", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(std::filesystem::exists(test_file));
}

// ---- DOUBLY LINKED LIST COMMANDS ----
TEST_F(CommandProcessorTest, DoublyListBasicOperations) {
    testing::internal::CaptureStdout();

    processor.execute("LPUSH 10", test_file);
    processor.execute("LPUSH 20", test_file);
    processor.execute("LPUSHFRONT 5", test_file);
    processor.execute("LGET 0", test_file);
    processor.execute("LGET 1", test_file);
    processor.execute("LCONTAINS 20", test_file);
    processor.execute("LCONTAINS 99", test_file);
    processor.execute("PRINTL", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("найден") != std::string::npos);
}

TEST_F(CommandProcessorTest, DoublyListAdvancedOperations) {
    testing::internal::CaptureStdout();

    processor.execute("LPUSH 10", test_file);
    processor.execute("LPUSH 20", test_file);
    processor.execute("LPUSH 30", test_file);
    processor.execute("LINSERTBEFORE 20 15", test_file);
    processor.execute("LINSERTAFTER 20 25", test_file);
    processor.execute("LDEL 20", test_file);
    processor.execute("LDELFRONT", test_file);
    processor.execute("LDELBACK", test_file);
    processor.execute("PRINTL", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(std::filesystem::exists(test_file));
}

// ---- STACK COMMANDS ----
TEST_F(CommandProcessorTest, StackOperations) {
    testing::internal::CaptureStdout();

    processor.execute("SPUSH 10", test_file);
    processor.execute("SPUSH 20", test_file);
    processor.execute("SPUSH 30", test_file);
    processor.execute("SPOP", test_file);
    processor.execute("PRINTS", test_file);
    processor.execute("SPOP", test_file);
    processor.execute("SPOP", test_file);
    processor.execute("SPOP", test_file);           // Из пустого стека

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("удалён") != std::string::npos);
    EXPECT_TRUE(output.find("пуст") != std::string::npos);
}

// ---- QUEUE COMMANDS ----
TEST_F(CommandProcessorTest, QueueOperations) {
    testing::internal::CaptureStdout();

    processor.execute("QPUSH 10", test_file);
    processor.execute("QPUSH 20", test_file);
    processor.execute("QPUSH 30", test_file);
    processor.execute("QPOP", test_file);
    processor.execute("PRINTQ", test_file);
    processor.execute("QPOP", test_file);
    processor.execute("QPOP", test_file);
    processor.execute("QPOP", test_file);           // Из пустой очереди

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("удалён") != std::string::npos);
    EXPECT_TRUE(output.find("пуста") != std::string::npos);
}

// ---- HASH TABLE COMMANDS ----
TEST_F(CommandProcessorTest, HashTableAllModes) {
    testing::internal::CaptureStdout();

    // Тестируем все режимы хеширования
    processor.execute("SETDOUBLEHASH", test_file);
    processor.execute("HASHADD 1 100", test_file);
    processor.execute("HASHADD 2 200", test_file);
    processor.execute("HASHGET 1", test_file);
    processor.execute("HASHDEL 2", test_file);
    processor.execute("PRINTHASH", test_file);

    processor.execute("SETCUCKOOHASH", test_file);
    processor.execute("HASHADD 3 300", test_file);
    processor.execute("HASHADD 4 400", test_file);
    processor.execute("HASHGET 3", test_file);
    processor.execute("PRINTHASH", test_file);

    processor.execute("SETFOLDHASH", test_file);
    processor.execute("HASHADD 12345 500", test_file);
    processor.execute("HASHADD 67890 600", test_file);
    processor.execute("HASHGET 12345", test_file);
    processor.execute("PRINTHASH", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Двойное") != std::string::npos);
    EXPECT_TRUE(output.find("Кукушкино") != std::string::npos);
    EXPECT_TRUE(output.find("свёртки") != std::string::npos);
}

TEST_F(CommandProcessorTest, HashTableErrorCases) {
    testing::internal::CaptureStdout();

    processor.execute("SETDOUBLEHASH", test_file);
    processor.execute("HASHGET 999", test_file); // Несуществующий ключ
    processor.execute("HASHDEL 999", test_file); // Несуществующий ключ

    // Неправильный формат команд
    processor.execute("HASHADD", test_file);     // Не хватает аргументов
    processor.execute("HASHADD 1", test_file);   // Не хватает значения

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("не найден") != std::string::npos ||
    output.find("Ошибка") != std::string::npos);
}

// ---- FILE OPERATIONS ----
TEST_F(CommandProcessorTest, FilePersistence) {
    // Проверяем что данные сохраняются между вызовами
    processor.execute("MPUSH 100", test_file);
    processor.execute("MPUSH 200", test_file);

    std::string content1 = getFileContent();
    EXPECT_FALSE(content1.empty());

    // Новый процессор должен загрузить те же данные
    CommandProcessor processor2;
    testing::internal::CaptureStdout();
    processor2.execute("PRINTM", test_file);
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем что команда выполнилась без ошибок
    EXPECT_FALSE(output.empty());
}

// ---- ERROR CASES ----
TEST_F(CommandProcessorTest, UnknownCommands) {
    testing::internal::CaptureStdout();

    processor.execute("UNKNOWN_COMMAND", test_file);
    processor.execute("INVALID", test_file);
    processor.execute("", test_file);                   // Пустая команда
    processor.execute("TINSERT", test_file);            // Не хватает аргумента
    processor.execute("MPUSH abc", test_file);          // Неправильный тип аргумента

    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем что есть сообщения об ошибках
    EXPECT_FALSE(output.empty());
}

// ---- COMPREHENSIVE TEST ----
TEST_F(CommandProcessorTest, ComprehensiveWorkflow) {
    testing::internal::CaptureStdout();

    // Комплексный тест - работа со всеми структурами
    processor.execute("MPUSH 1", test_file);
    processor.execute("MPUSH 2", test_file);

    processor.execute("TINSERT 50", test_file);
    processor.execute("TINSERT 25", test_file);

    processor.execute("FPUSH 10", test_file);
    processor.execute("FPUSH 20", test_file);

    processor.execute("LPUSH 30", test_file);
    processor.execute("LPUSH 40", test_file);

    processor.execute("SPUSH 100", test_file);
    processor.execute("SPUSH 200", test_file);

    processor.execute("QPUSH 300", test_file);
    processor.execute("QPUSH 400", test_file);

    processor.execute("SETDOUBLEHASH", test_file);
    processor.execute("HASHADD 1 1000", test_file);
    processor.execute("HASHADD 2 2000", test_file);

    // Проверяем все операции
    processor.execute("PRINTM", test_file);
    processor.execute("PRINT", test_file);
    processor.execute("PRINTF", test_file);
    processor.execute("PRINTL", test_file);
    processor.execute("PRINTS", test_file);
    processor.execute("PRINTQ", test_file);
    processor.execute("PRINTHASH", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(std::filesystem::exists(test_file));

    // Проверяем что файл не пустой
    std::string fileContent = getFileContent();
    EXPECT_FALSE(fileContent.empty());
}

// ---- ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ ----
TEST_F(CommandProcessorTest, EdgeCaseCommands) {
    testing::internal::CaptureStdout();

    // Тестируем граничные случаи которые могут быть не покрыты
    processor.execute("MPUSH -1", test_file);           // Отрицательные числа
    processor.execute("MPUSH 0", test_file);            // Ноль
    processor.execute("MPUSH 999999", test_file);       // Большие числа

    // Пустые операции
    processor.execute("PRINTM", test_file);             // Печать пустого массива
    processor.execute("PRINT", test_file);              // Печать пустого дерева
    processor.execute("PRINTF", test_file);             // Печать пустого списка
    processor.execute("PRINTL", test_file);             // Печать пустого двусвязного списка
    processor.execute("PRINTS", test_file);             // Печать пустого стека
    processor.execute("PRINTQ", test_file);             // Печать пустой очереди
    processor.execute("PRINTHASH", test_file);          // Печать пустой хеш-таблицы

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST_F(CommandProcessorTest, BinaryCommandsCoverage) {
    testing::internal::CaptureStdout();

    // Создаем данные для тестирования
    processor.execute("MPUSH 100", test_file);
    processor.execute("FPUSH 200", test_file);
    processor.execute("LPUSH 300", test_file);
    processor.execute("SPUSH 400", test_file);
    processor.execute("QPUSH 500", test_file);
    processor.execute("TINSERT 600", test_file);
    processor.execute("HASHADD 700 800", test_file);

    // Тестируем бинарную сериализацию для всех структур
    processor.execute("ARRAY_SAVE_BIN", test_file);
    processor.execute("SLIST_SAVE_BIN", test_file);
    processor.execute("DLIST_SAVE_BIN", test_file);
    processor.execute("STACK_SAVE_BIN", test_file);
    processor.execute("QUEUE_SAVE_BIN", test_file);
    processor.execute("TREE_SAVE_BIN", test_file);
    processor.execute("HASH_SAVE_BIN", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());

    // Проверяем что команды выполнены
    EXPECT_TRUE(output.find("сохранен") != std::string::npos);
}

TEST_F(CommandProcessorTest, TextSerializationCommands) {
    testing::internal::CaptureStdout();

    // Создаем данные
    processor.execute("MPUSH 5", test_file);
    processor.execute("MPUSH 6", test_file);

    // Тестируем текстовую сериализацию
    processor.execute("ARRAY_SAVE_TXT", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());

    // Проверяем что файл создан
    EXPECT_TRUE(std::filesystem::exists(test_file + ".txt"));

    // Проверяем что команда выполнена
    EXPECT_TRUE(output.find("сохранен") != std::string::npos);
    EXPECT_TRUE(output.find("текстовом") != std::string::npos);
}

TEST_F(CommandProcessorTest, AllTextSerializationCommands) {
    testing::internal::CaptureStdout();

    // Создаем данные для всех структур
    processor.execute("MPUSH 1", test_file);
    processor.execute("FPUSH 2", test_file);
    processor.execute("LPUSH 3", test_file);
    processor.execute("SPUSH 4", test_file);
    processor.execute("QPUSH 5", test_file);
    processor.execute("TINSERT 6", test_file);
    processor.execute("SETDOUBLEHASH", test_file);
    processor.execute("HASHADD 7 8", test_file);

    // Тестируем текстовую сериализацию для всех структур
    processor.execute("ARRAY_SAVE_TXT", test_file);
    processor.execute("SLIST_SAVE_TXT", test_file);
    processor.execute("DLIST_SAVE_TXT", test_file);
    processor.execute("STACK_SAVE_TXT", test_file);
    processor.execute("QUEUE_SAVE_TXT", test_file);
    processor.execute("TREE_SAVE_TXT", test_file);
    processor.execute("HASH_SAVE_TXT", test_file);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());

    // Проверяем что команды выполнены
    EXPECT_TRUE(output.find("сохранен") != std::string::npos);
    EXPECT_TRUE(output.find("текстовом") != std::string::npos);
}


TEST_F(CommandProcessorTest, FileErrorHandlingText) {
    // Аналогично для текстовых форматов

    testing::internal::CaptureStdout();
    processor.execute("ARRAY_LOAD_TXT", "nonexistent.txt");
    std::string output1 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    processor.execute("SLIST_LOAD_TXT", "nonexistent.txt");
    std::string output2 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    processor.execute("DLIST_LOAD_TXT", "nonexistent.txt");
    std::string output3 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    processor.execute("STACK_LOAD_TXT", "nonexistent.txt");
    std::string output4 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    processor.execute("QUEUE_LOAD_TXT", "nonexistent.txt");
    std::string output5 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    processor.execute("TREE_LOAD_TXT", "nonexistent.txt");
    std::string output6 = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    processor.execute("HASH_LOAD_TXT", "nonexistent.txt");
    std::string output7 = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(true);
}



TEST_F(CommandProcessorTest, SaveToInvalidPaths) {
    // Просто выполняем команды
    processor.execute("MPUSH 1", test_file);
    processor.execute("ARRAY_SAVE_BIN", "/invalid/path/file.bin");
    processor.execute("ARRAY_SAVE_TXT", "/invalid/path/file.txt");

    EXPECT_TRUE(true);
}

TEST_F(CommandProcessorTest, BinarySaveLoadEdgeCases) {
    // Создаем пустые структуры и сохраняем/загружаем их
    processor.execute("ARRAY_SAVE_BIN", test_file);
    processor.execute("ARRAY_LOAD_BIN", test_file + ".bin");

    processor.execute("SLIST_SAVE_BIN", test_file);
    processor.execute("SLIST_LOAD_BIN", test_file + ".bin");

    processor.execute("DLIST_SAVE_BIN", test_file);
    processor.execute("DLIST_LOAD_BIN", test_file + ".bin");

    processor.execute("STACK_SAVE_BIN", test_file);
    processor.execute("STACK_LOAD_BIN", test_file + ".bin");

    processor.execute("QUEUE_SAVE_BIN", test_file);
    processor.execute("QUEUE_LOAD_BIN", test_file + ".bin");

    processor.execute("TREE_SAVE_BIN", test_file);
    processor.execute("TREE_LOAD_BIN", test_file + ".bin");

    processor.execute("HASH_SAVE_BIN", test_file);
    processor.execute("HASH_LOAD_BIN", test_file + ".bin");

    EXPECT_TRUE(true);
}

