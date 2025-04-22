#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

struct TreeNode {
    TreeNode *left, *right;
    char symbol;
    int height, balance, freq;
    std::string code;

    TreeNode(char sym) : left(nullptr), right(nullptr), symbol(sym), height(1), balance(0), freq(1), code("") {}
    TreeNode(char sym, std::string c) : left(nullptr), right(nullptr), symbol(sym), height(1), balance(0), freq(1), code(c) {}
};

class AVLTree {
    TreeNode* root = nullptr;
    std::vector<TreeNode*> nodes;

    TreeNode* insert(TreeNode* node, char sym) {
        if (!node) return new TreeNode(sym);
        if (sym < node->symbol) node->left = insert(node->left, sym);
        else if (sym > node->symbol) node->right = insert(node->right, sym);
        else node->freq++;
        return balance(node);
    }

    TreeNode* insert(TreeNode* node, char sym, std::string c) {
        if (!node) return new TreeNode(sym, c);
        if (sym < node->symbol) node->left = insert(node->left, sym, c);
        else if (sym > node->symbol) node->right = insert(node->right, sym, c);
        return balance(node);
    }

    int getHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(TreeNode* node) {
        return node ? getHeight(node->right) - getHeight(node->left) : 0;
    }

    TreeNode* rotateLeft(TreeNode* node) {
        TreeNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    TreeNode* rotateRight(TreeNode* node) {
        TreeNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    TreeNode* balance(TreeNode* node) {
        if (!node) return nullptr;
        updateHeight(node);
        if (node->balance == 2) {
            if (node->right->balance < 0) node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (node->balance == -2) {
            if (node->left->balance > 0) node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }

    void updateHeight(TreeNode* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        node->balance = getBalance(node);
    }

    void traverse(TreeNode* node) {
        if (!node) return;
        traverse(node->left);
        nodes.push_back(node);
        traverse(node->right);
    }

public:
    void add(char sym) {
        root = insert(root, sym);
    }

    void add(char sym, std::string c) {
        root = insert(root, sym, c);
    }

    TreeNode* find(char sym) {
        TreeNode* current = root;
        while (current && current->symbol != sym) {
            current = (sym < current->symbol) ? current->left : current->right;
        }
        return current;
    }

    std::vector<TreeNode*> getNodes() {
        nodes.clear();
        traverse(root);
        return nodes;
    }
};

struct HuffmanNode {
    char symbol;
    int freq;
    HuffmanNode *left, *right;
};

HuffmanNode* createHuffmanNode(char sym, int f, HuffmanNode* l, HuffmanNode* r) {
    HuffmanNode* node = new HuffmanNode();
    node->symbol = sym;
    node->freq = f;
    node->left = l;
    node->right = r;
    return node;
}

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

HuffmanNode* buildHuffmanTree(const std::string& input) {
    AVLTree freqMap;
    for (char c : input) freqMap.add(c);

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (auto node : freqMap.getNodes()) {
        pq.push(createHuffmanNode(node->symbol, node->freq, nullptr, nullptr));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        pq.push(createHuffmanNode('\0', left->freq + right->freq, left, right));
    }

    return pq.top();
}

void buildEncodingTable(HuffmanNode* root, std::string code, AVLTree& table) {
    if (!root) return;
    if (root->symbol != '\0') table.add(root->symbol, code);
    buildEncodingTable(root->left, code + "0", table);
    buildEncodingTable(root->right, code + "1", table);
}

std::string encode(const std::string& input, AVLTree& table) {
    std::string encoded;
    for (char c : input) encoded += table.find(c)->code;
    return encoded;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string input;
    std::cin >> input;

    HuffmanNode* huffmanRoot = buildHuffmanTree(input);
    AVLTree encodingTable;
    buildEncodingTable(huffmanRoot, "", encodingTable);

    std::string encoded = encode(input, encodingTable);
    std::cout << encoded.size() << "\n";

    return 0;
}