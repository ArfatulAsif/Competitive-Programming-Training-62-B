#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin>>n;
    vector<int>v(n);
    long long even=0;
    long long odd=0;
     for(int i=0;i<n;i++)
     {
        cin>>v[i];
        if(v[i]%2==0) even+=v[i];
        else odd+=v[i];
        
     }
     if(even>odd)cout<<"EVEN"<<endl;
        else cout<<"ODD"<<endl;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}