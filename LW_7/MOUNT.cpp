#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int longestIncreasingSubsequence(vector<int>& a) {
    int n = a.size();
    vector<int> dp;
    
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);
        if (it == dp.end()) {
            dp.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    
    return dp.size();
}

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    int k = longestIncreasingSubsequence(a);
    cout << k << endl;
    
    return 0;
}