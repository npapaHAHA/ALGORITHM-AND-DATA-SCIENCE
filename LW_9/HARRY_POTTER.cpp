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
    int s, f;
    cin >> s >> f;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int b, e, w;
        cin >> b >> e >> w;
        adj[b].emplace_back(e, w);
        adj[e].emplace_back(b, w);
    }
    
    vector<int> dist(n + 1, INT_MAX);
    dist[s] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, s);
    
    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();
        if (current_dist > dist[u]) continue;
        for (const auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    
    cout << (dist[f] == INT_MAX ? -1 : dist[f]) << '\n';
    
    return 0;
}