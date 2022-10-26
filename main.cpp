#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

// struct that desctibes every node in tree.
struct Node {
    int64_t value;
    Node *left;
    Node *right;
    Node *parent;

    explicit Node(int64_t x) {
        value = x;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class Tree {

private:
    // this method is being called in destructror
    void deleteNode(Node *node) {
        if (node != nullptr) {
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }
    }

    Node *root_;
    std::vector<int64_t> values_; // vector that helps to print all the vallues
    std::vector<int64_t> leafs_; // this vector helps to print all the leafs

public:
    explicit Tree() {
        root_ = nullptr;
    }

    ~Tree() {
        deleteNode(root_);
    }
    // method that finds second maximum in the tree
    int64_t max2(const Node *node) {
        if (node->right != nullptr) {
            return max2(node->right);
        } else if (node->right == nullptr) {
            if (node->left != nullptr) {
                return node->left->value;
            } else {
                return node->parent->value;
            }
        }
        return node->value;
    }

    int64_t max2() {
        return max2(root_);
    }
    // additional method that calls from main insert method
    void insert(Node *node, int64_t value) {
        if (value < node->value) {
            if (node->left == nullptr) {
                Node *new_node = new Node(value);
                node->left = new_node;
                new_node->parent = node;

            } else {
                insert(node->left, value);
            }
        } else if (value > node->value) {
            if (node->right == nullptr) {
                Node *new_node = new Node(value);
                node->right = new_node;
                new_node->parent = node;
            } else {
                insert(node->right, value);
            }
        }
    }
    // base method to insert the value in the tree
    void insert(int64_t value) {
        if (value == 0) {
            printf("%zu", getHeight());
            return;
        }
        values_.push_back(value);
        // если дерево пустое, то создаем корень.
        if (root_ == nullptr) {
            root_ = new Node(value);
            return;
        }
        // если корень уже есть, то начинаем искать место для очередного элемента, начиная с корня
        insert(root_, value);
    }
    // method allows to find the height of the tree
    [[nodiscard]] size_t getHeight() {
        if (root_ == nullptr) {
            return 0;
        }
        return getHeight(root_);
    }

    size_t getHeight(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        auto left_tree_height = getHeight(node->left);
        auto right_tree_height = getHeight(node->right);
        return std::max(left_tree_height, right_tree_height) + 1;
    }
    // method to print all the values ordered by ascending
    void printValues() {
        std::sort(values_.begin(), values_.end());
        auto copies = std::unique(values_.begin(), values_.end());
        values_.erase(copies, values_.end());
        for (auto el : values_) {
            printf("%lld", el);
            printf("\n");
        }
    }
    // method to find all the leafs
    void findLeafes(Node *node) {
        if (node->right != nullptr) {
            findLeafes(node->right);
        }
        if (node->left != nullptr) {
            findLeafes(node->left);
        }
        if (node->right == nullptr && node->left == nullptr) {
            leafs_.push_back(node->value);
        }
    }
    // method to print all the leafes
    void printLeafes() {
        findLeafes(root_);
        std::sort(leafs_.begin(), leafs_.end());
        auto copies = std::unique(leafs_.begin(), leafs_.end());
        leafs_.erase(copies, leafs_.end());
        for (auto el : leafs_) {
            printf("%lld", el);
            printf("\n");
        }
    }
};