#include <iostream>
#include <vector>
using namespace std;

int main() 
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = v1; 

    for (int i : v1) 
    {
        cout << i << " ";
    }
    cout << endl;

    for (int i : v2) 
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}