#include<bits/stdc++.h>
using namespace std;
int main(){
    pair<int,pair<  string,double> >p1;
    p1.first=101;

    p1.second.first="Arafatul";
    
    p1.second.second=3.80;
    
    cout<<"id:"<<p1.first<<endl;
    
    cout<<"name:"<<p1.second.first<<endl;
    
    cout<<"cgpa:"<<p1.second.second<<endl;
    return 0;
}