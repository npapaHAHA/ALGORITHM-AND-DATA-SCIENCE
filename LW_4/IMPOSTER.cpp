#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

struct Tree {
    Node* root = nullptr;

    Node* buildTreeFromPreorder(std::vector<int>& preorder_data, int min_val, int max_val, int& index) {
        if (index >= preorder_data.size()) return nullptr;

        int key = preorder_data[index];
        if (key < min_val || key >= max_val) return nullptr;

        Node* node = new Node(key);
        index++;
        node->left = buildTreeFromPreorder(preorder_data, min_val, key, index);
        node->right = buildTreeFromPreorder(preorder_data, key, max_val, index);
        return node;
    }

    // Измененная функция inorderTraversal
    void inorderTraversal(Node* node, std::vector<int>& result) {
        std::vector<Node*> stack;
        Node* current = node;

        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push_back(current);
                current = current->left;
            }
            current = stack.back();
            stack.pop_back();
            result.push_back(current->key);
            current = current->right;
        }
    }

    void postorderTraversal(Node* node, std::vector<int>& result) {
        if (node != nullptr) {
            postorderTraversal(node->left, result);
            postorderTraversal(node->right, result);
            result.push_back(node->key);
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> slavas_preorder, slavas_inorder, slavas_postorder;

    for (int i = 0; i < n; ++i) {
        int key;
        std::cin >> key;
        slavas_preorder.push_back(key);
    }

    for (int i = 0; i < n; ++i) {
        int key;
        std::cin >> key;
        slavas_inorder.push_back(key);
    }

    for (int i = 0; i < n; ++i) {
        int key;
        std::cin >> key;
        slavas_postorder.push_back(key);
    }

    Tree tree;
    bool result_inorder = false;
    bool result_postorder = false;

    int temp_index = 0;
    tree.root = tree.buildTreeFromPreorder(slavas_preorder, -1000000000, 1000000001, temp_index);

    std::vector<int> check_inorder;
    std::vector<int> check_postorder;

    tree.inorderTraversal(tree.root, check_inorder);
    tree.postorderTraversal(tree.root, check_postorder);

    if (check_inorder == slavas_inorder) {
        result_inorder = true;
    }

    if (check_postorder == slavas_postorder) {
        result_postorder = true;
    }

    if (result_inorder && result_postorder) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
