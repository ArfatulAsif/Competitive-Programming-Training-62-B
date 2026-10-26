#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;  cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++)
    {
        cin >> a[i];
    }
    vector<long long> prefix(n);
    prefix[0] = a[0];
    for(int i = 1; i < n; i++)
    {
        prefix[i] = prefix[i - 1] + a[i];
    }

    cout<< prefix[n-1] << endl;
    for(int i = 0; i < n; i++)
    {
        cout << prefix[i] << " ";
    }
    return 0;
}