#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
     map<string, int> freq;
    for(int i = 0; i < n; i++) 
    {
     string word;
     cin >> word;
        freq[word]++; 
    }
   cout <<"Word Frequencies:"<< endl;
    for(auto it = freq.begin(); it != freq.end(); it++) 
    {
        cout <<it->first<< " : " << it->second << endl;
    }
    string query;
    cin >> query;
    cout << "Frequency of "<< query<< "' is: " <<freq[query]<< endl;
    return 0;
}