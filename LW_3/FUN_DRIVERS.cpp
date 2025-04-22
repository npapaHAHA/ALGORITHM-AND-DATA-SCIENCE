#include <iostream>

struct Node {
    long long value;
    Node* next;

    Node(long long x) : value(x), next(nullptr) {}
};

class Stack {
private:
    Node* top; 

public:
    Stack() : top(nullptr) {}
    
    void push(long long x) {
        Node* newNode = new Node(x);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top != nullptr) {
            std::cout << top->value <<'\n';
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    Stack stack;

    for (int i = 0; i < n; ++i) {
        char operation;
        std::cin >> operation;

        if (operation == '+') {
            long long x;
            std::cin >> x;
            stack.push(x);
        } else if (operation == '-') {
            stack.pop();
        }
    }

    return 0;
}