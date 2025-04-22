#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 4e18; 

struct Edge {
    int to, rev;
    ll cap;
};

struct Dinic {
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    Dinic(int n) : graph(n), level(n), iter(n) {}
    
    void addEdge(int u, int v, ll c) {
        Edge a{v, (int)graph[v].size(), c};
        Edge b{u, (int)graph[u].size(), 0};
        graph[u].push_back(a);
        graph[v].push_back(b);
    }
    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            
            for (auto &e : graph[v]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        
        return level[t] != -1;
    }
    
    ll dfs(int v, int t, ll f) {
        if (f == 0 || v == t) return f;
        
        for (int &i = iter[v]; i < (int)graph[v].size(); ++i) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                ll pushed = dfs(e.to, t, min(f, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    graph[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        
        return 0;
    }
    
    ll maxflow(int s, int t) {
        ll flow = 0, aug;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            while ((aug = dfs(s, t, INF))) {
                flow += aug;
            }
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, P;
    if (!(cin >> N >> M >> P)) return 0;

    vector<ll> V(N);
    vector<vector<int>> need(N);
    for (int i = 0; i < N; ++i) {
        int k;
        cin >> V[i] >> k;
        need[i].resize(k);
        for (int &x : need[i]) { cin >> x; --x; }
    }

    vector<ll> C(M);
    for (ll &c : C) cin >> c;

    struct Pair { int a, b; ll d; };
    vector<Pair> pairs(P);
    for (auto &p : pairs) {
        cin >> p.a >> p.b >> p.d;
        --p.a; --p.b;
    }

    int S = 0;
    int base = 1;
    int idDelivery = base;
    int idModule   = idDelivery + N;
    int idPair     = idModule   + M;
    int T = idPair + P;

    Dinic din(T + 1);

    ll posSum = 0; // W+

    // Добавляем узлы доставки
    for (int i = 0; i < N; ++i) {
        din.addEdge(S, idDelivery + i, V[i]);
        posSum += V[i];
        for (int m : need[i]) {
            din.addEdge(idDelivery + i, idModule + m, INF);
        }
    }

    for (int j = 0; j < M; ++j) {
        din.addEdge(idModule + j, T, C[j]); 
    }

    for (int k = 0; k < P; ++k) {
        auto [a, b, d] = pairs[k];
        ll save = C[a] + C[b] - d;
        if (save <= 0) continue; 
        int node = idPair + k;
        din.addEdge(S, node, save); 
        posSum += save;
        din.addEdge(node, idModule + a, INF);
        din.addEdge(node, idModule + b, INF);
    }

    ll maxFlow = din.maxflow(S, T);
    cout << (posSum - maxFlow) << '\n';
    return 0;
}