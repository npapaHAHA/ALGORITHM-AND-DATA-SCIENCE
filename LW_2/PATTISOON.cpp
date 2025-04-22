#include <iostream>

int pat(int a, int b, int c) {
    if ((a > b) != (a > c))
        return a;
    else if ((b > a) != (b > c))
        return b;
    else
        return c;
}

void QuickSort(int a[], int left, int right) {
    int i = left, j = right;
    int middle = (left + right) / 2;
    int essential = pat(a[left], a[middle], a[right]);
    int bust;

    while (i <= j) {
        while (a[i] < essential) {
            i++;
        }
        while (a[j] > essential) {
            j--;
        }
        if (i <= j) {
            bust = a[i];
            a[i] = a[j];
            a[j] = bust;
            i++;
            j--;
        }
    }

    if (left < j) {
        QuickSort(a, left, j);
    }

    if (right > i) {
        QuickSort(a, i, right);
    }
}

int main() {
    int n;
    std::cin >> n;

    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    QuickSort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }

    return 0;
}