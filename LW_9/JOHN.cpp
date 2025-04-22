#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

struct Edge {
    int from, to;
    double rate, commission;
};

int main() {
    int n, m, s;
    double v;
    cin >> n >> m >> s >> v;

    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        double r_ab, c_ab, r_ba, c_ba;
        cin >> a >> b >> r_ab >> c_ab >> r_ba >> c_ba;
        edges.push_back({a, b, r_ab, c_ab});
        edges.push_back({b, a, r_ba, c_ba});
    }

    vector<double> dist(n + 1, 0.0);
    dist[s] = v;

    for (int i = 0; i < n - 1; ++i) {
        for (const auto& e : edges) {
            double new_amount = (dist[e.from] - e.commission) * e.rate;
            if (new_amount > dist[e.to] + EPS) {
                dist[e.to] = new_amount;
            }
        }
    }

    bool can_increase = false;
    for (const auto& e : edges) {
        double new_amount = (dist[e.from] - e.commission) * e.rate;
        if (new_amount > dist[e.to] + EPS) {
            can_increase = true;
            break;
        }
    }

    cout << (can_increase ? "YES" : "NO") << endl;
    return 0;
}