#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }

    for (int i = 2; i < n; i++)
    {
        int sort = arr[i];
        arr[i] = arr[i/2];
        arr[i/2] = sort;
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
}