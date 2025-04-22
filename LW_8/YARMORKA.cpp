#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1, vector<int>());
    vector<int> in_degree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        in_degree[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topological_order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topological_order.push_back(u);

        for (auto &v : graph[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    vector<int> titles(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        titles[topological_order[i]] = i + 1;
    }


    for (int i = 1; i <= n; ++i) {
        cout << titles[i] << (i < n ? ' ' : '\n');
    }

    return 0;
}