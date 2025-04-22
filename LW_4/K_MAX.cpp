#include <iostream>

struct Node {
    int key;
    int size;
    Node* left;
    Node* right;
    Node* parent;
};

struct BST {
    Node* root = nullptr;

    Node* k_maximum(Node* root, int k) {
    while (root != nullptr) {
        int right_subtree_size = (root->right != nullptr) ? root->right->size : 0;
        int node_num = right_subtree_size + 1;

        if (k == node_num) {
            return root;
        } else if (k > node_num) {
            k -= node_num;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return nullptr;
}


    Node* minimum(Node* x) {
        if (x->left == nullptr) {
            return x;
        }
        return minimum(x->left);
    }

    Node* maximum(Node* x) {
        if (x->right == nullptr) {
            return x;
        }
        return maximum(x->right);
    }

    Node* insert(Node* x, int z) {
        if (x == nullptr) {
            Node* newNode = new Node;
            newNode->key = z;
            newNode->size = 1;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        if (z < x->key) {
            x->left = insert(x->left, z);
        } else if (z > x->key) {
            x->right = insert(x->right, z);
        }

        int left_subtree_size = 0;
        if (x->left != nullptr) {
            left_subtree_size = x->left->size;
        }

        int right_subtree_size = 0;
        if (x->right != nullptr) {
            right_subtree_size = x->right->size;
        }

        int total_size = left_subtree_size + right_subtree_size + 1;
        x->size = total_size;
        return x;
    }

    Node* del(Node* root, int z) {
        if (root == nullptr) {
            return root;
        }

        if (z < root->key) {
            root->left = del(root->left, z);
        } else if (z > root->key) {
            root->right = del(root->right, z);
        } else if (root->left != nullptr && root->right != nullptr) {
            root->key = minimum(root->right)->key;
            root->right = del(root->right, root->key);
        } else {
            if (root->left != nullptr) {
                root = root->left;
            } else if (root->right != nullptr) {
                root = root->right;
            } else {
                root = nullptr;
            }
        }

        if (root != nullptr) {
            int left_subtree_size = 0;
            if (root->left != nullptr) {
                left_subtree_size = root->left->size;
            }

            int right_subtree_size = 0;
            if (root->right != nullptr) {
                right_subtree_size = root->right->size;
            }

            int total_size = left_subtree_size + right_subtree_size + 1;
            root->size = total_size;
        }
        return root;
    }

    void insertValueInBST(int x) {
        root = insert(root, x);
    }

    void delValueInBST(int x) {
        root = del(root, x);
    }

    int findKmax(int k) {
        Node* temp;
        temp = k_maximum(root, k);
        return temp->key;
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    BST bst;

    for (int i = 0; i < n; i++) {
        int temp_action;
        std::cin >> temp_action;

        if (temp_action == 1) {
            int k;
            std::cin >> k;
            bst.insertValueInBST(k);
        } else if (temp_action == 0) {
            int k;
            std::cin >> k;
            int k_max = bst.findKmax(k);
            std::cout << k_max << '\n';
        } else if (temp_action == -1) {
            int k;
            std::cin >> k;
            bst.delValueInBST(k);
        }
    }

    return 0;
}
