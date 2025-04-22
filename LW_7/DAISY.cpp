#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    
    vector<vector<long long>> flowers(n, vector<long long>(m));
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < m; ++j) {
            cin >> flowers[i][j];
        }
    }
    
    vector<vector<long long>> dp_masha(n, vector<long long>(m, 0));
    dp_masha[0][0] = flowers[0][0];
    
    for (long long i = 1; i < n; ++i) dp_masha[i][0] = dp_masha[i-1][0] + flowers[i][0];
    for (long long j = 1; j < m; ++j) dp_masha[0][j] = dp_masha[0][j-1] + flowers[0][j];
    
    for (long long i = 1; i < n; ++i) {
        for (long long j = 1; j < m; ++j) {
            dp_masha[i][j] = flowers[i][j] + max(dp_masha[i-1][j], dp_masha[i][j-1]);
        }
    }

    vector<vector<long long>> dp_dasha(n, vector<long long>(m, 0));
    dp_dasha[n-1][m-1] = flowers[n-1][m-1];
    
    for (int i = n-2; i >= 0; --i) dp_dasha[i][m-1] = dp_dasha[i+1][m-1] + flowers[i][m-1];
    for (int j = m-2; j >= 0; --j) dp_dasha[n-1][j] = dp_dasha[n-1][j+1] + flowers[n-1][j];
    
    for (int i = n-2; i >= 0; --i) {
        for (int j = m-2; j >= 0; --j) {
            dp_dasha[i][j] = flowers[i][j] + max(dp_dasha[i+1][j], dp_dasha[i][j+1]);
        }
    }

    int q;
    cin >> q;
    
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        
        if (x >= 0 && x < n && y >= 0 && y < m) {
            cout << dp_masha[x][y] + dp_dasha[x][y] - flowers[x][y] << endl;
        } else {
            cout << 0 << endl;
        }
    }
    
    return 0;
}
