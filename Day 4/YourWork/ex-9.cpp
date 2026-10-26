#include <iostream>
#include <vector>
using namespace std;

int main() 
{
    vector<pair<int, int>> v = {{1, 2}, {3, 4}, {5, 6}};

    for (const auto& [a, b] : v) 
    {   
        cout << "(" << a << ", " << b << ")" << endl;
    }

    return 0;
}