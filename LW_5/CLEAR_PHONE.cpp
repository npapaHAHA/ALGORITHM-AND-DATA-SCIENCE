#include <cstdint>
#include <iostream>

struct TreeNode {
    std::string value;
    TreeNode* left;
    TreeNode* right;
    long long height = 1;

    TreeNode(std::string value) : value{ value }, left{ nullptr }, right{ nullptr } {}
    TreeNode(std::string value, TreeNode* left, TreeNode* right) : value{ value }, left{ left }, right{ right } {}
};

long long getTreeHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

long long fixHeight(TreeNode* node) {
    return std::max(getTreeHeight(node->right), getTreeHeight(node->left)) + 1;
}

long long balanceFactor(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getTreeHeight(node->right) - getTreeHeight(node->left);
}

TreeNode* rotateLeft(TreeNode* node) {
    TreeNode* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    tmp->height = fixHeight(tmp);
    node->height = fixHeight(node);
    return tmp;
}

TreeNode* rotateRight(TreeNode* node) {
    TreeNode* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    tmp->height = fixHeight(tmp);
    node->height = fixHeight(node);
    return tmp;
}

TreeNode* doubleRotateLeft(TreeNode* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

TreeNode* doubleRotateRight(TreeNode* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

TreeNode* balanceTree(TreeNode* node) {
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0) {
            return doubleRotateLeft(node);
        } else {
            return rotateLeft(node);
        }
    } else if (balanceFactor(node) == -2) {
        if (balanceFactor(node->left) >= 0) {
            return doubleRotateRight(node);
        } else {
            return rotateRight(node);
        }
    }
    return node;
}

TreeNode* insertNode(TreeNode* root, std::string value) {
    if (root == nullptr) {
        TreeNode* newRoot = new TreeNode(value);
        return newRoot;
    }
    if (value < root->value) {
        root->left = insertNode(root->left, value);
    } else if (value > root->value) {
        root->right = insertNode(root->right, value);
    }
    root->height = fixHeight(root);
    return balanceTree(root);
}

bool searchNode(TreeNode* root, std::string value) {
    if (root == nullptr) {
        return false;
    }
    if (value == root->value) {
        return true;
    }
    if (value < root->value) {
        return searchNode(root->left, value);
    } else {
        return searchNode(root->right, value);
    }
}

void preorderTraversal(TreeNode* root) {
    if (root != nullptr) {
        std::cout << root->value << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n; 
    std::cin >> n;
    
    std::string value;
    long long result = 0;
    TreeNode* root = nullptr;

    for (long long i = 0; i < n; ++i) {
        std::cin >> value;
        if (!searchNode(root, value)) {
            root = insertNode(root, value);
        } else {
            uint8_t* countArray = new uint8_t[257]{ 0 };
            long long strLength = value.length();
            for (long long i = 0; i < value.size(); ++i) {
                if (countArray[value[i]] == 0) {
                    ++countArray[value[i]];
                    ++result;
                }
            }
        }
    }

    std::cout << result;
    return 0;
}
