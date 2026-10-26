#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    
    vector<int> v = {10, 20, 30, 40, 50};

    int n = v.size();
    for (int i = 0; i < n / 2; ++i) 
    {
        swap(v[i], v[n - 1 - i]);
    }

    
    for (int num : v) 
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}