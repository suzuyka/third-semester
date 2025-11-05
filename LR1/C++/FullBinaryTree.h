#ifndef FULL_BINARY_TREE_H
#define FULL_BINARY_TREE_H

#include <iostream>
#include <string>

// Узел полного бинарного дерева
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

};

struct T {
    TreeNode* root = nullptr;
    int size = 0;
};

TreeNode* insertNode(TreeNode* node, int data, int& size);

void insert(T* tree, int data);

bool isFull(const T* tree);
bool isFullBinaryTree(const TreeNode *node);
// Печать дерева (preorder)
void printPreOrder(TreeNode* node);

// Освобождение памяти
void freeTree(TreeNode* node);

// Поиск узла по значению (возвращает указатель на узел)
TreeNode* findNode(TreeNode* node, int data);

// Обёртка для дерева
TreeNode* find(const T* tree, int data);

#endif // FULL_BINARY_TREE_H