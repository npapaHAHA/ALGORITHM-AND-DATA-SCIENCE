#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int days[n], summadays = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> days[i];
        summadays += days[i];
    }

    int best_day = -1;
    int before_days = 0, after_days = summadays - days[0];

    if (n <= 4)
    {
        cout << 0;
        return 0;
    } else
    {
        for (int i = 1; i < n; i++)
        {
            before_days += days[i-1];
            after_days -= days[i];

            if (before_days == after_days)
            {
                best_day = i;
                break;
            }
        }
    }
    cout << best_day;
}