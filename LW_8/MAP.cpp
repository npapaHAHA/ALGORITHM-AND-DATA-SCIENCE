#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int m, k;
    cin >> m >> k;


    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); 
    }

    
    vector<int> distance(n + 1, -1); 
    queue<int> q;

    
    q.push(1);
    distance[1] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : graph[v]) {
            if (distance[u] == -1) { 
                distance[u] = distance[v] + 1;
                q.push(u);
            }
        }
    }

    
    vector<int> result;
    for (int i = 1; i <= n; ++i) {
        if (distance[i] == k) {
            result.push_back(i);
        }
    }

    
    if (result.empty()) {
        cout << "NO";
    } else {
        for (int island : result) {
            cout << island << "\n";
        }
    }

    return 0;
}