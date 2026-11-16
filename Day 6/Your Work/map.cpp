#include<iostream>
#include<map>
using namespace std;

int32_t main()
{   
    ios::sync_with_std(0);
    cin.tie(0);

    int n; cin >> n;
    map< string, int> freq;
    for(int i = 0; i < n; i++)
    {
    string word; cin >> word; 
    freq[word]++;
    }
    cout << "word of frequencies:" << endl;
    for(auto it = freq.begin(); it != freq.end() it++)
    {
        cout << it-> first <<" : " << it -> second << endl; 
    }

    string query; cin >> query;
    cout << "frequency of " << query << "is: " << freq[query] << endl;
    return 0;
}





