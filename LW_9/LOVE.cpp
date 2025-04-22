#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int n, s, f;
    cin >> n >> s >> f;
    s--;
    f--;
    
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    vector<vector<pair<int, int>>> adj(n);
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u != v && matrix[u][v] != -1) {
                adj[u].emplace_back(v, matrix[u][v]);
            }
        }
    }
    
    const long long INF = 1e18;
    vector<long long> dist(n, INF);
    dist[s] = 0;
    vector<bool> visited(n, false);
    
    for (int i = 0; i < n; ++i) {
        int u = -1;
        long long min_dist = INF;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        if (u == -1 || u == f) break;
        visited[u] = true;
        
        for (auto [v, w] : adj[u]) {
            if (!visited[v] && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    cout << (dist[f] < INF ? dist[f] : -1) << endl;
    return 0;
}