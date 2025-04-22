#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<long long> dp(m + 1, 0);
    
    for(int i = 0; i < n; ++i){
        int k;
        cin >> k;
        vector<long long> row(k);
        for(auto &x : row) cin >> x;
        
        vector<long long> prefix(k + 1, 0);
        for(int l = 0; l < k; ++l){
            prefix[l + 1] = prefix[l] + row[l];
        }
        
        vector<long long> suffix(k + 1, 0);
        for(int r = k - 1; r >= 0; --r){
            suffix[k - r] = suffix[k - r - 1] + row[r];
        }
        
        int max_t = min(k, m);
        vector<long long> best(max_t + 1, 0);
        for(int t = 1; t <= max_t; ++t){
            for(int l = 0; l <= t; ++l){
                int r = t - l;
                if(l + r > k) continue;
                long long current = prefix[l] + suffix[r];
                if(current > best[t]){
                    best[t] = current;
                }
            }
        }
        
        for(int j = m; j >= 0; --j){
            for(int t = 1; t <= min((int)best.size() - 1, j); ++t){
                dp[j] = max(dp[j], dp[j - t] + best[t]);
            }
        }
    }
    
    cout << dp[m] << "\n";
    
    return 0;
}
