#include <bits/stdc++.h>
using namespace std;

int main() {

    vector<pair<int, int> > v; 
    
    v.push_back(make_pair(2, 5));
    v.push_back(make_pair(1, 9));
    v.push_back(make_pair(2, 3));
    v.push_back(make_pair(1, 4));
    
    sort(v.begin(),v.end());
    
    cout<<"Sorted pairs:"<<endl;
    for(int i=0;i<v.size();i++) {
        cout<<"{"<<v[i].first<< ", "<< v[i].second<< "}"<< endl;
    }
    return 0;
}
