#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* left_child;
    Node* right_child;

    Node(int val) : value(val), left_child(nullptr), right_child(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }

    void inorderedTravel(Node* element) const {
        if (element == nullptr) {
            return;
        }
        inorderedTravel(element->left_child);
        std::cout << element->value << " ";
        inorderedTravel(element->right_child);
    }

private:
    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left_child = insertRec(node->left_child, value);
        } else {
            node->right_child = insertRec(node->right_child, value);
        }
        return node;
    }
};

int main() {
    int n;
    std::cin >> n;

    BST tree;

    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        tree.insert(value);
    }

    tree.inorderedTravel(tree.root);
    std::cout << std::endl;

    return 0;
}
