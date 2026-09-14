#include<iostream>
using namespace std;
int main()
{
    pair < int , pair<string, double>> student = {1 , {"bikash", 3.6}};
    cout <<"ID: " << student.first << " Name: " << student.second.first << "CGPA: " << student.second.second << endl;
    return 0;
}