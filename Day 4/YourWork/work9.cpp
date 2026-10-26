#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string longest_word = "";

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        if (s.size() > longest_word.size()) {
            longest_word = s;
        }
    }

    cout << longest_word << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}