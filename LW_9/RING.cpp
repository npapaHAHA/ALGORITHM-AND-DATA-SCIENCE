#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    int s, f;
    cin >> s >> f;
    
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int b, e, w;
        cin >> b >> e >> w;
        graph[b].emplace_back(e, w);
        graph[e].emplace_back(b, w);
    }
    
    vector<int> dist(n + 1, INT_MAX);
    vector<int> prev(n + 1, -1);
    dist[s] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, s);
    
    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (current_dist > dist[u]) continue;
        
        for (const auto& [v, w] : graph[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }
    
    if (dist[f] == INT_MAX) {
        cout << -1 << endl;
    } else {
        vector<int> path;
        int current = f;
        while (current != s) {
            path.push_back(current);
            current = prev[current];
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        cout << dist[f] << endl;
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << (i < path.size() - 1 ? " " : "\n");
        }
    }
    
    return 0;
}