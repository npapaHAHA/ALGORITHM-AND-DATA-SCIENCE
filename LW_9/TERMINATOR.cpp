#include <iostream>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    int count = 0;
    for (int i = 1; i < N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (count >= M) break;
            cout << i << " " << j << " " << (j - i - 1) << endl;
            count++;
        }
    }
    return 0;
}