#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<int>v;
     for(int i=0;i<n;i++)
     {
        int f;
        cin>>f;
        v.push_back(f);

     }
     for(int i=0;i<n;i++)
     {
        cout<< v[i] <<endl;
     }
     return 0;
}