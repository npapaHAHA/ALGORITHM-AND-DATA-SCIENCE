#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

double mysqrt(long long x) {
    if (x == 0) return 0.0;
    double low = 0, high = x;
    double mid;
    for (int i = 0; i < 100; ++i) {
        mid = (low + high) / 2;
        if (mid * mid > x)
            high = mid;
        else
            low = mid;
    }
    return (low + high) / 2;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> cities(n);
    for (auto& c : cities) cin >> c.first >> c.second;

    if (n == 1) {
        cout << fixed << setprecision(5) << 0.0 << endl;
        return 0;
    }

    vector<bool> used(n, false);
    vector<long long> min_e(n, LLONG_MAX);
    vector<int> sel_e(n, -1);
    min_e[0] = 0;

    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        }
        if (min_e[v] == LLONG_MAX) {
            cout << fixed << setprecision(5) << -1 << endl;
            return 0;
        }

        used[v] = true;

        for (int to = 0; to < n; ++to) {
            if (used[to]) continue;
            int dx = cities[v].first - cities[to].first;
            int dy = cities[v].second - cities[to].second;
            long long dist_sq = static_cast<long long>(dx)*dx + dy*dy;
            if (dist_sq < min_e[to]) {
                min_e[to] = dist_sq;
                sel_e[to] = v;
            }
        }
    }

    double total = 0.0;
    for (int i = 1; i < n; ++i) {
        total += mysqrt(min_e[i]);
    }

    cout << fixed << setprecision(5) << total << endl;
    return 0;
}