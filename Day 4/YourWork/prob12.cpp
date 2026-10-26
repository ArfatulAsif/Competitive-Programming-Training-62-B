#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<int>v;
     v.push_back(50);
    v.push_back(20);
    v.push_back(40);
    v.push_back(10);
    v.push_back(30);
    cout<<"Befor sorting: "<<endl;
    for(auto x: v)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    sort(v.rbegin(),v.rend());
    cout<<"Descending order "<<endl;
    for(auto p: v)
    {
        cout<<p<<" ";
    }
    cout<<endl;

}