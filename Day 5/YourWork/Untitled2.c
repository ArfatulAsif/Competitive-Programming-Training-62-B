#include <bits/stdc++.h>
using namespace std;

int main() {

  int n,q;
  cin>>n>>q;
  vector<long long>a(n+1,0);
  vecotor<long long>pref(n+1,0);

  for(int i=0;i<=n;i++)
  {
      cin>>a[i];
      pref[i]=pref[i-1]+a[i];
  }
  while(q--)
  {
      int l,r;
      cin>>l>>r;
      long long range_sum=pref[r]-pref[l-1];
      cout<<"sum from "<<l<<"to"<<r<<"="<<range_sum<<'\n';
  }

 return 0;
}
