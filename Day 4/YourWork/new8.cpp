#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<pair<int,char>>v={{12,'a'},{12,'b'},{11,'a'}};
    sort(v.begin(),v.end());
    for(auto x:v)
    {
        cout<<x.first <<" "<<x.second<<endl;
    }
    return 0;
}