#include <iostream>
#include <string>

struct AVLNode {
    std::string key;
    AVLNode* left;
    AVLNode* right;
    long long height = 1;

    AVLNode(std::string key) : key{key}, left{nullptr}, right{nullptr} {}
    AVLNode(std::string key, AVLNode* left, AVLNode* right) 
        : key{key}, left{left}, right{right} {}
};

long long getNodeHeight(AVLNode* node) {
    return (node == nullptr) ? 0 : node->height;
}

long long updateHeight(AVLNode* node) {
    long long leftHeight = getNodeHeight(node->left);
    long long rightHeight = getNodeHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

long long getBalanceFactor(AVLNode* node) {
    return getNodeHeight(node->right) - getNodeHeight(node->left);
}

AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->height = updateHeight(node);
    newRoot->height = updateHeight(newRoot);
    return newRoot;
}

AVLNode* rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = updateHeight(node);
    newRoot->height = updateHeight(newRoot);
    return newRoot;
}

AVLNode* doubleRotateLeft(AVLNode* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

AVLNode* doubleRotateRight(AVLNode* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

AVLNode* balanceTree(AVLNode* node) {
    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->right) < 0) {
            return doubleRotateLeft(node);
        }
        return rotateLeft(node);
    }
    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->left) >= 0) {
            return doubleRotateRight(node);
        }
        return rotateRight(node);
    }
    return node;
}

AVLNode* insertNode(AVLNode* node, const std::string& key) {
    if (node == nullptr) {
        return new AVLNode(key);
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    }
    node->height = updateHeight(node);
    return balanceTree(node);
}

bool searchNode(AVLNode* node, const std::string& key) {
    if (node == nullptr) return false;
    if (key == node->key) return true;
    return key < node->key ? searchNode(node->left, key) : searchNode(node->right, key);
}

void preorderTraversal(AVLNode* node) {
    if (node) {
        std::cout << node->key << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

int countPoints(const std::string& name, AVLNode* firstFriend, AVLNode* secondFriend) {
    int firstScore = (searchNode(firstFriend, name) == false) ? 1 : 0;
    int secondScore = (searchNode(secondFriend, name) == false) ? 1 : 0;
    if (firstScore == secondScore && firstScore == 1) {
        return 3;
    } else if (firstScore == secondScore && firstScore == 0) {
        return 0;
    }
    return 1;
}

int calculateTotalPoints(AVLNode* root, int points, AVLNode* firstFriend, AVLNode* secondFriend) {
    if (root == nullptr) {
        return points;
    }

    points += calculateTotalPoints(root->left, 0, firstFriend, secondFriend);
    points += calculateTotalPoints(root->right, 0, firstFriend, secondFriend);
    points += countPoints(root->key, firstFriend, secondFriend);
    return points;
}

int main() {
    int n; 
    std::cin >> n;
    AVLNode* friends[3] = { nullptr, nullptr, nullptr };
    std::string name;
    
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> name;
            friends[i] = insertNode(friends[i], name);
        }
    }
    
    int result1 = calculateTotalPoints(friends[0], 0, friends[1], friends[2]);
    int result2 = calculateTotalPoints(friends[1], 0, friends[0], friends[2]);
    int result3 = calculateTotalPoints(friends[2], 0, friends[0], friends[1]);
    
    std::cout << result1 << " " << result2 << " " << result3;
    return 0;
}
