#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin>>n;
    
    vector<int>v(n);
    long long even_sum=0;
    long long odd_sum=0;
    
    for(int i=0;i<n;i++) {
        cin>>v[i]; 
        if(v[i]%2==0) {
            even_sum+=v[i];
        } else {
            odd_sum+=v[i];
        }
    }
    if(even_sum>odd_sum) {
        cout<<"EVEN"<<endl;
    } else {
        cout<<"ODD"<<endl;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin>>t;
    while(t--) {
        solve(); 
    }
    return 0;
}
