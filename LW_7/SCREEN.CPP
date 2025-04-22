#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    
    vector<int> prev_row(M + 1, 0);
    vector<int> curr_row(M + 1, 0);
    
    int max_size = 0;
    int position_i = 0, position_j = 0;
    
    for (int i = 1; i <= N; ++i) {
        string row;
        cin >> row;
        
        for (int j = 1; j <= M; ++j) {
            if (row[j - 1] == '5') {
                curr_row[j] = min(prev_row[j], min(curr_row[j - 1], prev_row[j - 1])) + 1;
            } else {
                curr_row[j] = 0;
            }
            
            if (curr_row[j] > max_size) {
                max_size = curr_row[j];
                position_i = i - max_size + 1;
                position_j = j - max_size + 1;
            } else if (curr_row[j] == max_size) {
                int current_top_i = i - curr_row[j] + 1;
                int current_top_j = j - curr_row[j] + 1;
                if (current_top_i > position_i || (current_top_i == position_i && current_top_j > position_j)) {
                    position_i = current_top_i;
                    position_j = current_top_j;
                }
            }
        }
        
        prev_row = curr_row;
    }
    
    cout << max_size << " " << position_i << " " << position_j << endl;
    
    return 0;
}