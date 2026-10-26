#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};
    int n = v.size();
    
    // Swap elements from the outside going inwards using two pointers
    for(int i = 0; i < n / 2; i++) {
        int temp = v[i];
        v[i] = v[n - 1 - i];
        v[n - 1 - i] = temp;
        // Tip: You can also just use the built-in swap(v[i], v[n - 1 - i]);
    }
		 for (int i=0;i < n;i++)
    {
			    cout << v[i] << endl;
    }
    
    // It is now reversed!
    return 0;
}
