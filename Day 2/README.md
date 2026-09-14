
# Lab 1: Foundations & Basic STL

Welcome to Competitive Programming! 

## 1. Pair

A `pair` is a simple container that ties two values together into a single unit. It is extremely useful when you need to store two related pieces of data, like an $(x, y)$ coordinate.

**Example 1: Basic Pair Declaration and Assignment**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    pair<int, int> p1;
    p1.first = 10;
    p1.second = 20;
    
    cout << "First value: " << p1.first << "\n";
    cout << "Second value: " << p1.second << "\n";
    
    return 0;
}

```

**Example 2: Initializing Pairs quickly (C++11 style)**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // You can use {} to instantly create and assign a pair
    pair<string, int> student = {"Arfatul", 101};
    
    cout << "Name: " << student.first << ", Roll: " << student.second << "\n";
    
    return 0;
}

```

**Example 3: Nested Pairs (A Pair inside a Pair)**
Sometimes you need to store 3 related items. You can put a pair inside another pair!

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Stores: { ID, {Name, CGPA} }
    pair<int, pair<string, double>> student_data;
    
    student_data = {1, {"Alice", 3.95}};
    
    // Printing a nested pair
    cout << "ID: " << student_data.first << "\n";
    cout << "Name: " << student_data.second.first << "\n";
    cout << "CGPA: " << student_data.second.second << "\n";
    
    return 0;
}

```

---

## 2. String

In CP, we avoid C-style character arrays (`char arr[]`) and use C++ `string` instead. It acts like an automatically resizing array of characters.

**Example 1: Taking String Input and Printing**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s; // Reads a single word (stops at space)
    cout << "You entered: " << s << "\n";
    
    return 0;
}

```

**Example 2: Concatenating (Joining) Strings**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1 = "Competitive";
    string s2 = "Programming";
    
    // You can add strings together using the + operator
    string s = s1 + " " + s2; 
    
    cout << "Result: " << s << "\n";
    
    return 0;
}

```

**Example 3: Changing characters using a for-loop**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "hello";
    
    // Let's make every alternate character uppercase
    for(int i = 0; i < s.size(); i++) {
        if(i % 2 == 0) {
            s[i] = toupper(s[i]); 
        }
    }
    
    cout << "Modified string: " << s << "\n"; // Prints: HeLlO
    
    return 0;
}

```

---

## 3. Vector

A `vector` is a dynamic array. Unlike standard arrays (e.g., `int arr[100];`), vectors can grow and shrink in size automatically.

**Example 1: Input and Storing Numbers**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> v;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back(x); // Adds x to the back of the vector
    }
    for (int i=0;i < n;i++)
    {
			    cout << v[i] << endl;
    }
    
    return 0;
}

```

**Example 2: Reversing a Vector using a for-loop**

```cpp
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

```

**Example 3: Traversing with a For-Each Loop**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    
    // "For each integer 'x' inside vector 'v'..."
    for(int x : v) {
        cout << x << " ";
    }
    cout << "\n";
    
    return 0;
}

```

### Leveling Up with Vectors: 5 More Examples

**Level 1: Initialization with Default Values**

```cpp
// Creates a vector of size 5, where every element is initially 10
vector<int> v(5, 10); 

```

**Level 2: The `front()` and `back()` functions**

```cpp
vector<int> v = {5, 9, 15, 22};
cout << v.front() << "\n"; // Prints 5 (first element)
cout << v.back() << "\n";  // Prints 22 (last element)

```

**Level 3: Removing elements with `pop_back()**`

```cpp
vector<int> v = {1, 2, 3};
v.pop_back(); // Removes the last element (3). Size is now 2.

```

**Level 4: Copying vectors directly**

```cpp
vector<int> v1 = {10, 20, 30};
vector<int> v2;
v2 = v1; // In C++, you can copy an entire vector with the = operator!

```

**Level 5: Vector of Pairs (Very common in CP)**

```cpp
vector<pair<int, int>> points;
points.push_back({1, 5});
points.push_back({3, 7});

for(auto p : points) {
    cout << "X: " << p.first << ", Y: " << p.second << "\n";
}

```

---

## 4. Handling Test Cases (Codeforces Style)

In CP, your program usually doesn't run just once. The platform will give you an integer $t$ (the number of test cases), followed by $t$ distinct problems to solve in a single run.

### Problem A: Even-Odd Battle

**Problem Statement:**
You are given $t$ test cases. In each test case, you are given an integer $n$, followed by an array of $n$ integers. Print "EVEN" if the sum of all even numbers in the array is strictly greater than the sum of all odd numbers. Otherwise, print "ODD".

**Solution Code:**

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<int> v(n);
    long long even_sum = 0;
    long long odd_sum = 0;
    
    for(int i = 0; i < n; i++) {
        cin >> v[i]; // Reading directly into the sized vector
        if(v[i] % 2 == 0) {
            even_sum += v[i];
        } else {
            odd_sum += v[i];
        }
    }
    
    if(even_sum > odd_sum) {
        cout << "EVEN\n";
    } else {
        cout << "ODD\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t; // Read number of test cases
    while(t--) {
        solve(); // Process each test case individually
    }
    return 0;
}

```

### Problem B: Hide and Seek Words

**Problem Statement:**
You are given $t$ test cases. In each testcase, you are given an integer $n$, followed by $n$ strings. Your task is to output the longest string in the list. If multiple strings share the maximum length, print the one that appeared *first*.

**Solution Code (Using Vector of Strings):**

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<string> words(n);
    for(int i = 0; i < n; i++) {
        cin >> words[i];
    }
    
    string longest_word = "";
    int max_len = -1;
    
    // Traversing the vector of strings using a for-each loop
    for(string s : words) {
        if(s.size() > max_len) {
            max_len = s.size();
            longest_word = s;
        }
    }
    
    cout << longest_word << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

```
