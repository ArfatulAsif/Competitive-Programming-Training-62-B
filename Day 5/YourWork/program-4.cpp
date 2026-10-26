#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<long long> > a(n + 1, vector<long long>(m + 1, 0));
    vector<vector<long long> > pref(n + 1, vector<long long>(m + 1, 0));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            pref[i][j] = a[i][j] 
                       + pref[i - 1][j] 
                       + pref[i][j - 1] 
                       - pref[i - 1][j - 1];
        }
    }

    int q;
    cin >> q;
    while(q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        long long subgrid_sum = pref[r2][c2] 
                              - pref[r1 - 1][c2] 
                              - pref[r2][c1 - 1] 
                              + pref[r1 - 1][c1 - 1];

        cout << "Subgrid sum = " << subgrid_sum << endl;
    }

    return 0;
}
