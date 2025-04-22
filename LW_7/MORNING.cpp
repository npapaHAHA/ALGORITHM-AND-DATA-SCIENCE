#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
   
    vector<string> dict = {""};
    unordered_map<string, int> mp;
    mp[""] = 0;

    int n = (int)s.size();
    int i = 0;

    while (i < n) {
        int len = 0;
        string current;
        while (i + len <= n && mp.find(s.substr(i, len + 1)) != mp.end()) {
            len++;
        }

        if (len == 0) {
            char nextChar = s[i];
            cout << 0 << " " << nextChar << "\n";
            dict.push_back(string(1, nextChar));
            mp[string(1, nextChar)] = dict.size() - 1;
            i++;
        } else {
            string prefix = s.substr(i, len);
            char nextChar = s[i + len];
            int pos = mp[prefix];
            cout << pos << " " << nextChar << "\n";
            dict.push_back(prefix + nextChar);
            mp[prefix + nextChar] = dict.size() - 1;
            i += len + 1;
        }
    }

    return 0;
}
