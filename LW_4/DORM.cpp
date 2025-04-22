#include <iostream>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<long long> rooms;
    int op;
    long long x;

    while (std::cin >> op >> x) {
        if (op == 0) {
            
            rooms.insert(x);
        } else if (op == 1) {
            
            rooms.erase(x);
        } else if (op == 2) {
        
            if (rooms.count(x)) {
                std::cout << "true" << '\n';
            } else {
                std::cout << "false" << '\n';
            }
        } else if (op == 3) {
            
            auto it = rooms.upper_bound(x);
            if (it == rooms.end()) {
                std::cout << "none" << '\n';
            } else {
                std::cout << *it << '\n';
            }
        } else if (op == 4) {
            
            auto it = rooms.lower_bound(x);
            if (it == rooms.begin()) {
                std::cout << "none" << '\n';
            } else {
                it--;
                std::cout << *it << '\n';
            }
        }
    }

    return 0;
}
