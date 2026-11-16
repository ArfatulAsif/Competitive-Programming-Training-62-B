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
