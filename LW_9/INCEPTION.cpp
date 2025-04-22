#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].emplace_back(b, w);
        rev_adj[b].push_back(a);
    }
    
    vector<bool> reachable_from_start(n + 1, false);
    queue<int> q;
    q.push(1);
    reachable_from_start[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& [v, w] : adj[u]) {
            if (!reachable_from_start[v]) {
                reachable_from_start[v] = true;
                q.push(v);
            }
        }
    }
    if (!reachable_from_start[n]) {
        cout << ":(" << endl;
        return 0;
    }
    
    vector<bool> reachable_to_end(n + 1, false);
    q.push(n);
    reachable_to_end[n] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : rev_adj[u]) {
            if (!reachable_to_end[v]) {
                reachable_to_end[v] = true;
                q.push(v);
            }
        }
    }
    
    vector<long long> max_c(n + 1, LLONG_MIN);
    max_c[1] = 0;
    
    bool updated = true;
    for (int i = 0; i < n - 1 && updated; ++i) {
        updated = false;
        for (int u = 1; u <= n; ++u) {
            if (max_c[u] == LLONG_MIN) continue;
            for (auto& [v, w] : adj[u]) {
                if (max_c[v] < max_c[u] + w) {
                    max_c[v] = max_c[u] + w;
                    updated = true;
                }
            }
        }
    }
    
    vector<long long> prev_max = max_c;
    bool has_infinite = false;
    for (int u = 1; u <= n && !has_infinite; ++u) {
        if (prev_max[u] == LLONG_MIN) continue;
        for (auto& [v, w] : adj[u]) {
            if (prev_max[v] < prev_max[u] + w) {
                if (reachable_from_start[u] && reachable_to_end[v]) {
                    has_infinite = true;
                    break;
                }
            }
        }
    }
    
    if (has_infinite) {
        cout << ":)" << endl;
    } else {
        cout << (max_c[n] == LLONG_MIN ? ":(" : to_string(max_c[n])) << endl;
    }
    
    return 0;
}