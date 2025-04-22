#include <bits/stdc++.h>
using namespace std;

bool breadthFirstSearch(int leftSize, const vector<vector<int>>& edges, const vector<int>& leftPair, const vector<int>& rightPair, vector<int>& levels) {
    queue<int> nodeQueue;
    const int MAX_DIST = 1e9;
    bool foundUnmatched = false;

    for(int node = 0; node < leftSize; ++node) {
        if(leftPair[node] < 0) {
            levels[node] = 0;
            nodeQueue.push(node);
        } else {
            levels[node] = MAX_DIST;
        }
    }

    while(!nodeQueue.empty()) {
        int current = nodeQueue.front();
        nodeQueue.pop();

        for(int neighbor : edges[current]) {
            int pairedNode = rightPair[neighbor];
            if(pairedNode < 0) {
                foundUnmatched = true;
            } else if(levels[pairedNode] == MAX_DIST) {
                levels[pairedNode] = levels[current] + 1;
                nodeQueue.push(pairedNode);
            }
        }
    }
    return foundUnmatched;
}

bool depthFirstSearch(int currentNode, const vector<vector<int>>& edges, vector<int>& leftPair, vector<int>& rightPair, vector<int>& levels) {
    const int MAX_DIST = 1e9;
    for(int neighbor : edges[currentNode]) {
        int pairedNode = rightPair[neighbor];
        if(pairedNode < 0 || (levels[pairedNode] == levels[currentNode] + 1 && depthFirstSearch(pairedNode, edges, leftPair, rightPair, levels))) {
            leftPair[currentNode] = neighbor;
            rightPair[neighbor] = currentNode;
            return true;
        }
    }
    levels[currentNode] = MAX_DIST;
    return false;
}

int findMaxMatching(int leftSize, int rightSize, const vector<vector<int>>& edges, vector<int>& leftPair, vector<int>& rightPair) {
    leftPair.assign(leftSize, -1);
    rightPair.assign(rightSize, -1);
    vector<int> levels(leftSize);
    int totalMatches = 0;

    while(breadthFirstSearch(leftSize, edges, leftPair, rightPair, levels)) {
        for(int node = 0; node < leftSize; ++node) {
            if(leftPair[node] < 0 && depthFirstSearch(node, edges, leftPair, rightPair, levels))
                ++totalMatches;
        }
    }
    return totalMatches;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int leftNodes, rightNodes, edgeCount;
    cin >> leftNodes >> rightNodes >> edgeCount;
    vector<vector<int>> graph(leftNodes);

    for(int i = 0; i < edgeCount; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        graph[u].push_back(v);
    }

    vector<int> leftPair, rightPair;
    findMaxMatching(leftNodes, rightNodes, graph, leftPair, rightPair);

    vector<vector<int>> reverseGraph(rightNodes);
    for(int u = 0; u < leftNodes; ++u)
        for(int v : graph[u])
            reverseGraph[v].push_back(u);

    vector<char> leftVisited(leftNodes, 0), rightVisited(rightNodes, 0);
    queue<int> processingQueue;

    for(int u = 0; u < leftNodes; ++u)
        if(leftPair[u] < 0) {
            leftVisited[u] = 1;
            processingQueue.push(u);
        }

    while(!processingQueue.empty()) {
        int current = processingQueue.front();
        processingQueue.pop();

        for(int v : graph[current]) {
            if(v == leftPair[current] || rightVisited[v]) continue;
            rightVisited[v] = 1;
            int paired = rightPair[v];
            if(paired >= 0 && !leftVisited[paired]) {
                leftVisited[paired] = 1;
                processingQueue.push(paired);
            }
        }
    }

    vector<char> altLeftVisited(leftNodes, 0), altRightVisited(rightNodes, 0);
    for(int v = 0; v < rightNodes; ++v)
        if(rightPair[v] < 0) {
            altRightVisited[v] = 1;
            processingQueue.push(v);
        }

    while(!processingQueue.empty()) {
        int current = processingQueue.front();
        processingQueue.pop();

        for(int u : reverseGraph[current]) {
            if(u == rightPair[current] || altLeftVisited[u]) continue;
            altLeftVisited[u] = 1;
            int paired = leftPair[u];
            if(paired >= 0 && !altRightVisited[paired]) {
                altRightVisited[paired] = 1;
                processingQueue.push(paired);
            }
        }
    }

    string leftResult(leftNodes, 'N'), rightResult(rightNodes, 'N');
    for(int i = 0; i < leftNodes; ++i)
        if(leftVisited[i]) leftResult[i] = 'P';

    for(int j = 0; j < rightNodes; ++j)
        if(altRightVisited[j]) rightResult[j] = 'P';

    cout << leftResult << "\n" << rightResult << "\n";
    return 0;
}