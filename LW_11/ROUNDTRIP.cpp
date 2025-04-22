#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int size) : parent(size, -1) {}
    
    int find(int x) {
        return parent[x] < 0 ? x : parent[x] = find(parent[x]);
    }
    
    bool merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (parent[a] > parent[b]) swap(a, b);
        parent[a] += parent[b];
        parent[b] = a;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodes, edges;
    cin >> nodes >> edges;
    vector<pair<double, double>> points(nodes);
    for (int i = 0; i < nodes; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    struct Connection { int from, to; };
    vector<Connection> edgeList(edges);
    vector<vector<pair<int, int>>> graph(nodes);
    
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        edgeList[i] = {u, v};
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }

    auto calculateTurn = [&](pair<double, double> prevDir, pair<double, double> nextDir) {
        double dotProd = -(prevDir.first * nextDir.first + prevDir.second * nextDir.second);
        dotProd = max(-1.0, min(1.0, dotProd));
        return acos(dotProd);
    };

    DSU dsu(edges);
    double baseSum = 0.0;
    vector<tuple<double, int, int>> possibleFlips;

    for (int vertex = 0; vertex < nodes; ++vertex) {
        int connections = graph[vertex].size();
        if (connections == 0) continue;

        vector<pair<double, double>> directions;
        vector<int> edgeIDs;
        for (auto &neighbor : graph[vertex]) {
            double dx = points[neighbor.first].first - points[vertex].first;
            double dy = points[neighbor.first].second - points[vertex].second;
            double length = hypot(dx, dy);
            directions.emplace_back(dx / length, dy / length);
            edgeIDs.push_back(neighbor.second);
        }

        if (connections == 2) {
            double turn = calculateTurn(directions[0], directions[1]);
            baseSum += turn;
            dsu.merge(edgeIDs[0], edgeIDs[1]);
        } else if (connections == 4) {
            const vector<pair<int, int>> pairs[] = {
                {{0,1}, {2,3}}, {{0,2}, {1,3}}, {{0,3}, {1,2}}
            };
            double costs[3] = {0, 0, 0};
            
            for (int config = 0; config < 3; ++config) {
                for (auto &p : pairs[config]) {
                    costs[config] += calculateTurn(directions[p.first], directions[p.second]);
                }
            }
            
            int bestConfig = min_element(costs, costs + 3) - costs;
            baseSum += costs[bestConfig];
            for (auto &p : pairs[bestConfig]) {
                dsu.merge(edgeIDs[p.first], edgeIDs[p.second]);
            }
            
            for (int config = 0; config < 3; ++config) {
                if (config == bestConfig) continue;
                double delta = costs[config] - costs[bestConfig];
                int compA = dsu.find(edgeIDs[pairs[config][0].first]);
                int compB = dsu.find(edgeIDs[pairs[config][0].second]);
                possibleFlips.emplace_back(delta, compA, compB);
            }
        }
    }

    unordered_set<int> components;
    for (int i = 0; i < edges; ++i) {
        components.insert(dsu.find(i));
    }

    double additionalCost = 0.0;
    int compCount = components.size();
    if (compCount > 1) {
        sort(possibleFlips.begin(), possibleFlips.end());
        DSU tempDSU = dsu;
        for (auto &[delta, a, b] : possibleFlips) {
            if (tempDSU.merge(a, b)) {
                additionalCost += delta;
                compCount--;
                if (compCount == 1) break;
            }
        }
    }

    cout << fixed << setprecision(6) << (baseSum + additionalCost) << endl;
    return 0;
}