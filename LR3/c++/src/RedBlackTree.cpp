#include "../include/RedBlackTree.h"

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>

// ---------------- Node ----------------
Node::Node(int val) { // конструктор узла
    data = val;
    color = RED;
    left = right = parent = nullptr;
}

// ---------------- RedBlackTree ----------------
RedBlackTree::RedBlackTree() { // конструктор дерева
    NIL = new Node(0);
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = nullptr;
    root = NIL;
}

// Вспомогательные повороты
void RedBlackTree::rotateLeft(Node* x) { // левый поворот
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node* x) { // правый поворот
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

// Вставка
void RedBlackTree::insert(int key) { // вставка элемента
    Node* node = new Node(key);
    node->parent = nullptr;
    node->left = node->right = NIL;
    node->color = RED;

    Node* y = nullptr;
    Node* x = root;

    while (x != NIL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    fixInsert(node);
}

// Балансировка после вставки
void RedBlackTree::fixInsert(Node* k) { // восстановление свойств после вставки
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->left) {
            Node* u = k->parent->parent->right; // дядя
            if (u->color == RED) {
                // случай 1
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    // случай 2
                    k = k->parent;
                    rotateLeft(k);
                }
                // случай 3
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(k->parent->parent);
            }
        } else {
            Node* u = k->parent->parent->left; // дядя
            if (u->color == RED) {
                k->parent->color = BLACK;
                u->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = BLACK;
}

// Поиск
Node* RedBlackTree::search(Node* node, int key) { // поиск узла
    if (node == NIL || key == node->data) {
        return node;
    }
    if (key < node->data) {
        return search(node->left, key);
    }
    return search(node->right, key);
}

bool RedBlackTree::contains(int key) { // проверка наличия
    return search(root, key) != NIL;
}

std::string RedBlackTree::getNodeInfo(Node* node) { // информация об узле
    if (node == NIL) return "";
    std::string info = std::to_string(node->data);
    info += " (";
    if (node == root) {
        info += "ROOT, ";
    }
    info += (node->color == BLACK ? "BLACK" : "RED");
    info += ")";
    return info;
}


void RedBlackTree::inorder(Node* node) { // обход in-order
    if (node != NIL) {
        inorder(node->left);
        std::cout << getNodeInfo(node) << " ";
        inorder(node->right);
    }
}

void RedBlackTree::print() { // вывод дерева
    inorder(root);
    std::cout << std::endl;
}

std::vector<int> RedBlackTree::toVector() const { // преобразовать в вектор
    std::vector<int> res;
    std::function<void(Node*)> dfs = [&](Node* n) {
        if (n == NIL) return;
        dfs(n->left);
        res.push_back(n->data);
        dfs(n->right);
    };
    dfs(root);
    return res;
}

Node* RedBlackTree::minimum(Node* node) { // поиск минимума
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

void RedBlackTree::transplant(Node* u, Node* v) { // замена поддерева
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RedBlackTree::remove(int key) { // удаление элемента
    Node* z = search(root, key);
    if (z == NIL) {
        std::cout << "Элемент " << key << " не найден\n";
        return;
    }

    Node* y = z;
    Node* x;
    Color yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right); // преемник
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK) {
        fixDelete(x);
    }
}

void RedBlackTree::fixDelete(Node* x) { // балансировка после удаления
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right; // брат
            if (w->color == RED) {
                // случай 1
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // случай 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // случай 3
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                // случай 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left; // брат
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

std::pair<bool,int> RedBlackTree::validateHelper(Node* node) const { // проверка свойств дерева
    if (node == NIL) {
        return {true, 1}; // NIL считается чёрным листом
    }

    // левое и правое поддеревья
    auto leftRes = validateHelper(node->left);
    auto rightRes = validateHelper(node->right);

    if (!leftRes.first || !rightRes.first) {
        return {false, 0};
    }

    // чёрная высота левой и правой ветви должны совпадать
    if (leftRes.second != rightRes.second) {
        return {false, 0};
    }

    // правило: у красного узла не может быть красного ребёнка
    if (node->color == RED) {
        if (node->left != NIL && node->left->color == RED) return {false, 0};
        if (node->right != NIL && node->right->color == RED) return {false, 0};
    }

    int add = (node->color == BLACK) ? 1 : 0;
    return {true, leftRes.second + add};
}

bool RedBlackTree::validate() { // результат проверки
    // пустое дерево — валидно
    if (root == NIL) {
        std::cout << "Проверка: пустое дерево — OK\n";
        return true;
    }

    // корень должен быть чёрным
    if (root->color != BLACK) {
        std::cout << "Ошибка проверки: корень не ЧЁРНЫЙ\n";
        return false;
    }

    auto res = validateHelper(root);
    if (!res.first) {
        std::cout << "Ошибка проверки: нарушены свойства (красный родитель или разная чёрная высота)\n";
        return false;
    }

    std::cout << "Проверка пройдена: дерево удовлетворяет свойствам (чёрная высота = " << res.second << ")\n";
    return true;
}

// Бинарная сериализация
void RedBlackTree::serializeBinary(std::ostream& os) const {
    std::vector<int> vec = toVector();
    size_t size = vec.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    if (size > 0) {
        os.write(reinterpret_cast<const char*>(vec.data()), size * sizeof(int));
    }
}

// Бинарная десериализация
void RedBlackTree::deserializeBinary(std::istream& is) {
    // Очищаем текущее дерево
    std::vector<int> keys = toVector();
    for (int key : keys) {
        remove(key);
    }

    // Загружаем новые данные
    size_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));

    if (size > 0) {
        std::vector<int> temp(size);
        is.read(reinterpret_cast<char*>(temp.data()), size * sizeof(int));

        for (int value : temp) {
            insert(value);
        }
    }
}

// Текстовая сериализация
void RedBlackTree::serializeText(std::ostream& os) const {
    std::vector<int> vec = toVector();
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) os << " ";
    }
}

// Текстовая десериализация
void RedBlackTree::deserializeText(std::istream& is) {
    // Очищаем текущее дерево
    std::vector<int> keys = toVector();
    for (int key : keys) {
        remove(key);
    }

    // Загружаем новые данные
    int value;
    while (is >> value) {
        insert(value);
    }
}
