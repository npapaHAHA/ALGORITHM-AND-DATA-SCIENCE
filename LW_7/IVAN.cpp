#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

vector<pair<char, unsigned long long>> parseRLE(const string& s) {
    vector<pair<char, unsigned long long>> res;
    int i = 0;
    while (i < s.length()) {
        char c = s[i];
        i += 1;
        string count_str;
        while (i < s.length() && isdigit(s[i])) {
            count_str += s[i];
            i += 1;
        }
        unsigned long long count = stoull(count_str);
        res.push_back(make_pair(c, count));
    }
    return res;
}

unsigned long long computeDiff(const vector<pair<char, unsigned long long>>& list1, const vector<pair<char, unsigned long long>>& list2) {
    vector<pair<char, unsigned long long>> copy1 = list1;
    vector<pair<char, unsigned long long>> copy2 = list2;
    
    unsigned long long len1 = 0, len2 = 0;
    for (auto p : list1) len1 += p.second;
    for (auto p : list2) len2 += p.second;
    
    unsigned long long min_len = min(len1, len2);
    unsigned long long diff = 0;
    
    int i = 0, j = 0;
    unsigned long long pos = 0;
    while (pos < min_len) {
        char c1 = copy1[i].first;
        unsigned long long cnt1 = copy1[i].second;
        char c2 = copy2[j].first;
        unsigned long long cnt2 = copy2[j].second;
        
        unsigned long long step = min(cnt1, cnt2);
        if (c1 != c2) {
            diff += step;
        }
        
        pos += step;
        copy1[i].second -= step;
        if (copy1[i].second == 0) i++;
        copy2[j].second -= step;
        if (copy2[j].second == 0) j++;
    }
    
    return diff;
}

int main() {
    unsigned long long m, n, k;
    cin >> m >> n >> k;
    cin.ignore(); 
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    
    vector<pair<char, unsigned long long>> list1 = parseRLE(s1);
    vector<pair<char, unsigned long long>> list2 = parseRLE(s2);
    
    unsigned long long diff = computeDiff(list1, list2);
    
    if (diff <= k) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}