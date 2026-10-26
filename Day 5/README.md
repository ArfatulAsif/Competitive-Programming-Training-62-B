# Part 1: Prefix Sums

### Program 1: Building a 1D Prefix Sum Array

**Concept:** Constructing the prefix sum array $P$, where $P[i] = A[0] + A[1] + \dots + A[i]$.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
   
    cin >> n;

    vector<int> a(n);
    
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Building prefix sum array
    vector<long long> pref(n);
    pref[0] = a[0];
    for(int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }

    cout << "Prefix Sum Array: " << endl;
    for(int i = 0; i < n; i++) {
        cout << pref[i] << " ";
    }
    cout << endl;

    return 0;
}

```

**Sample Input:**

```text
5
2 4 1 7 3

```

**Sample Output:**

```text
Prefix Sum Array: 
2 6 7 14 17 

```

---

### Program 2: 1-Based Static Range Sum Queries ($O(1)$ Query)

**Concept:** Answering $Q$ queries for the sum in range $[L, R]$ using 1-based indexing to eliminate boundary checks.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    // 1-based indexing makes range formulas cleaner: pref[R] - pref[L-1]
    vector<long long> a(n + 1, 0);
    vector<long long> pref(n + 1, 0);

    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    while(q--) {
        int l, r;
        cin >> l >> r;
        long long range_sum = pref[r] - pref[l - 1];
        cout << "Sum from " << l << " to " << r << " = " << range_sum << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
5 3
2 4 1 7 3
1 3
2 5
4 4

```

**Sample Output:**

```text
Sum from 1 to 3 = 7
Sum from 2 to 5 = 15
Sum from 4 to 4 = 7

```

---

### Program 3: Substring Character Frequency Queries

**Concept:** Extend prefix sum to non-numeric data. Count occurrences of a character in substring $[L, R]$ in $O(1)$.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // pref[i][ch] stores count of character 'ch' in prefix s[0...i-1]
    vector<vector<int> > pref(n + 1, vector<int>(26, 0));

    for(int i = 1; i <= n; i++) {
        for(int c = 0; c < 26; c++) {
            pref[i][c] = pref[i - 1][c];
        }
        pref[i][s[i - 1] - 'a']++;
    }

    int q;
    cin >> q;
    while(q--) {
        int l, r;
        char target;
        cin >> l >> r >> target;

        int char_idx = target - 'a';
        int count_in_range = pref[r][char_idx] - pref[l - 1][char_idx];

        cout << "Count of '" << target << "' in range [" << l << ", " << r << "] = " << count_in_range << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
abacaba
3
1 7 a
2 5 b
3 4 c

```

**Sample Output:**

```text
Count of 'a' in range [1, 7] = 4
Count of 'b' in range [2, 5] = 2
Count of 'c' in range [3, 4] = 1

```

---

### Program 4: 2D Prefix Sum (Subgrid Sum Query)

**Concept:** Subgrid sum from top-left $(r1, c1)$ to bottom-right $(r2, c2)$ in $O(1)$ time.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<long long> > a(n + 1, vector<long long>(m + 1, 0));
    vector<vector<long long> > pref(n + 1, vector<long long>(m + 1, 0));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            pref[i][j] = a[i][j] 
                       + pref[i - 1][j] 
                       + pref[i][j - 1] 
                       - pref[i - 1][j - 1];
        }
    }

    int q;
    cin >> q;
    while(q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        long long subgrid_sum = pref[r2][c2] 
                              - pref[r1 - 1][c2] 
                              - pref[r2][c1 - 1] 
                              + pref[r1 - 1][c1 - 1];

        cout << "Subgrid sum = " << subgrid_sum << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
3 3
1 2 3
4 5 6
7 8 9
2
1 1 2 2
2 2 3 3

```

**Sample Output:**

```text
Subgrid sum = 12
Subgrid sum = 28

```

---

# Part 2: Binary Search 

### Program 1: Standard Iterative Binary Search

**Concept:** Standard $O(\log N)$ search returning 0-based index or $-1$.

```cpp
#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int>& a, int target) {
    int low = 0, high = a.size() - 1;

    while(low <= high) {
        int mid = low + (high - low) / 2; // Prevents integer overflow

        if(a[mid] == target) {
            return mid;
        } else if(a[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n, target;
    cin >> n >> target;

    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end()); // Binary search requires a sorted array

    int index = binarySearch(a, target);
    if(index != -1) {
        cout << "Found at index " << index << endl;
    } else {
        cout << "Not Found" << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
5 7
10 3 7 1 9

```

**Sample Output:**

```text
Found at index 2

```

*(Note: Array is sorted internally to `[1, 3, 7, 9, 10]`, so target `7` is found at 0-based index 2).*

---

### Program 2: STL `lower_bound` & `upper_bound` Applications

**Concept:** Finding first element $\ge X$, first element $> X$, and total occurrences of $X$ in $O(\log N)$.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    // lower_bound: iterator to first element >= x
    // upper_bound: iterator to first element > x
    auto it1 = lower_bound(a.begin(), a.end(), x);
    auto it2 = upper_bound(a.begin(), a.end(), x);

    if(it1 != a.end() && *it1 == x) {
        int first_pos = it1 - a.begin();
        int last_pos = it2 - a.begin() - 1;
        int frequency = it2 - it1;

        cout << "First occurrence at index: " << first_pos << endl;
        cout << "Last occurrence at index: " << last_pos << endl;
        cout << "Total frequency of " << x << " = " << frequency << endl;
    } else {
        cout << "Element " << x << " not present." << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
7 4
2 4 1 4 4 9 5

```

**Sample Output:**

```text
First occurrence at index: 2
Last occurrence at index: 4
Total frequency of 4 = 3

```

*(Note: Array is sorted internally to `[1, 2, 4, 4, 4, 5, 9]`).*

---

### Program 3: Integer Square Root (Binary Search on Answer)

**Concept:** Search for largest integer $X$ such that $X \times X \le N$ without using `sqrt()`.

```cpp
#include <bits/stdc++.h>
using namespace std;

long long integerSqrt(long long n) {
    long long low = 1, high = n, ans = 0;

    while(low <= high) {
        long long mid = low + (high - low) / 2;

        if(mid * mid <= n) {
            ans = mid;     // mid is a valid answer, try to find a larger one
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    long long n;
    cin >> n;

    cout << "Integer Square Root of " << n << " is: " << integerSqrt(n) << endl;

    return 0;
}

```

**Sample Input:**

```text
27

```

**Sample Output:**

```text
Integer Square Root of 27 is: 5

```

---

### Program 4: Wood Cutter Problem (Monotonic Predicate Function)

**Concept:** Given $N$ tree heights, set saw blade height $H$ to obtain at least $M$ meters of wood (Maximizing $H$).

```cpp
#include <bits/stdc++.h>
using namespace std;

bool canGetWood(vector<long long>& trees, long long h, long long m) {
    long long wood = 0;
    for(int i = 0; i < trees.size(); i++) {
        if(trees[i] > h) {
            wood += (trees[i] - h);
        }
    }
    return wood >= m;
}

int main() {
    int n;
    long long m;
    cin >> n >> m;

    vector<long long> trees(n);
    long long max_h = 0;

    for(int i = 0; i < n; i++) {
        cin >> trees[i];
        max_h = max(max_h, trees[i]);
    }

    long long low = 0, high = max_h, best_h = 0;

    while(low <= high) {
        long long mid = low + (high - low) / 2;

        if(canGetWood(trees, mid, m)) {
            best_h = mid;    // Try to increase saw height to save trees
            low = mid + 1;
        } else {
            high = mid - 1;  // Lower saw height to get more wood
        }
    }

    cout << "Maximum saw height: " << best_h << endl;

    return 0;
}

```

**Sample Input:**

```text
4 7
20 15 10 17

```

**Sample Output:**

```text
Maximum saw height: 15

```

---

### Program 5: Binary Search on Floating Point / Continuous Domain

**Concept:** Find continuous values (e.g., $\sqrt{N}$ up to 6 decimal places) using fixed iterations to avoid precision infinite loops.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    double n;
    cin >> n;

    double low = 0, high = max(1.0, n);

    // Running 100 iterations gives precision around 10^-15
    for(int iter = 0; iter < 100; iter++) {
        double mid = low + (high - low) / 2.0;

        if(mid * mid <= n) {
            low = mid;
        } else {
            high = mid;
        }
    }

    cout << fixed << setprecision(6);
    cout << "Precise Square Root = " << low << endl;

    return 0;
}

```

**Sample Input:**

```text
50

```

**Sample Output:**

```text
Precise Square Root = 7.071068

```
