#include <iostream>
void Quicksort(int* a, int* b, int left, int right) {
    int l = left;
    int r = right;
    int mid = a[(left + right)/2];

    while (l <= r) {
        while (a[l] < mid) {
            l++;
        }
        while (a[r] > mid) {
            r--;
        }
        if (l <= r) {
            int sort = a[l];
            int sort2 = b[l];
            a[l] = a[r];
            b[l] = b[r];
            b[r] = sort2;
            a[r] = sort;
            l++;
            r--;
        }
    }
    if (left < r) {
        Quicksort(a, b, left, r);
    }
    if (right > l) {
        Quicksort(a, b, l, right);
    }
}
int main() {
    int n;
    std::cin >> n;
    int a[n];

    int b[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        std::cin >> b[i];
    }
    Quicksort(a, b, 0, n - 1);
    int c2 = b[0];
    int c1 = a[0];
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > c2) {
            sum += (c2 - c1 + 1);
            c1 = a[i];
        }
        if (b[i] > c2) {
            c2 = b[i];
        }
    }
    sum += (c2 - c1 + 1);
    std::cout << sum;

    return 0;
}