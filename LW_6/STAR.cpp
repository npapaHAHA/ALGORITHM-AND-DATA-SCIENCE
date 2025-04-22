#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct MaxHeap {
    vector<int> heap;

    void push(int value) {
        heap.push_back(value);
        sift_up(heap.size() - 1);
    }

    void pop_top() {
        if (heap.empty()) return;
        swap(heap[0], heap.back());
        heap.pop_back();
        if (!heap.empty()) sift_down(0);
    }

    int top() const {
        if (heap.empty()) return 0;
        return heap[0];
    }

    int size() const {
        return heap.size();
    }

private:
    void sift_up(int idx) {
        while (idx > 0 && heap[idx] > heap[(idx - 1) / 2]) {
            swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void sift_down(int idx) {
        while (2 * idx + 1 < heap.size()) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int largest = idx;

            if (left < heap.size() && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < heap.size() && heap[right] > heap[largest]) {
                largest = right;
            }
            if (largest == idx) break;

            swap(heap[idx], heap[largest]);
            idx = largest;
        }
    }
};


struct MinHeap {
    vector<int> heap;

    void push(int value) {
        heap.push_back(value);
        sift_up(heap.size() - 1);
    }

    void pop_top() {
        if (heap.empty()) return;
        swap(heap[0], heap.back());
        heap.pop_back();
        if (!heap.empty()) sift_down(0);
    }

    int top() const {
        if (heap.empty()) return 0;
        return heap[0];
    }

    int size() const {
        return heap.size();
    }

private:
    void sift_up(int idx) {
        while (idx > 0 && heap[idx] < heap[(idx - 1) / 2]) {
            swap(heap[idx], heap[(idx - 1) / 2]);
            idx = (idx - 1) / 2;
        }
    }

    void sift_down(int idx) {
        while (2 * idx + 1 < heap.size()) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int smallest = idx;

            if (left < heap.size() && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < heap.size() && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest == idx) break;

            swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
    }
};


int main() {
    std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);

    int n;
    cin >> n;

    MaxHeap maxHeap;
    MinHeap minHeap;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        if (maxHeap.size() == 0 || x <= maxHeap.top()) {
            maxHeap.push(x);
        } else {
            minHeap.push(x);
        }


        if (maxHeap.size() > minHeap.size() + 1) {
            int value = maxHeap.top();
            maxHeap.pop_top();
            minHeap.push(value);
        } else if (minHeap.size() > maxHeap.size()) {
            int value = minHeap.top();
            minHeap.pop_top();
            maxHeap.push(value);
        }

        if ((maxHeap.size() + minHeap.size()) % 2 == 1) {
            cout << maxHeap.top() << "\n";
        } else {
            long long median = (long long)maxHeap.top() + minHeap.top();
            cout << median / 2 << "\n";
        }
    }

    return 0;
}
