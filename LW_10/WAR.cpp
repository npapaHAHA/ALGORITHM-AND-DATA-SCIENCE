#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> p;

int dsu_get(int v) {
    if (v == p[v]) return v;
    return p[v] = dsu_get(p[v]);
}

void dsu_unite(int a, int b) {
    a = dsu_get(a);
    b = dsu_get(b);
    if (rand() & 1) swap(a, b);
    if (a != b) p[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, pair<int, int>>> edges(m);
    for (auto& edge : edges) {
        int u, v, w;
        cin >> u >> v >> w;
        edge = make_pair(w, make_pair(u, v));
    }
    
    sort(edges.begin(), edges.end());
    
    p.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    
    int total_cost = 0;
    for (const auto& edge : edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if (dsu_get(u) != dsu_get(v)) {
            dsu_unite(u, v);
            total_cost += w;
        }
    }
    
    cout << total_cost << endl;
    return 0;
}