#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> x(n+1), y(n+1);
    for (int i = 1; i <= n; ++i)
        cin >> x[i] >> y[i];

    vector<long long> c(n+1);
    for (int i = 1; i <= n; ++i)
        cin >> c[i];

    vector<long long> k(n+1);
    for (int i = 1; i <= n; ++i)
        cin >> k[i];

    vector<long long> min_e(n+1, LLONG_MAX);
    vector<int> sel_e(n+1, -1);
    vector<bool> used(n+1, false);

    for (int i = 1; i <= n; ++i) {
        min_e[i] = c[i];
        sel_e[i] = 0;
    }
    min_e[0] = 0; 
    used[0] = true;

    for (int i = 0; i <= n; ++i) {
        int v = -1;
        for (int j = 0; j <= n; ++j) {
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        }
        if (v == -1) break;
        used[v] = true;

        if (v != 0) {
            for (int to = 1; to <= n; ++to) {
                if (used[to]) continue;
                long long cost = (abs(x[v] - x[to]) + abs(y[v] - y[to])) * (k[v] + k[to]);
                if (cost < min_e[to]) {
                    min_e[to] = cost;
                    sel_e[to] = v;
                }
            }
        }
    }

    long long total = 0;
    vector<int> stations;
    vector<pair<int, int>> lines;

    for (int i = 1; i <= n; ++i) {
        total += min_e[i];
        if (sel_e[i] == 0) {
            stations.push_back(i);
        } else if (sel_e[i] != -1) {
            lines.push_back({sel_e[i], i});
        }
    }

    cout << total << "\n";
    cout << stations.size() << "\n";
    for (int s : stations) cout << s << " ";
    cout << "\n" << lines.size() << "\n";
    for (auto [a, b] : lines) cout << a << " " << b << "\n";

    return 0;
}