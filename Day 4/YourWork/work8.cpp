#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<int> v(n);
    long long even_sum = 0;
    long long odd_sum = 0;
    
    for(int i = 0; i < n; i++) {
        cin >> v[i]; // Reading directly into the sized vector
        if(v[i] % 2 == 0) {
            even_sum += v[i];
        } else {
            odd_sum += v[i];
        }
    }
    
    if(even_sum > odd_sum) {
        cout << "EVEN\n";
    } else {
        cout << "ODD\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t; // Read number of test cases
    while(t--) {
        solve(); // Process each test case individually
    }
    return 0;
}
