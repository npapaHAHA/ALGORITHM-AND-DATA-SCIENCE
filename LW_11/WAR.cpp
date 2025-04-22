#include <bits/stdc++.h>
using namespace std;

struct FlowNetwork {
    struct Link { int dst, rev; long long capacity; };
    vector<vector<Link>> graph;
    vector<int> dist, ptr;
    FlowNetwork(int size) : graph(size), dist(size), ptr(size) {}
    
    void addLink(int from, int to, long long cap) {
        Link forward{to, (int)graph[to].size(), cap};
        Link backward{from, (int)(graph[from].size()), 0};
        graph[from].emplace_back(forward);
        graph[to].emplace_back(backward);
    }
    
    bool bfs(int src, int sink) {
        fill(dist.begin(), dist.end(), -1);
        queue<int> q; q.push(src); dist[src] = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : graph[v]) {
                if (e.capacity > 0 && dist[e.dst] == -1) {
                    dist[e.dst] = dist[v] + 1;
                    q.push(e.dst);
                }
            }
        }
        return dist[sink] != -1;
    }
    
    long long dfs(int v, int sink, long long flow) {
        if (flow == 0 || v == sink) return flow;
        for (int &i = ptr[v]; i < (int)graph[v].size(); ++i) {
            auto &edge = graph[v][i];
            if (edge.capacity > 0 && dist[edge.dst] == dist[v] + 1) {
                long long pushed = dfs(edge.dst, sink, min(flow, edge.capacity));
                if (pushed > 0) {
                    edge.capacity -= pushed;
                    graph[edge.dst][edge.rev].capacity += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    
    long long computeMaxFlow(int src, int sink) {
        const long long INF = 4e18;
        long long totalFlow = 0, delta;
        while (bfs(src, sink)) {
            fill(ptr.begin(), ptr.end(), 0);
            while ((delta = dfs(src, sink, INF))) totalFlow += delta;
        }
        return totalFlow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int teamsCount;
    cin >> teamsCount;
    vector<long long> victories(teamsCount);
    for (auto &v : victories) cin >> v;
    vector<int> remainingGames(teamsCount);
    for (auto &r : remainingGames) cin >> r;
    vector<vector<int>> matchups(teamsCount, vector<int>(teamsCount));
    for (int i = 0; i < teamsCount; ++i)
        for (int j = 0; j < teamsCount; ++j)
            cin >> matchups[i][j];

    long long maxWins = victories[0] + remainingGames[0];
    for (int k = 1; k < teamsCount; ++k)
        if (victories[k] > maxWins) {
            cout << "NO\n";
            return 0;
        }

    vector<pair<int, int>> gameNodes;
    long long totalMatchups = 0;
    for (int i = 1; i < teamsCount; ++i)
        for (int j = i + 1; j < teamsCount; ++j)
            if (matchups[i][j]) {
                gameNodes.emplace_back(i, j);
                totalMatchups += matchups[i][j];
            }

    int source = 0;
    int gameBase = 1;
    int teamBase = gameBase + gameNodes.size();
    int sink = teamBase + (teamsCount - 1);
    FlowNetwork network(sink + 1);

    for (int idx = 0; idx < gameNodes.size(); ++idx) {
        auto [i, j] = gameNodes[idx];
        int node = gameBase + idx;
        int cap = matchups[i][j];
        network.addLink(source, node, cap);
        network.addLink(node, teamBase + (i - 1), 1e18);
        network.addLink(node, teamBase + (j - 1), 1e18);
    }

    for (int k = 1; k < teamsCount; ++k) {
        long long limit = maxWins - victories[k];
        network.addLink(teamBase + (k - 1), sink, limit);
    }

    cout << (network.computeMaxFlow(source, sink) == totalMatchups ? "YES\n" : "NO\n");
}