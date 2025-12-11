#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    void insert(Node*& node, int val) {
        if (node == nullptr) {
            node = new Node(val);
            return;
        }
        if (val < node->value) {
            insert(node->left, val);
        } else if (val > node->value) {
            insert(node->right, val);
        }
    }

    bool search(Node* node, int val) const {
        if (node == nullptr) return false;
        if (val == node->value) return true;
        if (val < node->value) return search(node->left, val);
        return search(node->right, val);
    }

    bool isFull(Node* node) const {
        if (node == nullptr) return true;
        if (node->left == nullptr && node->right == nullptr) return true;
        if (node->left != nullptr && node->right != nullptr) {
            return isFull(node->left) && isFull(node->right);
        }
        return false;
    }

    void inorderPrint(Node* node) const {
        if (node == nullptr) return;
        inorderPrint(node->left);
        cout << node->value << " ";
        inorderPrint(node->right);
    }

    void collectForks(Node* node, vector<int>& forks) const {
        if (node == nullptr) return;
        collectForks(node->left, forks);
        if (node->left != nullptr && node->right != nullptr) {
            forks.push_back(node->value);
        }
        collectForks(node->right, forks);
    }

public:
    BST() : root(nullptr) {}

    void add(int val) {
        insert(root, val);
    }

    bool find(int val) const {
        return search(root, val);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    int getRoot() const {
        if (root == nullptr) {
            throw runtime_error("Дерево пустое");
        }
        return root->value;
    }

    bool isFull() const {
        return isFull(root);
    }

    void printInOrder() const {
        if (isEmpty()) {
            cout << "Дерево пустое" << endl;
            return;
        }
        inorderPrint(root);
        cout << endl;
    }

    void printForks() const {
        vector<int> forks;
        collectForks(root, forks);
        for (size_t i = 0; i < forks.size(); ++i) {
            if (i > 0) cout << " ";
            cout << forks[i];
        }
        cout << endl;
    }
};