#include <bits/stdc++.h>
using namespace std;

struct Passage {
    int room;
    int minH;
    int maxH;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    if (n == 1) {
        cout << 1000000 << "\n";
        return 0;
    }

    vector<pair<int, int>> connections(m);
    for (int i = 0; i < m; ++i) {
        cin >> connections[i].first >> connections[i].second;
    }

    vector<pair<int, int>> limits(m);
    vector<int> candidates;
    for (int i = 0; i < m; ++i) {
        cin >> limits[i].first >> limits[i].second;
        candidates.push_back(limits[i].first);
    }

    vector<vector<Passage>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u = connections[i].first, v = connections[i].second;
        int l = limits[i].first, r = limits[i].second;
        graph[u].push_back({v, l, r});
        graph[v].push_back({u, l, r});
    }

    if (m == 0) {
        cout << -1 << "\n";
        return 0;
    }

    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

    int result = 0;

    for (int minHeight : candidates) {
        const int MAX_HEIGHT = 1000000;
        vector<int> bestHeight(n + 1, -1);
        bestHeight[1] = MAX_HEIGHT;

        priority_queue<pair<int, int>> pq;
        pq.push({bestHeight[1], 1});

        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();

            int bottleneck = current.first;
            int room = current.second;

            if (bottleneck != bestHeight[room]) continue;

            if (room == n) break;

            for (auto &passage : graph[room]) {
                if (passage.minH > minHeight) continue;
                int newBottleneck = min(bottleneck, passage.maxH);

                if (newBottleneck > bestHeight[passage.room]) {
                    bestHeight[passage.room] = newBottleneck;
                    pq.push({newBottleneck, passage.room});
                }
            }
        }

        if (bestHeight[n] >= minHeight && bestHeight[n] != -1) {
            int count = bestHeight[n] - minHeight + 1;
            result = max(result, count);
        }
    }

    if (result == 0) {
        cout << -1 << "\n";
    } else {
        cout << result << "\n";
    }

    return 0;
}