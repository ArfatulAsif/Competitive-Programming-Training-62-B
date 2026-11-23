#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
     vector<int> a(n);
     for(int i=0;i<n;i++)
     {
        cin>>a[i];
     }
     vector<long long> pref(n);
     pref[0]=a[0];
     for(int i=1;i<n;i++)
     {
        pref[i]=pref[i-1]+a[i];
     }
     cout<< " prefix sum array: "<<endl;
     for(int i=0;i<n;i++)
     {
        cout<<pref[i]<<" ";
    }
    cout<<endl;
    return 0;

}