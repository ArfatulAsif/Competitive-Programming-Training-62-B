#include<bits/stdc++.h>
using namespace std;
int main()
{
    pair<int, pair<string, double> >p;
    p={53, {"Tania",3.99}};
    
    cout<<"ID: "<<p.first<<endl;
    cout<<"Name: "<<p.second.first<<endl;
    cout<<"CGPA: "<<p.second.second<<endl;
    return 0;

}