# Part 3: STL `set` and `map` (Associative Containers)

### Program 1: STL `set` (Unique & Sorted Elements)

**Concept:** A `set` stores unique elements in sorted order. Insertions, deletions, and searches take $O(\log N)$ time. It is highly useful when you need to remove duplicates and keep data ordered.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    set<int> s;
    for(int i = 0; i < n; i++) {
        int val;
        cin >> val;
        s.insert(val); // Inserts element; duplicates are automatically ignored
    }

    cout << "Total unique elements: " << s.size() << endl;

    cout << "Elements in sorted order: ";
    for(auto it = s.begin(); it != s.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // Searching for an element using .count() (returns 1 if present, 0 if not)
    int target;
    cin >> target;
    if(s.count(target)) {
        cout << target << " is present in the set." << endl;
    } else {
        cout << target << " is NOT present in the set." << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
7
5 2 8 5 2 1 9
8

```

**Sample Output:**

```text
Total unique elements: 5
Elements in sorted order: 1 2 5 8 9 
8 is present in the set.

```

---

### Program 2: STL `map` (Frequency Counter)

**Concept:** A `map` stores key-value pairs sorted by keys. It is commonly used to count the frequency of elements (like strings or large numbers) where a standard array cannot be used as a frequency array. Operations take $O(\log N)$ time.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    map<string, int> freq;
    
    for(int i = 0; i < n; i++) {
        string word;
        cin >> word;
        freq[word]++; // If word doesn't exist, it's created with value 0, then incremented
    }

    cout << "Word Frequencies:" << endl;
    // Iterating through the map (elements are stored in alphabetical order of keys)
    for(auto it = freq.begin(); it != freq.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }

    // Accessing a specific key
    string query;
    cin >> query;
    cout << "Frequency of '" << query << "' is: " << freq[query] << endl;

    return 0;
}

```

**Sample Input:**

```text
6
apple banana apple orange banana apple
banana

```

**Sample Output:**

```text
Word Frequencies:
apple : 3
banana : 2
orange : 1
Frequency of 'banana' is: 2

```

---

# Part 4: STL `stack` and `queue` (Container Adapters)

### Program 3: STL `stack` (Balanced Parentheses)

**Concept:** A `stack` follows Last-In-First-Out (LIFO). Elements are pushed to the top and popped from the top. Operations take $O(1)$ time. A classic application is checking if a string of brackets is balanced.

```cpp
#include <bits/stdc++.h>
using namespace std;

bool isValid(string s) {
    stack<char> st;
    
    for(char ch : s) {
        if(ch == '(' || ch == '{' || ch == '[') {
            st.push(ch); // Push opening brackets
        } 
        else {
            if(st.empty()) return false; // Closing bracket with no opening bracket
            
            char top = st.top();
            if((ch == ')' && top == '(') || 
               (ch == '}' && top == '{') || 
               (ch == ']' && top == '[')) {
                st.pop(); // Match found, remove opening bracket
            } else {
                return false; // Mismatched brackets
            }
        }
    }
    
    return st.empty(); // If stack is empty, all brackets were matched
}

int main() {
    int t;
    cin >> t;
    
    while(t--) {
        string s;
        cin >> s;
        if(isValid(s)) {
            cout << s << " -> Balanced" << endl;
        } else {
            cout << s << " -> Not Balanced" << endl;
        }
    }

    return 0;
}

```

**Sample Input:**

```text
3
()[]{}
([)]
(([]))

```

**Sample Output:**

```text
()[]{} -> Balanced
([)] -> Not Balanced
(([])) -> Balanced

```

---

### Program 4: STL `queue` (Basic Operations & Simulation)

**Concept:** A `queue` follows First-In-First-Out (FIFO). Elements are added to the back (`push`) and removed from the front (`pop`). Operations take $O(1)$ time. It is highly useful for scheduling and Breadth-First Search (BFS).

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q; // Number of queries
    
    queue<string> line;
    
    cout << "Processing Queue Operations:" << endl;
    while(q--) {
        int type;
        cin >> type;
        
        if(type == 1) {
            // Type 1: Person joins the queue
            string name;
            cin >> name;
            line.push(name);
            cout << name << " joined the line." << endl;
        } 
        else if(type == 2) {
            // Type 2: Front person is served
            if(line.empty()) {
                cout << "Line is already empty!" << endl;
            } else {
                cout << line.front() << " has been served and left the line." << endl;
                line.pop();
            }
        } 
        else if(type == 3) {
            // Type 3: Check who is at the front
            if(line.empty()) {
                cout << "Nobody is in the line." << endl;
            } else {
                cout << "Next in line is: " << line.front() << endl;
            }
        }
    }
    
    cout << "\nRemaining people in line: " << line.size() << endl;

    return 0;
}

```

**Sample Input:**

```text
6
1 Alice
1 Bob
3
2
1 Charlie
2

```

**Sample Output:**

```text
Processing Queue Operations:
Alice joined the line.
Bob joined the line.
Next in line is: Alice
Alice has been served and left the line.
Charlie joined the line.
Bob has been served and left the line.

Remaining people in line: 1

```





---
---
---

# Part 1: Two Pointers

### Program 1: Two Sum in a Sorted Array

**Concept:** Checking whether the sum of two numbers in a sorted array exactly equals a target $X$ in $O(N)$ time. We place pointers at the beginning and end, moving them inward based on the current sum.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;

    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Assuming the array is already sorted. If not, sort(a.begin(), a.end());
    int left = 0, right = n - 1;
    bool found = false;

    while(left < right) {
        long long current_sum = a[left] + a[right];

        if(current_sum == target) {
            cout << "Pair found: " << a[left] << " and " << a[right] << endl;
            found = true;
            break; 
        } 
        else if(current_sum < target) {
            left++; // We need a larger sum, move left pointer right
        } 
        else {
            right--; // We need a smaller sum, move right pointer left
        }
    }

    if(!found) {
        cout << "No pair exists that sums to " << target << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
6 11
1 3 4 6 8 10

```

**Sample Output:**

```text
Pair found: 3 and 8

```

---

### Program 2: Valid Palindrome (Two Pointers from Ends)

**Concept:** Checking if a string reads the same forwards and backwards by comparing characters from both ends, moving towards the center.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int left = 0;
    int right = s.length() - 1;
    bool is_palindrome = true;

    while(left < right) {
        if(s[left] != s[right]) {
            is_palindrome = false;
            break;
        }
        left++;
        right--;
    }

    if(is_palindrome) {
        cout << "The string is a palindrome." << endl;
    } else {
        cout << "The string is NOT a palindrome." << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
racecar

```

**Sample Output:**

```text
The string is a palindrome.

```

---

### Program 3: Merging Two Sorted Arrays

**Concept:** Merging two sorted arrays into a single sorted array in $O(N + M)$ time using two pointers starting at the beginning of each array.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m), merged;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];

    int i = 0, j = 0;

    // Traverse both arrays
    while(i < n && j < m) {
        if(a[i] <= b[j]) {
            merged.push_back(a[i]);
            i++;
        } else {
            merged.push_back(b[j]);
            j++;
        }
    }

    // Add remaining elements of array a (if any)
    while(i < n) {
        merged.push_back(a[i]);
        i++;
    }

    // Add remaining elements of array b (if any)
    while(j < m) {
        merged.push_back(b[j]);
        j++;
    }

    cout << "Merged Array: ";
    for(int x : merged) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

```

**Sample Input:**

```text
4 3
1 4 5 8
2 3 6

```

**Sample Output:**

```text
Merged Array: 1 2 3 4 5 6 8 

```

---

### Program 4: Remove Duplicates In-Place (Slow and Fast Pointers)

**Concept:** Removing duplicates from a sorted array in $O(N)$ time using a "slow" pointer that tracks the position of unique elements and a "fast" pointer that scans the array.

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

    if(n == 0) return 0;

    int slow = 0; // Tracks the index of the last unique element found

    for(int fast = 1; fast < n; fast++) {
        if(a[fast] != a[slow]) {
            slow++;
            a[slow] = a[fast];
        }
    }

    int unique_count = slow + 1;

    cout << "Number of unique elements: " << unique_count << endl;
    cout << "Array after removing duplicates: ";
    for(int i = 0; i < unique_count; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

```

**Sample Input:**

```text
7
2 2 3 3 3 5 6

```

**Sample Output:**

```text
Number of unique elements: 4
Array after removing duplicates: 2 3 5 6 

```

---

# Part 2: Sliding Window

### Program 1: Maximum Sum of a Subarray of Size K (Fixed Window)

**Concept:** Find the maximum sum of any contiguous subarray of exactly size $K$ in $O(N)$ time. We compute the sum of the first window, then slide it by adding the new element and subtracting the oldest element.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (k > n) {
        cout << "Invalid window size." << endl;
        return 0;
    }

    long long current_sum = 0, max_sum = 0;

    // Compute sum of the first window
    for(int i = 0; i < k; i++) {
        current_sum += a[i];
    }
    max_sum = current_sum;

    // Slide the window from index k to n-1
    for(int i = k; i < n; i++) {
        current_sum += a[i] - a[i - k]; // Add new element, remove old element
        max_sum = max(max_sum, current_sum);
    }

    cout << "Maximum sum of subarray of size " << k << " is: " << max_sum << endl;

    return 0;
}

```

**Sample Input:**

```text
7 3
2 1 5 1 3 2 1

```

**Sample Output:**

```text
Maximum sum of subarray of size 3 is: 9

```

*(Note: The maximum sum comes from the subarray `[5, 1, 3]`)*

---

### Program 2: Longest Subarray with Sum $\le S$ (Variable Window)

**Concept:** Find the length of the longest contiguous subarray whose sum is less than or equal to a given value $S$. Both pointers start at 0, and the left pointer only shrinks the window when the sum exceeds $S$.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long s;
    cin >> n >> s;

    vector<long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int left = 0, max_len = 0;
    long long current_sum = 0;

    for(int right = 0; right < n; right++) {
        current_sum += a[right]; // Expand window by adding the right element

        // Shrink window from the left if the sum exceeds S
        while(current_sum > s && left <= right) {
            current_sum -= a[left];
            left++;
        }

        // Update maximum length found so far
        max_len = max(max_len, right - left + 1);
    }

    cout << "Longest subarray length with sum <= " << s << " is: " << max_len << endl;

    return 0;
}

```

**Sample Input:**

```text
7 20
2 6 5 3 8 1 9

```

**Sample Output:**

```text
Longest subarray length with sum <= 20 is: 4

```

*(Note: The longest valid subarray is `[2, 6, 5, 3]` with sum 16 $\le$ 20).*

---

### Program 3: Minimum Size Subarray with Sum $\ge S$ (Variable Window)

**Concept:** Find the *minimum* length of a contiguous subarray whose sum is greater than or equal to $S$. The window expands until the condition is met, then shrinks from the left to find the smallest possible valid length.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long s;
    cin >> n >> s;

    vector<long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int left = 0, min_len = INT_MAX;
    long long current_sum = 0;

    for(int right = 0; right < n; right++) {
        current_sum += a[right];

        // While condition is satisfied, try to shrink the window
        while(current_sum >= s) {
            min_len = min(min_len, right - left + 1);
            current_sum -= a[left];
            left++;
        }
    }

    if(min_len == INT_MAX) {
        cout << "No subarray found with sum >= " << s << endl;
    } else {
        cout << "Minimum subarray length with sum >= " << s << " is: " << min_len << endl;
    }

    return 0;
}

```

**Sample Input:**

```text
6 7
2 3 1 2 4 3

```

**Sample Output:**

```text
Minimum subarray length with sum >= 7 is: 2

```

*(Note: The shortest valid subarray is `[4, 3]`).*

---

### Program 4: Longest Substring Without Repeating Characters (Variable Window)

**Concept:** Given a string, find the length of the longest substring without repeating characters using a sliding window and an array/set to track character frequencies.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.length();
    vector<int> count(256, 0); // Array to store frequency of characters

    int left = 0, max_len = 0;

    for(int right = 0; right < n; right++) {
        char current_char = s[right];
        count[current_char]++;

        // If a duplicate character is found, shrink the window from the left
        while(count[current_char] > 1) {
            char left_char = s[left];
            count[left_char]--;
            left++;
        }

        max_len = max(max_len, right - left + 1);
    }

    cout << "Longest substring without repeating characters has length: " << max_len << endl;

    return 0;
}

```

**Sample Input:**

```text
abcabcbb

```

**Sample Output:**

```text
Longest substring without repeating characters has length: 3

```

*(Note: The longest substrings without repeating characters are `"abc"`, `"bca"`, or `"cab"`).*








