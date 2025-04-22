#include <iostream>

void QuickSort(int a[], int left, int right) {
    int l = left, j = right;
    int mid = (left + right) / 2;
    int bust;
    int essential = a[mid];
    

    while (l <= j) {
        while (a[l] > essential) {
            l++;
        }
        while (a[j] < essential) {
            j--;
        }

        if (l <= j) {
            bust = a[l];
            a[l] = a[j];
            a[j] = bust;
            l++;
            j--;
        }
    }

    if (left < j) {
        QuickSort(a, left, j);
    }
    if (right > l) {
        QuickSort(a, l, right);
    }
}

int main() {
    int n;
    std::cin >> n;

    int sticks[n];
    for (int i = 0; i < n; i++) {
        std::cin >> sticks[i];
    }

    QuickSort(sticks, 0, n - 1);

    long best_palki[n];
    int k = 0;

    for (int i = 0; i < n - 1; i++) {

        if (sticks[i] - sticks[i + 1] < 2) {
            best_palki[k] = sticks[i + 1];
            k++;
            i++;
        }
    }

    long area = 0;
    for (int i = 0; i < k - 1; i += 2) {
        area += best_palki[i] * best_palki[i + 1];
    }

    std::cout << area;
    return 0;
}

