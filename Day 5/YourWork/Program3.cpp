#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    
    vector<vector<int> > pref(n + 1, vector<int>(26, 0));

    for(int i = 1; i <= n; i++) {
        for(int c = 0; c < 26; c++) {
            pref[i][c] = pref[i - 1][c];
        }
        pref[i][s[i - 1] - 'a']++;
    }

    int q;
    cin >> q;
    while(q--) {
        int l, r;
        char target;
        cin >> l >> r >> target;

        int char_idx = target - 'a';
        int count_in_range = pref[r][char_idx] - pref[l - 1][char_idx];

        cout << "Count of '" << target << "' in range [" << l << ", " << r << "] = " << count_in_range << endl;
    }

    return 0;
}
