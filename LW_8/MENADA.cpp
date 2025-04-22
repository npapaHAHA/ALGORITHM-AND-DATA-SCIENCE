#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> graph;         
vector<vector<int>> transpose_graph;  
vector<bool> visited;
vector<int> order;                  
vector<int> component;             


void dfs1(int v) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs1(u);
        }
    }
    order.push_back(v);
}


void dfs2(int v, int comp_id) {
    visited[v] = true;
    component[v] = comp_id;
    for (int u : transpose_graph[v]) {
        if (!visited[u]) {
            dfs2(u, comp_id);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    graph.assign(n + 1, vector<int>());
    transpose_graph.assign(n + 1, vector<int>());

    
    for (int i = 0; i < m; ++i) {
        int start, end;
        cin >> start >> end;
        graph[start].push_back(end);
        transpose_graph[end].push_back(start); 
    }

    
    visited.assign(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    
    visited.assign(n + 1, false);
    component.assign(n + 1, -1);
    int comp_id = 0;
    for (int i = order.size() - 1; i >= 0; --i) {
        int v = order[i];
        if (!visited[v]) {
            dfs2(v, comp_id++);
        }
    }

    
    while (q--) {
        int a, b;
        cin >> a >> b;
        if (component[a] == component[b] && component[a] != -1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}