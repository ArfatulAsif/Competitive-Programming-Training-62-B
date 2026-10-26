#include <iostream>
#include <string>
using namespace std;

int main() 
{
    // Declare a pair of numbers
    int num1 = 5, num2 = 10;

    // Declare a string
    string str = "Hello, World!";

    // Loop through the string
    for (size_t i = 0; i < str.length(); ++i) 
    {
        cout << str[i] << endl;
    }

    return 0;
}