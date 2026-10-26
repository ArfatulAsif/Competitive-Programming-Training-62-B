#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int>v={2,4,1,5,3};
    reverse(v.begin(),v.end());
    for(int i=0;i<v.size();i++)
    {
cout << v[i] <<endl;
    }
    
    return 0;
}