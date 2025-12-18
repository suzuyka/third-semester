#pragma once
#include <string>

#include "RedBlackTree.h"
#include "Array.h"

// обработчик команд для структур данных
class CommandProcessor {
public:
    void execute(const std::string& query, const std::string& filename); // выполнить команду
};
