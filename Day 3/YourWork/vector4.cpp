#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<pair<string,int>>v;
    int n;
    cin>>n;
    v.push_back({"arman",33});
     v.push_back({"eva",55});
      v.push_back({"srijon",6});
      for(auto x: v)
      {
        cout<<x.first<<" "<<x.second<<endl;
      }

}