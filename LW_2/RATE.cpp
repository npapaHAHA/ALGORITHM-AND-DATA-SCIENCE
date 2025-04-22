#include <iostream>

long k = 0;

void SortMerge(int a[], int left, int right, int mid)
{
    int l = 0, r = 0;
    int res[right - left];

    while ((left + l < mid) && (mid + r < right))
    {
        if (a[left + l] <= a[mid + r])
        {
            res[l + r] = a[left + l];
            l++;
        } else
        {
            res[l + r] = a[mid + r];
            r++;
            k += mid - left - l;
        }
    }
    while (left + l < mid)
    {
        res[l + r] = a[left + l];
        l++;
    }
    while (mid + r < right)
    {
        res[l + r] = a[mid + r];
        r++;
    }
    for (int i = 0; i < l + r; i++)
    {
        a[left + i] = res[i];
    }
}

void MergeSortRecurring(int a[], int left, int right)
{
    if (right - left > 1)
    {
        int mid = (left + right) / 2;

        MergeSortRecurring(a, left, mid);
        MergeSortRecurring(a, mid, right);

        SortMerge(a, left, right, mid);
    }
}

int main()
{
    int n;
    std::cin >> n;

    int a[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    MergeSortRecurring(a, 0, n);

    std::cout << k;
}