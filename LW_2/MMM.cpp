#include <iostream>

void QickSort(int a[], int left, int right, int stop)
{
    int l = left, r = right;
    int mid = (left + right) / 2;
    int bust;
    int essential = a[mid];
    if (left < right)
    {
        while (l <= r)
        {
            while (a[l] > essential)
            {
                l++;
            }
            while (a[r] < essential)
            {
                r--;
            }
            if (l <= r)
            {
                bust = a[l];
                a[l] = a[r];
                a[r] = bust;
                l++;
                r--;
            }
        }

        if (stop <= r)
        {
            QickSort(a, left, r, stop);
        }

        if (l < stop)
        {
            QickSort(a, l, right, stop);
        }
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    
    int A, B, C;
    int c[n];
    std::cin >> A >> B >> C >> c[0] >> c[1];

    for (int i = 2; i < n; i++) {
        c[i] = c[i - 2] * A + c[i - 1] * B + C;
    }

    QickSort(c, 0, n - 1, k);

    int best_rate = 0;
    for (int i = 0; i < k; i++) {
        best_rate ^= c[i];
    }

    std::cout << best_rate;
}