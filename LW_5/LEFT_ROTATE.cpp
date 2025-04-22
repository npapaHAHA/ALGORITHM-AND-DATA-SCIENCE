#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int value;
    int height_left = -1;
    int height_right = -1;
    int left_child;
    int right_child;
    int balance_factor;

    Node(int value, int left_child, int right_child)
        : value(value), left_child(left_child), right_child(right_child) {
    }
};

int computeHeights(Node **nodes, int index) {
    if (nodes[index]->height_right == -1) {
        if (nodes[index]->right_child != 0) {
            nodes[index]->height_right = computeHeights(nodes, nodes[index]->right_child - 1);
        }
    }
    if (nodes[index]->height_left == -1) {
        if (nodes[index]->left_child != 0) {
            nodes[index]->height_left = computeHeights(nodes, nodes[index]->left_child - 1);
        }
    }
    nodes[index]->balance_factor = nodes[index]->height_right - nodes[index]->height_left;
    return std::max(nodes[index]->height_left, nodes[index]->height_right) + 1;
}

int performSmallLeftRotation(Node **nodes, int root_index) {
    int right_child_index = nodes[root_index]->right_child - 1;
    int temp_left = nodes[right_child_index]->left_child - 1;

    nodes[right_child_index]->left_child = root_index + 1;
    nodes[root_index]->right_child = temp_left + 1;

    return right_child_index;
}

int performBigLeftRotation(Node **nodes, int root_index) {
    int right_child_index = nodes[root_index]->right_child - 1;
    int right_left_child_index = nodes[right_child_index]->left_child - 1;

    int left_subtree = nodes[right_left_child_index]->left_child - 1;
    int right_subtree = nodes[right_left_child_index]->right_child - 1;

    nodes[right_left_child_index]->left_child = root_index + 1;
    nodes[right_left_child_index]->right_child = right_child_index + 1;
    nodes[root_index]->right_child = left_subtree + 1;
    nodes[right_child_index]->left_child = right_subtree + 1;

    return right_left_child_index;
}

int main() {
    int num_nodes;
    std::cin >> num_nodes;

    Node **tree_nodes = new Node *[num_nodes];

    for (int i = 0; i < num_nodes; ++i) {
        int value, left, right;
        std::cin >> value >> left >> right;
        tree_nodes[i] = new Node(value, left, right);
    }

    for (int i = 0; i < num_nodes; ++i) {
        computeHeights(tree_nodes, i);
    }

    int unbalanced_index = -1;
    for (int i = 0; i < num_nodes; ++i) {
        if (tree_nodes[i]->balance_factor == 2) {
            unbalanced_index = i;
            break;
        }
    }

    int new_root_index;
    if (tree_nodes[tree_nodes[unbalanced_index]->right_child - 1]->balance_factor == -1) {
        new_root_index = performBigLeftRotation(tree_nodes, unbalanced_index);
    } else {
        new_root_index = performSmallLeftRotation(tree_nodes, unbalanced_index);
    }

    std::queue<int> level_order;
    int index_counter = 1;
    level_order.push(new_root_index);
    std::cout << num_nodes << '\n';

    while (!level_order.empty()) {
        int current_index = level_order.front();
        level_order.pop();

        std::cout << tree_nodes[current_index]->value << " ";

        if (tree_nodes[current_index]->left_child != 0) {
            level_order.push(tree_nodes[current_index]->left_child - 1);
            std::cout << ++index_counter << " ";
        } else {
            std::cout << 0 << " ";
        }

        if (tree_nodes[current_index]->right_child != 0) {
            level_order.push(tree_nodes[current_index]->right_child - 1);
            std::cout << ++index_counter << '\n';
        } else {
            std::cout << 0 << '\n';
        }
    }

    return 0;
}
