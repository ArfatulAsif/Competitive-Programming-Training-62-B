#include<bits/stdc++.h>
using  namespace std;
void solve(){


    int n;
    cin>>n;
    vector<string>words(n);
    for(int i=0;i<n;i++){
        cin>>words[i];
    }
    string longest_word=" ";
    int max_len=-1;
     for(string s : words) {
        if(s.size() > max_len) {
            max_len = s.size();
            longest_word = s;
        }
    }
    cout << longest_word << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
