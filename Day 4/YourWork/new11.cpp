#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> v;
    v.push_back(50);
    v.push_back(12);
    v.push_back(60);
    v.push_back(10);
    v.push_back(3);
    cout <<"before sorting: "<<endl;
    for(auto x:v)
    {
        cout <<x<<" ";

    }
    cout <<"\n";
    sort(v.begin(),v.end());
    cout << "after sorting: "<<endl;
    for(auto p:v)
    {
        cout <<p<<" ";
    }
    return 0;

}