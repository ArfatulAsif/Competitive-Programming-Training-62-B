#include<iostream>
#include<set>
using namespace std;

int32_t main()
{   
    ios::sync_with_std(0);
    cin.tie(0);

    int n; cin >> n;
    set<int>s;
    for(int i = 0; i < n; i++)
    {
        int x; cin >> x;
        s.insert(x);
    }

    cout << "total unique elements: " << s.size()<< endl;
    cout << "elements in sorted order: ";
    for(auto it = s.begin(); it != s.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    int target; cin >> target;
    if(s.count(target))
    {
        cout << target << " is present in the set." << endl;
    }
    else
    {
        cout << target << " is not count in the set." << endl;
    }
    return 0;

}