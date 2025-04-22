#include <iostream>
#include <vector>
#include <queue>

using namespace std;


struct Node {
    long long value;
    Node* left;
    Node* right;


    Node(long long val) : value(val), left(nullptr), right(nullptr) {}
};


class BinarySearchTree {
private:
    Node* root;

public:

    BinarySearchTree() : root(nullptr) {}

    void insert(long long value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        while (true) {
            if (value <= current->value) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                } else {
                    current = current->left;
                }
            } else {
                // Вставляем в правое поддерево (включая равные значения)
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }


    vector<long long> getRightmostValues() const {
        vector<long long> rightmostValues;
        if (root == nullptr) {
            return rightmostValues;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            long long levelSize = q.size();
            long long rightmost = 0;
            bool found = false;

            for (int i = 0; i < levelSize; ++i) {
                Node* current = q.front();
                q.pop();


                if (current->right != nullptr) {
                    q.push(current->right);
                }
                if (current->left != nullptr) {
                    q.push(current->left);
                }


                if (!found) {
                    rightmost = current->value;
                    found = true;
                }
            }
            rightmostValues.push_back(rightmost);
        }

        return rightmostValues;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    vector<long long> branchLengths(n);
    for (int i = 0; i < n; ++i) {
        cin >> branchLengths[i];
    }

    BinarySearchTree bst;
    for (const long long& length : branchLengths) {
        bst.insert(length);
    }

    vector<long long> rightmost = bst.getRightmostValues();


    if (!rightmost.empty()) {
        cout << rightmost[0];
        for (size_t i = 1; i < rightmost.size(); ++i) {
            cout << ' ' << rightmost[i];
        }
    }
    cout << '\n';

    return 0;
}
