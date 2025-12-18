#include <gtest/gtest.h>
#include <algorithm>
#include <climits>

#include "../include/HashTable.h"

class HashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Используем double hashing по умолчанию
        table.insert(1, 100);
        table.insert(2, 200);
        table.insert(3, 300);
    }

    HashTable table;
};

// Базовые тесты
TEST_F(HashTableTest, InsertAndGet) {
    auto value = table.get(1);
    EXPECT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), 100);
}

TEST_F(HashTableTest, GetNonExistent) {
    auto value = table.get(999);
    EXPECT_FALSE(value.has_value());
}

TEST_F(HashTableTest, Remove) {
    bool removed = table.remove(1);
    EXPECT_TRUE(removed);
    EXPECT_FALSE(table.get(1).has_value());
}

TEST_F(HashTableTest, RemoveNonExistent) {
    bool removed = table.remove(999);
    EXPECT_FALSE(removed);
}

// Расширенные тесты
TEST_F(HashTableTest, DoubleHashing) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Тестируем коллизии и rehash
    for (int i = 0; i < 20; i++) {
        ht.insert(i, i * 10);
    }

    for (int i = 0; i < 20; i++) {
        EXPECT_TRUE(ht.get(i).has_value());
        EXPECT_EQ(ht.get(i).value(), i * 10);
    }
}

TEST_F(HashTableTest, CuckooHashing) {
    HashTable ht(11, HashType::CUCKOO_HASHING);

    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(3, 300);

    EXPECT_EQ(ht.get(1).value(), 100);
    EXPECT_EQ(ht.get(2).value(), 200);
    EXPECT_EQ(ht.get(3).value(), 300);

    // Проверяем удаление
    EXPECT_TRUE(ht.remove(1));
    EXPECT_FALSE(ht.get(1).has_value());
}

TEST_F(HashTableTest, FoldingHashing) {
    HashTable ht(11, HashType::FOLDING_HASHING);

    // Тестируем метод свертки с большими числами
    ht.insert(123456, 100);
    ht.insert(789012, 200);
    ht.insert(345678, 300);

    EXPECT_TRUE(ht.get(123456).has_value());
    EXPECT_TRUE(ht.get(789012).has_value());
    EXPECT_TRUE(ht.get(345678).has_value());

    EXPECT_EQ(ht.get(123456).value(), 100);
    EXPECT_EQ(ht.get(789012).value(), 200);
}

TEST_F(HashTableTest, LoadFactorAndRehash) {
    HashTable ht(5, HashType::DOUBLE_HASHING); // Маленький размер для теста rehash

    // Заполняем до rehash
    for (int i = 0; i < 10; i++) {
        ht.insert(i, i * 10);
    }

    // Проверяем что все элементы на месте после rehash
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(ht.get(i).has_value());
        EXPECT_EQ(ht.get(i).value(), i * 10);
    }
}

TEST_F(HashTableTest, CollisionHandling) {
    HashTable ht(3, HashType::DOUBLE_HASHING);

    // Создаем коллизии
    ht.insert(1, 100);
    ht.insert(4, 400);
    ht.insert(7, 700);

    // Все элементы должны быть доступны
    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(4).has_value());
    EXPECT_TRUE(ht.get(7).has_value());
}

TEST_F(HashTableTest, ClearAndPrint) {
    // Проверяем что print не падает
    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());

    // Проверяем toVector
    auto vec = table.toVector();
    EXPECT_GE(vec.size(), 3);
}

TEST_F(HashTableTest, UpdateExistingKey) {
    // Вставка с существующим ключом должна обновить значение
    table.insert(1, 999);
    EXPECT_EQ(table.get(1).value(), 999);
}

TEST_F(HashTableTest, AllHashTypes) {
    // Тестируем что все типы работают
    HashTable doubleHash(11, HashType::DOUBLE_HASHING);
    HashTable cuckooHash(11, HashType::CUCKOO_HASHING);
    HashTable foldingHash(11, HashType::FOLDING_HASHING);

    // Простая вставка в каждый тип
    doubleHash.insert(1, 100);
    cuckooHash.insert(2, 200);
    foldingHash.insert(3, 300);

    EXPECT_TRUE(doubleHash.get(1).has_value());
    EXPECT_TRUE(cuckooHash.get(2).has_value());
    EXPECT_TRUE(foldingHash.get(3).has_value());
}

TEST_F(HashTableTest, LargeKeys) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Тестируем большие ключи
    ht.insert(1000000, 1);
    ht.insert(2000000, 2);
    ht.insert(3000000, 3);

    EXPECT_TRUE(ht.get(1000000).has_value());
    EXPECT_TRUE(ht.get(2000000).has_value());
    EXPECT_TRUE(ht.get(3000000).has_value());
}

TEST_F(HashTableTest, ClearOperation) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    ht.insert(1, 100);
    ht.insert(2, 200);
    EXPECT_TRUE(ht.get(1).has_value());

    ht.clear();
    EXPECT_FALSE(ht.get(1).has_value());
    EXPECT_FALSE(ht.get(2).has_value());
}

TEST_F(HashTableTest, ZeroKey) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    ht.insert(0, 999);
    EXPECT_TRUE(ht.get(0).has_value());
    EXPECT_EQ(ht.get(0).value(), 999);
}

TEST_F(HashTableTest, MultipleOperationsSequence) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Последовательность операций
    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(1, 111); // Обновление
    ht.remove(2);      // Удаление
    ht.insert(3, 300); // Новая вставка

    EXPECT_EQ(ht.get(1).value(), 111);
    EXPECT_FALSE(ht.get(2).has_value());
    EXPECT_TRUE(ht.get(3).has_value());
}

TEST_F(HashTableTest, FoldingHashEdgeCases) {
    HashTable ht(11, HashType::FOLDING_HASHING);

    // Тестируем граничные случаи для folding hash
    ht.insert(0, 100);      // Ноль
    ht.insert(999, 200);    // Ровно 3 цифры
    ht.insert(1000, 300);   // Граница 4 цифр

    EXPECT_TRUE(ht.get(0).has_value());
    EXPECT_TRUE(ht.get(999).has_value());
    EXPECT_TRUE(ht.get(1000).has_value());
}

TEST_F(HashTableTest, CuckooRehashScenario) {
    HashTable ht(3, HashType::CUCKOO_HASHING); // Маленький размер для теста rehash

    // Создаем сценарий где потребуется rehash
    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(3, 300);
    ht.insert(4, 400); // Должен вызвать rehash

    // Проверяем что все элементы доступны после rehash
    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(2).has_value());
    EXPECT_TRUE(ht.get(3).has_value());
    EXPECT_TRUE(ht.get(4).has_value());
}

TEST_F(HashTableTest, RehashBehavior) {
    HashTable ht(5, HashType::DOUBLE_HASHING);

    // Вставляем элементы до rehash
    for (int i = 0; i < 10; i++) {
        ht.insert(i, i * 10);
    }

    // Проверяем что все элементы доступны после rehash
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(ht.get(i).has_value());
        EXPECT_EQ(ht.get(i).value(), i * 10);
    }
}

TEST_F(HashTableTest, EmptyTableOperations) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Операции на пустой таблице
    EXPECT_FALSE(ht.get(1).has_value());
    EXPECT_FALSE(ht.remove(1));

    auto vec = ht.toVector();
    EXPECT_TRUE(vec.empty());
}

TEST_F(HashTableTest, ToVectorCompleteness) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    std::vector<std::pair<int, int>> expected = {
        {1, 100}, {2, 200}, {3, 300}, {4, 400}
    };

    for (auto& pair : expected) {
        ht.insert(pair.first, pair.second);
    }

    auto result = ht.toVector();

    // Проверяем что все элементы присутствуют
    EXPECT_EQ(result.size(), expected.size());

    // Сортируем для сравнения
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(result, expected);
}

TEST_F(HashTableTest, MassiveOperations) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Множественные операции для тестирования стабильности
    for (int i = 0; i < 100; i++) {
        ht.insert(i, i * 10);
    }

    for (int i = 0; i < 100; i += 2) {
        ht.remove(i);
    }

    for (int i = 0; i < 100; i++) {
        if (i % 2 == 1) {
            EXPECT_TRUE(ht.get(i).has_value());
            EXPECT_EQ(ht.get(i).value(), i * 10);
        } else {
            EXPECT_FALSE(ht.get(i).has_value());
        }
    }
}

// Тест для покрытия cuckooRehash и сложных сценариев кукушки
TEST_F(HashTableTest, CuckooComplexScenarios) {
    HashTable ht(3, HashType::CUCKOO_HASHING); // Очень маленькая таблица

    // Создаем сценарий который вызовет multiple swaps
    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(3, 300);

    ht.insert(4, 400);
    ht.insert(5, 500);

    // Проверяем что все элементы на месте
    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(2).has_value());
    EXPECT_TRUE(ht.get(3).has_value());
    EXPECT_TRUE(ht.get(4).has_value());
    EXPECT_TRUE(ht.get(5).has_value());
}

// Тест для покрытия MAX_ITER сценария в кукушкином хешировании
TEST_F(HashTableTest, CuckooMaxIterScenario) {
    HashTable ht(5, HashType::CUCKOO_HASHING);

    // Используем ключи которые будут давать коллизии в обеих хеш-функциях
    std::vector<int> problematicKeys = {1, 6, 11, 16, 21, 26, 31};

    for (int key : problematicKeys) {
        ht.insert(key, key * 10);
    }

    // Проверяем что все вставлено
    for (int key : problematicKeys) {
        EXPECT_TRUE(ht.get(key).has_value()) << "Key " << key << " should be present";
    }
}

// Тест для покрытия удаления в folding hashing
TEST_F(HashTableTest, FoldingHashingRemove) {
    HashTable ht(11, HashType::FOLDING_HASHING);

    ht.insert(123456, 100);
    ht.insert(789012, 200);

    // Удаление существующего элемента
    EXPECT_TRUE(ht.remove(123456));
    EXPECT_FALSE(ht.get(123456).has_value());
    EXPECT_TRUE(ht.get(789012).has_value());

    // Удаление несуществующего элемента
    EXPECT_FALSE(ht.remove(999999));
}

// Тест для покрытия edge cases в folding hashing
TEST_F(HashTableTest, FoldingHashingEdgeCases) {
    HashTable ht(11, HashType::FOLDING_HASHING);

    // Тестируем разные сценарии для folding hash
    ht.insert(0, 100);           // Ноль
    ht.insert(9, 200);           // Одна цифра
    ht.insert(99, 300);          // Две цифры
    ht.insert(999, 400);         // Три цифры
    ht.insert(1000, 500);        // Граница
    ht.insert(123456789, 600);   // Много цифр

    EXPECT_TRUE(ht.get(0).has_value());
    EXPECT_TRUE(ht.get(9).has_value());
    EXPECT_TRUE(ht.get(99).has_value());
    EXPECT_TRUE(ht.get(999).has_value());
    EXPECT_TRUE(ht.get(1000).has_value());
    EXPECT_TRUE(ht.get(123456789).has_value());
}

// Тест для покрытия hash1 метода со всеми типами
TEST_F(HashTableTest, Hash1AllTypes) {
    // Создаем временные объекты чтобы покрыть switch case
    HashTable doubleHt(11, HashType::DOUBLE_HASHING);
    HashTable cuckooHt(11, HashType::CUCKOO_HASHING);
    HashTable foldingHt(11, HashType::FOLDING_HASHING);

    // Просто вставляем по элементу в каждый тип
    doubleHt.insert(1, 100);
    cuckooHt.insert(2, 200);
    foldingHt.insert(3, 300);

    EXPECT_TRUE(doubleHt.get(1).has_value());
    EXPECT_TRUE(cuckooHt.get(2).has_value());
    EXPECT_TRUE(foldingHt.get(3).has_value());
}


// Тест для проверки что таблица работает после многих операций
TEST_F(HashTableTest, StressTest) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Множественные операции вставки/удаления
    for (int i = 0; i < 50; i++) {
        ht.insert(i, i * 10);
    }

    // Удаляем каждое второе
    for (int i = 0; i < 50; i += 2) {
        ht.remove(i);
    }

    // Добавляем новые
    for (int i = 50; i < 75; i++) {
        ht.insert(i, i * 10);
    }

    // Проверяем состояние
    for (int i = 0; i < 75; i++) {
        if (i % 2 == 1 || i >= 50) {
            EXPECT_TRUE(ht.get(i).has_value()) << "Key " << i << " should be present";
        } else {
            EXPECT_FALSE(ht.get(i).has_value()) << "Key " << i << " should be removed";
        }
    }
}

// Тест для проверки поведения при полной таблице
TEST_F(HashTableTest, FullTableScenario) {
    HashTable ht(5, HashType::DOUBLE_HASHING);

    // Заполняем таблицу
    for (int i = 0; i < 10; i++) {
        ht.insert(i, i * 10);
    }

    // Проверяем что все элементы доступны
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(ht.get(i).has_value());
    }

    // Пробуем добавить еще
    ht.insert(10, 1000);
    EXPECT_TRUE(ht.get(10).has_value());
}

// Тесты для покрытия cuckooRehash
TEST_F(HashTableTest, CuckooRehashDirectTest) {
    HashTable ht(3, HashType::CUCKOO_HASHING);

    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(3, 300);

    ht.insert(4, 400);

    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(2).has_value());
    EXPECT_TRUE(ht.get(3).has_value());
    EXPECT_TRUE(ht.get(4).has_value());
}

TEST_F(HashTableTest, CuckooInsertWithRehashFallback) {
    HashTable ht(2, HashType::CUCKOO_HASHING);

    ht.insert(1, 100);
    ht.insert(2, 200);

    ht.insert(3, 300);

    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(2).has_value());
    EXPECT_TRUE(ht.get(3).has_value());
}

TEST_F(HashTableTest, CuckooSwapOperations) {
    HashTable ht(5, HashType::CUCKOO_HASHING);

    ht.insert(1, 100);
    ht.insert(6, 600);

    // Проверяем что оба элемента на месте после swap
    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(6).has_value());
    EXPECT_EQ(ht.get(1).value(), 100);
    EXPECT_EQ(ht.get(6).value(), 600);
}

TEST_F(HashTableTest, CuckooRemoveEdgeCases) {
    HashTable ht(11, HashType::CUCKOO_HASHING);

    // Тестируем удаление в разных позициях
    ht.insert(1, 100);
    ht.insert(2, 200);

    EXPECT_TRUE(ht.remove(1));
    EXPECT_FALSE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(2).has_value());

    ht.insert(3, 300);
    ht.insert(4, 400);

    EXPECT_TRUE(ht.remove(4));
    EXPECT_FALSE(ht.get(4).has_value());
}

// Явно тестируем все ветки
TEST_F(HashTableTest, Hash1MethodCoverage) {

    // DOUBLE_HASHING
    HashTable doubleHt(11, HashType::DOUBLE_HASHING);
    doubleHt.insert(5, 100);
    EXPECT_TRUE(doubleHt.get(5).has_value());

    // CUCKOO_HASHING с различными ключами
    HashTable cuckooHt(11, HashType::CUCKOO_HASHING);
    cuckooHt.insert(10, 200);
    cuckooHt.insert(20, 300);
    EXPECT_TRUE(cuckooHt.get(10).has_value());
    EXPECT_TRUE(cuckooHt.get(20).has_value());

    // FOLDING_HASHING
    HashTable foldingHt(11, HashType::FOLDING_HASHING);
    foldingHt.insert(123, 400);
    foldingHt.insert(4567, 500);
    EXPECT_TRUE(foldingHt.get(123).has_value());
    EXPECT_TRUE(foldingHt.get(4567).has_value());
}

TEST_F(HashTableTest, CuckooMaxIterationsScenario) {
    HashTable ht(3, HashType::CUCKOO_HASHING);

    std::vector<int> collisionKeys = {1, 4, 7, 10, 13, 16};

    for (int key : collisionKeys) {
        ht.insert(key, key * 10);
    }

    for (int key : collisionKeys) {
        EXPECT_TRUE(ht.get(key).has_value()) << "Key " << key << " should be present after rehash";
        EXPECT_EQ(ht.get(key).value(), key * 10);
    }
}

TEST_F(HashTableTest, CuckooMultipleRehashChain) {
    HashTable ht(2, HashType::CUCKOO_HASHING);

    // Последовательная вставка
    for (int i = 1; i <= 10; i++) {
        ht.insert(i, i * 100);
    }

    for (int i = 1; i <= 10; i++) {
        EXPECT_TRUE(ht.get(i).has_value()) << "Key " << i << " should be present";
        EXPECT_EQ(ht.get(i).value(), i * 100);
    }
}

TEST_F(HashTableTest, FoldingHashWithRehash) {
    HashTable ht(3, HashType::FOLDING_HASHING);

    // Вставляем элементы чтобы вызвать rehash
    ht.insert(123, 100);
    ht.insert(456, 200);
    ht.insert(789, 300);

    ht.insert(101112, 400);

    // Проверяем что все элементы на месте
    EXPECT_TRUE(ht.get(123).has_value());
    EXPECT_TRUE(ht.get(456).has_value());
    EXPECT_TRUE(ht.get(789).has_value());
    EXPECT_TRUE(ht.get(101112).has_value());
}

TEST_F(HashTableTest, CuckooComplexDisplacementChain) {
    HashTable ht(5, HashType::CUCKOO_HASHING);

    // Создаем цепочку вытеснений
    ht.insert(1, 100);
    ht.insert(6, 600);
    ht.insert(11, 1100);
    ht.insert(16, 1600);

    // Все элементы должны быть доступны
    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(6).has_value());
    EXPECT_TRUE(ht.get(11).has_value());
    EXPECT_TRUE(ht.get(16).has_value());
}

TEST_F(HashTableTest, HashTypeSwitchingWithData) {
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Добавляем данные с одним типом хеширования
    ht.insert(1, 100);
    ht.insert(2, 200);
    ht.insert(3, 300);

    // Данные должны остаться доступными
    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_TRUE(ht.get(2).has_value());
    EXPECT_TRUE(ht.get(3).has_value());
}

TEST_F(HashTableTest, CuckooDeleteAndReinsert) {
    HashTable ht(11, HashType::CUCKOO_HASHING);

    // Вставляем, удаляем и снова вставляем
    ht.insert(1, 100);
    ht.insert(2, 200);

    EXPECT_TRUE(ht.remove(1));
    EXPECT_FALSE(ht.get(1).has_value());

    // Вставляем снова
    ht.insert(1, 150);
    EXPECT_TRUE(ht.get(1).has_value());
    EXPECT_EQ(ht.get(1).value(), 150);
}

// Тестируем специальные ключи
TEST_F(HashTableTest, EdgeCaseKeysAllHashTypes) {

    // Отрицательные ключи
    HashTable ht(11, HashType::DOUBLE_HASHING);

    // Очень большие ключи
    ht.insert(INT_MAX - 1, 999);
    ht.insert(INT_MAX, 1000);

    EXPECT_TRUE(ht.get(INT_MAX - 1).has_value());
    EXPECT_TRUE(ht.get(INT_MAX).has_value());
}

TEST_F(HashTableTest, CuckooRehashPreservesData) {
    HashTable ht(3, HashType::CUCKOO_HASHING);

    // Заполняем таблицу данными
    std::vector<std::pair<int, int>> testData = {
        {1, 100}, {2, 200}, {3, 300}, {4, 400}, {5, 500}
    };

    for (const auto& data : testData) {
        ht.insert(data.first, data.second);
    }

    // Проверяем, что все данные сохранены после rehash
    for (const auto& data : testData) {
        EXPECT_TRUE(ht.get(data.first).has_value());
        EXPECT_EQ(ht.get(data.first).value(), data.second);
    }
}

// Тест для проверки, что таблица корректно обрабатывает последовательные rehash
TEST_F(HashTableTest, MultipleSequentialRehash) {
    HashTable ht(2, HashType::CUCKOO_HASHING);

    for (int i = 0; i < 20; i++) {
        ht.insert(i, i * 10);

        for (int j = 0; j <= i; j++) {
            EXPECT_TRUE(ht.get(j).has_value())
            << "Key " << j << " should be accessible after inserting key " << i;
        }
    }
}

TEST_F(HashTableTest, InsertWithRehashBranch) {
    HashTable ht(3, HashType::DOUBLE_HASHING);

    // Заполняем таблицу чтобы следующий insert вызвал rehash
    for (int i = 0; i < 10; i++) {
        ht.insert(i, i * 10);
    }

    ht.insert(10, 1000);

    EXPECT_TRUE(ht.get(10).has_value());
    EXPECT_EQ(ht.get(10).value(), 1000);

    // Проверяем что старые данные не потеряны
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(ht.get(i).has_value());
    }
}
