#include <iostream>
#include <vector>
#include <algorithm>

struct ShawarmaMasterFeature {
    long long salary;
    long long release_time;
};

struct FreePriorityQueue {
    std::vector<ShawarmaMasterFeature> data;

    void sift_up(long long index) {
        while (index != 0 && data[index].salary < data[(index - 1) / 2].salary) {
            long long parent_index = (index - 1) / 2;
            std::swap(data[index], data[parent_index]);
            index = parent_index;
        }
    }

    void sift_down(long long index) {
        while (2 * index + 1 < data.size()) {
            long long left_child_index = 2 * index + 1;
            long long right_child_index = 2 * index + 2;
            long long smallest_child_index = index;

            if (left_child_index < data.size() && data[left_child_index].salary < data[index].salary) {
                smallest_child_index = left_child_index;
            }

            if (right_child_index < data.size() && data[right_child_index].salary < data[smallest_child_index].salary) {
                smallest_child_index = right_child_index;
            }

            if (smallest_child_index == index) {
                break;
            }

            std::swap(data[index], data[smallest_child_index]);
            index = smallest_child_index;
        }
    }

    void push(ShawarmaMasterFeature value) {
        data.push_back(value);
        sift_up(data.size() - 1);
    }

    ShawarmaMasterFeature extract_min() {
        ShawarmaMasterFeature min_element = data[0];
        data[0] = data.back();
        data.pop_back();
        sift_down(0);
        return min_element;
    }

    bool is_empty() {
        return data.empty();
    }

    ShawarmaMasterFeature top() {
        return data.empty() ? ShawarmaMasterFeature{0, 0} : data[0];
    }
};

struct BusyPriorityQueue {
    std::vector<ShawarmaMasterFeature> data;

    void sift_up(long long index) {
        while (index != 0 && data[index].release_time < data[(index - 1) / 2].release_time) {
            long long parent_index = (index - 1) / 2;
            std::swap(data[index], data[parent_index]);
            index = parent_index;
        }
    }

    void sift_down(long long index) {
        while (2 * index + 1 < data.size()) {
            long long left_child_index = 2 * index + 1;
            long long right_child_index = 2 * index + 2;
            long long smallest_child_index = index;

            if (left_child_index < data.size() && data[left_child_index].release_time < data[index].release_time) {
                smallest_child_index = left_child_index;
            }

            if (right_child_index < data.size() && data[right_child_index].release_time < data[smallest_child_index].release_time) {
                smallest_child_index = right_child_index;
            }

            if (smallest_child_index == index) {
                break;
            }

            std::swap(data[index], data[smallest_child_index]);
            index = smallest_child_index;
        }
    }

    void push(ShawarmaMasterFeature value) {
        data.push_back(value);
        sift_up(data.size() - 1);
    }

    ShawarmaMasterFeature extract_min() {
        if (data.empty()) {
            return {0, 0};
        }
        ShawarmaMasterFeature min_element = data[0];
        data[0] = data.back();
        data.pop_back();
        sift_down(0);
        return min_element;
    }

    bool is_empty() {
        return data.empty();
    }

    ShawarmaMasterFeature top() {
        return data.empty() ? ShawarmaMasterFeature{0, 0} : data[0];
    }
};

int main() {
    long long n, m;
    std::cin >> n >> m;

    FreePriorityQueue free_masters;
    BusyPriorityQueue busy_masters;

    for (int i = 0; i < n; ++i) {
        long long salary;
        std::cin >> salary;
        free_masters.push({salary, 0});
    }

    long long total_salary = 0;

    for (int i = 0; i < m; ++i) {
        long long order_time, cooking_time;
        std::cin >> order_time >> cooking_time;

        
        while (!busy_masters.is_empty() && busy_masters.top().release_time <= order_time) {
            free_masters.push(busy_masters.extract_min());
        }

        if (!free_masters.is_empty()) {
            ShawarmaMasterFeature best_master = free_masters.extract_min();
            total_salary += best_master.salary * cooking_time;
            best_master.release_time = order_time + cooking_time;
            busy_masters.push(best_master);
        }
    }

    std::cout << total_salary << std::endl;
    return 0;
}
