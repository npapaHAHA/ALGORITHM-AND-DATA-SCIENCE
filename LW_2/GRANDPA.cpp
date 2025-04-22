#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int tapki[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> tapki[i];
    }

    int sort;
    for (int i = 1; i < n; i++)
    {
        int j;
        sort = tapki[i];
        for (j = i-1; j >= 0 && tapki[j] > sort; j--)
        {
            tapki[j + 1] = tapki[j];
        }
        tapki[j+1] = sort;
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << tapki[i] << " ";
    }
}