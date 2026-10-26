#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n; cin >> n;
    vector<int>v[n];
    for(int i =0; i < n; i++)
    {
        int m; cin >> m;
        v.push_back(m);

    }
    for( int i = 0; i < n; i ++)
    {
        cout << v[i] << " ";
    }
    return 0;


}
