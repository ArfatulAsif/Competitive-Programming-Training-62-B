#include <iostream>
#include <vector>
using namespace std;

void solve()
{
    int n;
    cin>>n;
    vector<string> name(n);
    for(int i=0;i<n;i++)
    {
        cin>>name[i];
    }
    string longest_word=" ";
    int max_len=-1;
    for(string s: name)
    {
        if(s.size()>max_len)
        {
            max_len=s.size();
            longest_word=s;
        }
    }
   cout<<longest_word<<endl; 

}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}