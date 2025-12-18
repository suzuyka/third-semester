#pragma once
#include <string>
#include <vector>
#include <utility>

enum Color { RED, BLACK };                                      // цвета узлов

struct Node {                                                   // узел красно-чёрного дерева
    int data;
    Color color;
    Node *left, *right, *parent;
    Node(int val);
};

class RedBlackTree {                                            // красно-чёрное дерево
private:
    Node* root;                                                 // корень дерева
    Node* NIL;                                                  // листовые узлы
    void rotateLeft(Node* x);                                   // левый поворот
    void rotateRight(Node* x);                                  // правый поворот
    void fixInsert(Node* x);                                    // балансировка после вставки
    void fixDelete(Node* x);                                    // балансировка после удаления
    void transplant(Node* u, Node* v);                          // замена поддерева
    Node* minimum(Node* node);                                  // поиск минимума в поддереве
    void inorder(Node* node);                                   // симметричный обход
    Node* search(Node* node, int key);                          // поиск узла
    std::string getNodeInfo(Node* node);                        // информация об узле
public:
    RedBlackTree();                                             // конструктор
    void insert(int key);                                       // вставка элемента
    void remove(int key);                                       // удаление элемента
    bool contains(int key);                                     // проверка наличия
    std::pair<bool,int> validateHelper(Node* node) const;       // проверка свойств дерева
    std::vector<int> toVector() const;                          // преобразовать в вектор
    bool validate();                                            // результат проверки
    void print();                                               // вывод дерева

    // Бинарная сериализация/десериализация
    void serializeBinary(std::ostream& os) const;
    void deserializeBinary(std::istream& is);

    // Текстовая сериализация/десериализация
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
};
