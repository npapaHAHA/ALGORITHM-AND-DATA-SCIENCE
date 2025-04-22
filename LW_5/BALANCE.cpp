#include <iostream>
#include <vector>

struct Node {
    int val;
    int count_right = -1;
    int count_left = -1;
    int right;
    int left;

    Node(int val, int left, int right) : val{ val }, left { left }, right{ right } {}
};

int travset(Node** arr, int ind) {
    if (arr[ind]->count_right == -1) {
        if (arr[ind]->right != 0) {
            arr[ind]->count_right = travset(arr, arr[ind]->right - 1);
        }
    }
    if (arr[ind]->count_left == -1) {
        if (arr[ind]->left != 0) {
            arr[ind]->count_left = travset(arr, arr[ind]->left - 1);
        }
    }

    return std::max(arr[ind]->count_left, arr[ind]->count_right) + 1;
}

int main() {
    int n; std::cin >> n;
    int key, left, right;
    Node** arr = new Node*[n];
    Node* nd;
    for (int i = 0; i < n; ++i) {
        std::cin >> key >> left >> right;
        nd = new Node(key, left, right);
        arr[i] = nd;
    }

    for (int i = 0; i < n; ++i) {
        travset(arr, i);
    }
    for (int i = 0; i < n; ++i) {
        std::cout << -arr[i]->count_left + arr[i]->count_right << '\n';
    }
    return 0;
}