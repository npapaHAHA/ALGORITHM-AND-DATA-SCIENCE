#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> graph;
vector<bool> visited;
void dfs(int v, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs(u, component);
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

    int strongly_connected_components = 0;

    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            vector<int> component;
            dfs(i, component);

            
            bool is_strongly_connected = true;
            for (int v : component) {
                if (graph[v].empty()) { 
                    is_strongly_connected = false;
                    break;
                }
            }

            if (is_strongly_connected || component.size() == 1) {
                strongly_connected_components++;
            }
        }
    }

    cout << strongly_connected_components;

    return 0;
}