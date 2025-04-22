#include <iostream>
#include <vector>
#include <string>

class MinHeap {
private:
    std::vector<int> heap;

    void bubbleUp(int idx) {
        while (idx > 0 && heap[idx] < heap[(idx - 1) / 2]) {
            std::swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void bubbleDown(int idx) {
        while (true) {
            int leftChildIdx = 2 * idx + 1;
            int rightChildIdx = 2 * idx + 2;
            int smallestIdx = idx;

            if (leftChildIdx < heap.size() && heap[leftChildIdx] < heap[smallestIdx]) {
                smallestIdx = leftChildIdx;
            }
            if (rightChildIdx < heap.size() && heap[rightChildIdx] < heap[smallestIdx]) {
                smallestIdx = rightChildIdx;
            }
            if (heap[idx] <= heap[smallestIdx]) {
                break;
            }
            std::swap(heap[idx], heap[smallestIdx]);
            idx = smallestIdx;
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    int popMin() {
        int minElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        bubbleDown(0);
        return minElement;
    }

    bool isEmpty() const {
        return heap.empty();
    }

    void buildHeap() {
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            bubbleDown(i);
        }
    }

    void merge(const MinHeap &a, const MinHeap &b) {
        heap.insert(heap.end(), a.heap.begin(), a.heap.end());
        heap.insert(heap.end(), b.heap.begin(), b.heap.end());
        buildHeap();
    }

    void decreaseKey(int oldValue, int newValue) {
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i] == oldValue) {
                heap[i] = newValue;
                bubbleUp(i);
                break;
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<MinHeap> heaps;

    std::string command;
    while (std::cin >> command) {
        if (command == "create") {
            heaps.emplace_back();
        } else if (command == "insert") {
            int k, x;
            std::cin >> k >> x;
            if (k < heaps.size()) {
                heaps[k].insert(x);
            }
        } else if (command == "extract-min") {
            int k;
            std::cin >> k;
            if (!heaps[k].isEmpty()) {
                std::cout << heaps[k].popMin() << "\n";
            } else {
                std::cout << "*" << "\n";
            }
        } else if (command == "merge") {
            int k, m;
            std::cin >> k >> m;
            MinHeap newHeap;
            newHeap.merge(heaps[k], heaps[m]);
            heaps.push_back(newHeap);
        } else if (command == "decrease-key") {
            int k, x, y;
            std::cin >> k >> x >> y;
            heaps[k].decreaseKey(x, y);
        }
    }

    return 0;
}