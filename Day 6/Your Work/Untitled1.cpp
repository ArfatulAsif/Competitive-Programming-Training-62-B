#include<bits/stdc++.h>
using namespace std;
int main(){

    int n;
    cin>>n;
    set<int>s;
    for(int i=0;i<n;i++)
    {
        int val;
        cin>>val;
        s.insert(val);
    }

    cout<<"Total unique elements : "<<s.size()<<'\n';
    cout<<"Elements in sorted order: ";
    for(auto it=s.begin();it!=s.end();it++)
    {
        cout<<*it<<'\n';
    }
    cout<<'\n';

    int target;
    cin>>target;
    if(s.count(target))
    {
        cout<<target<<" is present in the set."<<'\n';
    }
    else{
        cout<<"Not present."<<'\n';
    }

return 0;
}
