#include <iostream>
#include <vector>
#include <algorithm> // for std::sort

using namespace std;

int main() 
{
    vector<int> numbers = {5, 2, 8, 1, 3};

   
    sort(numbers.begin(), numbers.end());

   
    for (int num : numbers) 
    {
        cout << num << " ";
    }

    return 0;
}