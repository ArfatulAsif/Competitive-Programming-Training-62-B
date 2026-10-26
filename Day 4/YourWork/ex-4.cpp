#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> v(5, 10);
    for(int x : v)
    {
        cout << x <<" ";
    }
    cout << endl;
}