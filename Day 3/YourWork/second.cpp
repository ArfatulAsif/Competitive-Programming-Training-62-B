#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    int n = v.size();

    for(int i=0;i<n/2;i++)
    {
        int temp=v[i];
        v[i]=v[n-1-i];
        v[n-1-i]=temp;
    }
     for(int i=0;i<n;i++)
     {
        cout<< v[i]<<endl;
     }
     return 0;
}