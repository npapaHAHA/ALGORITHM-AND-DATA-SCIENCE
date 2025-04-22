#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

struct PrimeData {
    long long prime;
    long long additional_value;
    long long frequency;
};

std::vector<PrimeData> sieve(long long max, long long limit) {
    long long* arr = new long long[max + 1];
    for (long long i = 0; i <= max; ++i) {
        arr[i] = i;
    }

    long long prime_count = 0;
    std::vector<PrimeData> primes;

    for (long long num = 2; num <= max; ++num) {
        if (arr[num] != 0) {
            primes.push_back(PrimeData{arr[num], arr[num], 1});
            ++prime_count;
            for (long long mul = num * num; mul <= max; mul += num) {
                arr[mul] = 0;
            }
        }
        if (prime_count >= limit) {
            break;
        }
    }
    return primes;
}

bool check_prime(long long number) {
    for (long long i = 2; i <= std::sqrt(number); ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

class PriorityQueue {
private:
    std::vector<PrimeData> heap;
    long long heap_size = 0;
    long long pop_count = 0;
    std::vector<long long> output;

public:
    PriorityQueue() = default;

    void heapifyUp(long long index) {
        while (index > 0 && heap[index].prime < heap[(index - 1) / 2].prime) {
            std::swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(long long index) {
        while (2 * index + 1 < heap.size()) {
            long long left_child = 2 * index + 1;
            long long right_child = left_child + 1;
            long long smaller_child = left_child;

            if (right_child < heap.size() && heap[left_child].prime > heap[right_child].prime) {
                smaller_child = right_child;
            }

            if (heap[index].prime <= heap[smaller_child].prime) {
                break;
            }

            std::swap(heap[index], heap[smaller_child]);
            index = smaller_child;
        }
    }

    void heapifyDownSpecial(long long index) {
        while (2 * index + 1 < heap.size()) {
            long long left_child = 2 * index + 1;
            long long right_child = left_child + 1;
            long long smaller_child = left_child;

            if (right_child < heap.size() && heap[left_child].additional_value > heap[right_child].additional_value) {
                smaller_child = right_child;
            }

            if (heap[index].additional_value <= heap[smaller_child].additional_value) {
                break;
            }

            std::swap(heap[index], heap[smaller_child]);
            index = smaller_child;
        }
    }

    PriorityQueue(std::vector<PrimeData>& values) {
        heap = values;
        for (long long i = heap.size() - 1; i >= 0; --i) {
            heapifyDown(i);
            ++heap_size;
        }
    }

    void insert(const PrimeData& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
        ++heap_size;
    }

    PrimeData remove() {
        PrimeData root_value = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        heapifyDown(0);
        --heap_size;
        ++pop_count;
        root_value.frequency *= 2; 
        return root_value;
    }

    PrimeData removeSpecial() {
        PrimeData root_value = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();
        heapifyDownSpecial(0);
        --heap_size;
        return root_value;
    }

    long long getSize() const {
        return heap.size();
    }

    long long getPopCount() const {
        return pop_count;
    }

    void generateResults() {
        for (long long i = heap.size() - 1; i >= 0; --i) {
            heapifyDownSpecial(i);
        }
        while (heap_size) {
            PrimeData current = removeSpecial();
            for (int i = 0; i < current.frequency - 1; ++i) {
                output.push_back(current.additional_value);
            }
        }
    }

    void displayResults() const {
        std::cout << output.size() << "\n";
        for (long long num : output) {
            std::cout << num << " ";
        }
    }
};

int main() {
    long long n;
    std::cin >> n;

    std::vector<PrimeData> prime_numbers = sieve(7000000, n);

    PriorityQueue queue(prime_numbers);

    while (queue.getPopCount() != n) {
        PrimeData item = queue.remove();
        item.prime = item.prime * item.prime;
        queue.insert(item);
    }

    queue.generateResults();
    queue.displayResults();

    return 0;
}
