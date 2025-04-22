#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> graph;
vector<bool> visited;
vector<int> depth; 
bool has_cycle_of_length_at_least_3 = false;


void dfs(int v, int parent) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        } else if (u != parent && depth[v] - depth[u] + 1 >= 3) {

            has_cycle_of_length_at_least_3 = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    
    graph.assign(n + 1, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); 
    }


    visited.assign(n + 1, false);
    depth.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            depth[i] = 1; 
            dfs(i, -1);
        }
    }

    
    if (has_cycle_of_length_at_least_3) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}