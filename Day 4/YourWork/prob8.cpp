#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<pair<int,int>> v;
    v.push_back({12,55});
    v.push_back({14,58});
    for(auto p:v)
    {
        cout<<p.first<<" "<<p.second<<endl;
    }
}