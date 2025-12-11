#include "FullBinaryTree.h"

// Построение полного бинарного дерева
TreeNode* insertNode(TreeNode* node, int data, int& size) {
    if (!node) {
        size++;
        TreeNode* newNode = new TreeNode;
        newNode->data = data;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    
    if (data < node->data) {
        node->left = insertNode(node->left, data, size);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data, size);
    }   //если есть уже такой узел
        return node;
}

void insert(T* tree, int data) {
    tree->root = insertNode(tree->root, data, tree->size);
}

bool isFullBinaryTree(const TreeNode *node)
{
    if (!node)
        return true;
    
    // лист
    if (!(node -> left) && !(node -> right))
        return true;
    
    // оба ребенлка
    if (node -> left && node -> right) {
        return isFullBinaryTree(node -> left) && isFullBinaryTree(node -> right);
    }
    
    // один ребенок
    return false;
}

bool isFull(const T *tree)
{
    if (!tree)
        return false;
    return isFullBinaryTree(tree -> root);
}

//обход корень лево право
void printPreOrder(TreeNode* tree) {
    if (tree) {
        std::cout << tree->data << " ";
        printPreOrder(tree->left);
        printPreOrder(tree->right);
    }
    
}

// Рекурсивный поиск узла в дереве
TreeNode* findNode(TreeNode* node, int data) {
    if (!node) {
        return nullptr;
    }
    if (data == node->data) {
        return node;
    }
    if (data < node->data) {
        return findNode(node->left, data);
    } else {
        return findNode(node->right, data);
    }
}

// Обёртка для всего дерева
TreeNode* find(const T* tree, int data) {
    if (!tree) {
        return nullptr;
    }
    return findNode(tree->root, data);
}

// Освобождение памяти
void freeTree(TreeNode* node) {
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}