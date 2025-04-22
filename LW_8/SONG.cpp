#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> graph, transpose_graph;
vector<bool> visited;
vector<int> order, component_id;
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
    component_id[v] = comp_id;
    for (int u : transpose_graph[v]) {
        if (!visited[u]) {
            dfs2(u, comp_id);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    graph.assign(n + 1, vector<int>());
    transpose_graph.assign(n + 1, vector<int>());


    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        transpose_graph[b].push_back(a); 
    }

    
    visited.assign(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    
    visited.assign(n + 1, false);
    component_id.assign(n + 1, -1);
    int comp_count = 0;
    for (int i = order.size() - 1; i >= 0; --i) {
        int v = order[i];
        if (!visited[v]) {
            dfs2(v, comp_count++);
        }
    }

    
    vector<int> min_house(comp_count, INT32_MAX);
    for (int i = 1; i <= n; ++i) {
        min_house[component_id[i]] = min(min_house[component_id[i]], i);
    }


    set<pair<int, int>> family_edges;
    for (int a = 1; a <= n; ++a) {
        for (int b : graph[a]) {
            int family_a = min_house[component_id[a]];
            int family_b = min_house[component_id[b]];
            if (family_a != family_b) {
                family_edges.emplace(family_a, family_b);
            }
        }
    }


    cout << comp_count << " " << family_edges.size() << "\n";
    for (auto &[a, b] : family_edges) {
        cout << a << " " << b << "\n";
    }

    return 0;
}