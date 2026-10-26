#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<pair<int,int> >points;
points.push_back(make_pair(1,5));
points.push_back(make_pair(3,7));

for(int i=0;i<points.size();i++) {
    cout << "X: " << points[i].first << ", Y: " << points[i].second << "\n";
}
}