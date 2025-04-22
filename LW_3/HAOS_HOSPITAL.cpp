#include <iostream>

struct Node {
    int value;
    Node* next;
    Node(int val) : value(val), next(nullptr) {}
};


class Queue {
private:
    Node* head;
    Node* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}


    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
        }
        tail = newNode;
        if (!head) {
            head = newNode;
        }
    }


    int dequeue() {
        if (!head) return -1;
        int removedValue = head->value;
        Node* temp = head;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
        delete temp;
        return removedValue;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;

    Queue queue;
    for (int i = 0; i < n; ++i) {
        char operation;
        std::cin >> operation;

        if (operation == '+') {
            int x;
            std::cin >> x;
            queue.enqueue(x);
        } else if (operation == '-') {
            std::cout << queue.dequeue() << "\n";
        }
    }

    return 0;
}
