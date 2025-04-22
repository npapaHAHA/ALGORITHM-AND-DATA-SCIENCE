#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;

    vector<int> freq(26, 0); 
    for (char c : s) {
        freq[c - 'a']++;
    }

    vector<double> intervals_start(26, 0.0); 
    vector<double> intervals_end(26, 0.0);   
    int total = s.size();

    double current_low = 0.0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            double prob = (double)freq[i] / total; 
            intervals_start[i] = current_low;      
            intervals_end[i] = current_low + prob; 
            current_low += prob;                  
        }
    }

    double low = 0.0, high = 1.0;
    for (char c : s) {
        int idx = c - 'a'; 
        double range = high - low;
        high = low + range * intervals_end[idx];   
        low = low + range * intervals_start[idx]; 
    }

 
    cout << fixed << setprecision(6) << low << endl; 
    return 0;
}
