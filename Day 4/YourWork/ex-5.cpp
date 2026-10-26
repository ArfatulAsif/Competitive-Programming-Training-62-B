#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int> v = {1,2, 3, 4};
    for(int i : v)
    {
        cout << i << " ";
        if (i == v.front()) {
            cout << "(front)";
        }
        if (i == v.back()) {
            cout << "(back)";
        }
    }
   
    cout << endl;
}