#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s;
    cin >> n >> m >> s;
    
    vector<vector<pair<int, long long>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        adj[a].emplace_back(b, w);
    }
    
    const long long INF = LLONG_MAX / 2;
    vector<long long> dist(n + 1, INF);
    vector<bool> reachable(n + 1, false);
    vector<bool> in_cycle(n + 1, false);
    
    
    queue<int> q;
    q.push(s);
    reachable[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &[v, w] : adj[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }
    
 
    dist[s] = 0;
    bool updated = true;
    for (int i = 0; i < n - 1 && updated; ++i) {
        updated = false;
        for (int u = 1; u <= n; ++u) {
            if (dist[u] == INF) continue;
            for (auto &[v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
        }
    }
    
  
    for (int i = 0; i < n; ++i) {
        for (int u = 1; u <= n; ++u) {
            if (dist[u] == INF) continue;
            for (auto &[v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    in_cycle[u] = true;
                    in_cycle[v] = true;
                }
            }
        }
    }
    
    vector<bool> visited_cycle(n + 1, false);
    for (int u = 1; u <= n; ++u) {
        if (in_cycle[u] && !visited_cycle[u]) {
            q.push(u);
            visited_cycle[u] = true;
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (auto &[v, w] : adj[node]) {
                    if (!visited_cycle[v]) {
                        visited_cycle[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    

    for (int u = 1; u <= n; ++u) {
        if (!reachable[u]) {
            cout << "*\n";
        } else if (visited_cycle[u]) {
            cout << "-\n";
        } else {
            cout << dist[u] << "\n";
        }
    }
    
    return 0;
}