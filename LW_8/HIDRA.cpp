#include <iostream>
#include <vector>

using namespace std;

void DFS(int vertex, vector<vector<int>>& graph, vector<bool>& visited, int& edgeCount) {
    visited[vertex] = true;
    edgeCount += graph[vertex].size();
    for (int neighbor : graph[vertex]) {
        if (!visited[neighbor]) {
            DFS(neighbor, graph, visited, edgeCount);
        }
    }
}

void DFS(int vertex, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[vertex] = true;
    for (int neighbor : graph[vertex]) {
        if (!visited[neighbor]) {
            DFS(neighbor, graph, visited);
        }
    }
}

int CountComponents(vector<vector<int>>& graph) {
    vector<bool> visitedNodes(graph.size(), false);
    int componentCount = 0;
    for (int i = 0; i < graph.size(); ++i) {
        if (!visitedNodes[i]) {
            ++componentCount;
            DFS(i, graph, visitedNodes);
        }
    }
    return componentCount;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    vector<vector<int>> graph(numVertices);
    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int totalEdges = 0;
    DFS(0, graph, visited, totalEdges);

    if ((totalEdges / 2) == numVertices && CountComponents(graph) == 1) {
        cout << "ARCHIMEDES";
    } else {
        cout << "EUCLID";
    }
}
