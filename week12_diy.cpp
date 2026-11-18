// Experiment 12 (Week 12) - DIY programs: STL Algorithms, Lambdas and Heaps
// Compile: g++ week12_diy.cpp -o week12_diy

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Sort pairs: given a vector<pair<string,int>>, sort by the integer (second) field ascending, then print.
// ---------------------------------------------------------------
namespace diy1 {
    int run() {
        vector<pair<string, int>> v = {
            {"Asha", 88}, {"Ravi", 72}, {"Meera", 95}, {"Kiran", 60}, {"Divya", 81}
        };

        // sort by the integer (second) field, ascending
        sort(v.begin(), v.end(),
             [](const pair<string, int> &a, const pair<string, int> &b) {
                 return a.second < b.second;
             });

        cout << "Sorted by marks (ascending):" << endl;
        for (auto &p : v)
            cout << "  " << p.first << " " << p.second << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Top-3 with heap: read N numbers and print the three largest using a priority_queue (do not sort the whole array).
// ---------------------------------------------------------------
namespace diy2 {
    int run() {
        int n;
        cout << "Enter N: ";
        cin >> n;

        // min-heap that never holds more than 3 values -> the 3 largest seen so far
        priority_queue<int, vector<int>, greater<int>> heap;

        cout << "Enter " << n << " numbers: ";
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            heap.push(x);
            if (heap.size() > 3) heap.pop();     // drop the smallest of the four
        }

        vector<int> top;
        while (!heap.empty()) {
            top.push_back(heap.top());
            heap.pop();
        }

        cout << "Three largest: ";
        for (int i = (int)top.size() - 1; i >= 0; --i)   // heap gives smallest first
            cout << top[i] << " ";
        cout << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Custom aggregate: use accumulate with a lambda to compute the product of all elements, or the sum of only the even ones.
// ---------------------------------------------------------------
namespace diy3 {
    int run() {
        vector<int> v = {1, 2, 3, 4, 5, 6};

        // product of all elements
        int product = accumulate(v.begin(), v.end(), 1,
                                 [](int acc, int x) { return acc * x; });

        // sum of only the even elements
        int evenSum = accumulate(v.begin(), v.end(), 0,
                                 [](int acc, int x) { return (x % 2 == 0) ? acc + x : acc; });

        cout << "Product of all elements : " << product << endl;
        cout << "Sum of even elements    : " << evenSum << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 12 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
