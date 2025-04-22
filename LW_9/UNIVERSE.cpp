#include <iostream>
#include <vector>
#include <limits>

const int INF = std::numeric_limits<int>::max();

void compute_diameter_and_radius(int n, const std::vector<std::vector<int>>& graph) {
    int empire_diameter = 0, empire_radius = INF;
    std::vector<int> eccentricities(n + 1, 0);

    for (int start_system = 1; start_system <= n; start_system++) {
        std::vector<int> distances(n + 1, INF);
        std::vector<bool> visited(n + 1, false);
        distances[start_system] = 0;

        for (int i = 1; i <= n; i++) {
            int closest_node = -1;

            for (int j = 1; j <= n; j++) {
                if (!visited[j] && (closest_node == -1 || distances[j] < distances[closest_node])) {
                    closest_node = j;
                }
            }

            if (closest_node == -1 || distances[closest_node] == INF) break;
            visited[closest_node] = true;

            for (int neighbor = 1; neighbor <= n; neighbor++) {
                if (graph[closest_node][neighbor] != INF && distances[closest_node] + graph[closest_node][neighbor] < distances[neighbor]) {
                    distances[neighbor] = distances[closest_node] + graph[closest_node][neighbor];
                }
            }
        }

        int max_distance = 0;
        for (int i = 1; i <= n; i++) {
            if (distances[i] != INF) {
                max_distance = std::max(max_distance, distances[i]);
            }
        }

        eccentricities[start_system] = max_distance;
        empire_diameter = std::max(empire_diameter, max_distance);
        empire_radius = std::min(empire_radius, max_distance);
    }

    std::cout << empire_diameter << "\n" << empire_radius;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int num_systems;
    std::cin >> num_systems;

    std::vector<std::vector<int>> graph(num_systems + 1, std::vector<int>(num_systems + 1, INF));

    for (int i = 1; i <= num_systems; i++) {
        for (int j = 1; j <= num_systems; j++) {
            std::cin >> graph[i][j];
            if (graph[i][j] == -1) graph[i][j] = INF; 
        }
    }

    compute_diameter_and_radius(num_systems, graph);
}
