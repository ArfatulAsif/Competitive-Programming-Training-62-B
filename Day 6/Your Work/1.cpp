#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    set<int>s;
    for(int i=0;i<n;i++)
    {
        int value;
        cin>>value;
        s.insert(value);
    }
    cout<<"Total unique elements:"<<s.size()<<endl;
    cout<<"Sorted Order: ";
    for(auto x:s)
    {
        cout<<x<<" ";
    }
    cout<<endl;

    int target;
    cin>>target;
    if(s.count(target)){
        cout<<target<<" is present in the set"<<endl;
    }
    else{
        cout<<target<<"is not present in the set"<<endl;
    }
    return 0;
}