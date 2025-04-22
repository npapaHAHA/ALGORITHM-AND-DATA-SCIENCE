#include <iostream>
#include <vector>

const int MOD = 1000000007;
const int MAXN = 10004;
const int MAXK = 1004;

int dp[2][10][MAXK];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    for (int j = 1; j <= 9; ++j) {
        dp[1][j][j % k] = 1;
    }

    for (int i = 2; i <= n; ++i) {
        int cur = i % 2;
        int prev = (i - 1) % 2;

        
        for (int j = 0; j <= 9; ++j) {
            for (int p = 0; p < k; ++p) {
                dp[cur][j][p] = 0;
            }
        }

       
        static int sum_even[MAXK], sum_odd[MAXK];
        for (int p = 0; p < k; ++p) {
            sum_even[p] = 0;
            sum_odd[p] = 0;
        }

        for (int j_prev = 0; j_prev <= 9; ++j_prev) {
            for (int p = 0; p < k; ++p) {
                if (j_prev % 2 == 0) {
                    sum_even[p] = (sum_even[p] + dp[prev][j_prev][p]) % MOD;
                } else {
                    sum_odd[p] = (sum_odd[p] + dp[prev][j_prev][p]) % MOD;
                }
            }
        }

        
        for (int j = 0; j <= 9; ++j) {
            if (j % 2 == 0) {
                
                for (int p_old = 0; p_old < k; ++p_old) {
                    if (sum_odd[p_old] != 0) {
                        int p_new = (int)((1LL * p_old * 10 + j) % k);
                        dp[cur][j][p_new] = (dp[cur][j][p_new] + sum_odd[p_old]) % MOD;
                    }
                }
            } else {
                
                for (int p_old = 0; p_old < k; ++p_old) {
                    if (sum_even[p_old] != 0) {
                        int p_new = (int)((1LL * p_old * 10 + j) % k);
                        dp[cur][j][p_new] = (dp[cur][j][p_new] + sum_even[p_old]) % MOD;
                    }
                }
            }
        }
    }

    int result = 0;
    for (int j = 0; j <= 9; ++j) {
        result = (result + dp[n % 2][j][0]) % MOD;
    }

    std::cout << result << "\n";
    return 0;
}
