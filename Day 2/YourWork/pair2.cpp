#include<iostream>
#include <utility>
using namespace std;
int main()
{
    pair < string, int > student = {"bikash", 82};
    cout << "Name: " << student.first << ", ID: " << student.second << endl;
    return 0;

}