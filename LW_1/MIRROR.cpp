#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<char> slovo(n);
    for (int i = 0; i < n; i++) {
        cin >> slovo[i];
    }

    if (n <= 1) {
        cout << "NO";
        return 0;
    }

    int l = 0, r = n - 1, k = 0;
    while (l < r) {
        if (slovo[l] != slovo[r]) {
            k++;
            if (k > 1) {
                cout << "NO";
                return 0;
            }
            if (slovo[l] == slovo[r - 1]) {
                r--;
            } else if (slovo[l + 1] == slovo[r]) {
                l++;
            }
        } else {
            l++;
            r--;
        }
    }

    cout << "YES";
    return 0;
}