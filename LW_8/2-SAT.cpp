#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

void AddEdge(int a, int b, vector<vector<int>>& graph, vector<vector<int>>& inversed) {
    graph[a].push_back(b);
    inversed[b].push_back(a);
}

void DFS(int v, vector<vector<int>>& inversed, vector<int>& visited, stack<int>& sorted) {
    visited[v] = true;
    for (const auto& it : inversed[v]) {
        if (!visited[it]) {
            DFS(it, inversed, visited, sorted);
        }
    }
    sorted.push(v);
}

void DFS_2(int v, int component, vector<vector<int>>& graph, vector<int>& visited) {
    visited[v] = component;
    for (const auto& it : graph[v]) {
        if (!visited[it]) {
            DFS_2(it, component, graph, visited);
        }
    }
}

void Order(vector<vector<int>>& graph, vector<vector<int>>& inversed, vector<int>& visited, stack<int>& sorted) {
    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            DFS(i, inversed, visited, sorted);
        }
    }
}

vector<int> Kosaraju(vector<vector<int>>& graph, vector<vector<int>>& inversed) {
    vector<int> visited(graph.size(), false);
    stack<int> sorted;

    Order(graph, inversed, visited, sorted);
    visited.assign(graph.size(), false);

    vector<int> scc;
    scc.assign(graph.size(), -1);
    int label = 0;

    while (!sorted.empty()) {
        if (!visited[sorted.top()]) {
            DFS_2(sorted.top(), ++label, graph, visited);
        }
        sorted.pop();
    }
    return visited;
}

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();

    vector<vector<int>> graph;
    vector<vector<int>> inversed;
    graph.assign(n * 2, {});
    inversed.assign(n * 2, {});

    vector<string> clauses;
    string input;

    for (int i = 0; i < m; ++i) {
        getline(cin, input);
        clauses.push_back(input);
    }

    for (int i = 0; i < m; ++i) {
        string clause = clauses[i];

        if (clause[0] == '!') {
            int number = stoi(clause.substr(1, clause.size()));
            AddEdge(number - 1, number - 1 + n, graph, inversed);
        }
        else if (clause.find(' ') != string::npos) {
            int pos = clause.find(' ');

            int a = stoi(clause.substr(0, pos));
            string sign = clause.substr(pos + 1, clause.find(' ', pos + 1) - (pos + 1));
            int pos2 = clause.find(' ', pos + 1);
            int b = stoi(clause.substr(pos2, clause.size() - pos2));

            --a;
            --b;

            if (sign == "||") {
                AddEdge(a + n, b, graph, inversed);
                AddEdge(b + n, a, graph, inversed);
            }
            else if (sign == "&") {
                AddEdge(a + n, a, graph, inversed);
                AddEdge(b + n, b, graph, inversed);
            }
            else if (sign == "->") {
                AddEdge(a, b, graph, inversed);
                AddEdge(b + n, a + n, graph, inversed);
            }
            else if (sign == "^") {
                AddEdge(a, b + n, graph, inversed);
                AddEdge(a + n, b, graph, inversed);
                AddEdge(b, a + n, graph, inversed);
                AddEdge(b + n, a, graph, inversed);
            }
        }
    }

    vector<int> res = Kosaraju(graph, inversed);

    for (int i = 0; i < n; ++i) {
        if (res[i] == res[i + n]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";

    return 0;
}
