#include <bits/stdc++.h>
using namespace std;
const int MAX = 101;
struct Point {
    int x, y, z;
};


bool isValid(int x, int y, int z, vector<vector<vector<bool>>> &occupied) {
    return x >= 0 && x < MAX && y >= 0 && y < MAX && z >= 0 && z < MAX && !occupied[x][y][z];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, E;
    cin >> K >> E;

    
    Point start, end;
    cin >> start.x >> start.y >> start.z;
    cin >> end.x >> end.y >> end.z;

    
    vector<vector<vector<bool>>> occupied(MAX, vector<vector<bool>>(MAX, vector<bool>(MAX, false)));

    
    for (int i = 0; i < K; ++i) {
        int x, y, z, h;
        cin >> x >> y >> z >> h;
        for (int dz = 0; dz < h; ++dz) {
            if (z + dz < MAX) {
                occupied[x][y][z + dz] = true;
            }
        }
    }

    
    vector<vector<vector<int>>> distance(MAX, vector<vector<int>>(MAX, vector<int>(MAX, -1)));
    queue<Point> q;

    
    q.push(start);
    distance[start.x][start.y][start.z] = 0;


    vector<Point> directions = {
        {1, 0, 0}, {-1, 0, 0},
        {0, 1, 0}, {0, -1, 0},
        {0, 0, 1}, {0, 0, -1}
    };

    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        
        if (current.x == end.x && current.y == end.y && current.z == end.z) {
            cout << distance[current.x][current.y][current.z];
            return 0;
        }


        for (auto &dir : directions) {
            int nx = current.x + dir.x;
            int ny = current.y + dir.y;
            int nz = current.z + dir.z;

            
            if (isValid(nx, ny, nz, occupied) && distance[nx][ny][nz] == -1) {
                distance[nx][ny][nz] = distance[current.x][current.y][current.z] + 1;
                q.push({nx, ny, nz});
            }
        }
    }

    
    cout << "-1";

    return 0;
}