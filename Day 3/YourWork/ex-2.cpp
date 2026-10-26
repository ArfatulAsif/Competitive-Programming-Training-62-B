#include <iostream>
#include <vector>

using namespace std;

int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    vector<int> reversedVec;

    for (int i = vec.size() - 1; i >= 0; --i) 
    {
        reversedVec.push_back(vec[i]);
    }

    
    for (int i = 0; i < reversedVec.size(); ++i) 
    {
        cout << reversedVec[i] << " ";
    }
    cout << endl;

    return 0;
}