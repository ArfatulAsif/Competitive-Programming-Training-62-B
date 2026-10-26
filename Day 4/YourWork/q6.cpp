#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v;
    v.push_back(50);
    v.push_back(20);
    v.push_back(40);
    v.push_back(10);
    v.push_back(30);
    
    cout << "Before sorting: ";
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    sort(v.begin(), v.end());
    
    cout << "After sorting: ";
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    return 0;
}
