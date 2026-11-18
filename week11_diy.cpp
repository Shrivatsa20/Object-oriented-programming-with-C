// Experiment 11 (Week 11) - DIY programs: Templates and STL Containers
// Compile: g++ week11_diy.cpp -o week11_diy

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Generic utilities: Write template functions swapVals(T&, T&) and findMax(T arr[], int n) and test with int and double.
// ---------------------------------------------------------------
namespace diy1 {
    template <typename T>
    void swapVals(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    T findMax(T arr[], int n) {
        T best = arr[0];
        for (int i = 1; i < n; ++i)
            if (arr[i] > best) best = arr[i];
        return best;
    }

    int run() {
        int a = 10, b = 20;
        swapVals(a, b);
        cout << "int    after swap : a = " << a << ", b = " << b << endl;

        double x = 1.5, y = 9.25;
        swapVals(x, y);
        cout << "double after swap : x = " << x << ", y = " << y << endl;

        int    ia[] = {4, 17, 9, 23, 6};
        double da[] = {2.5, 8.75, 3.1, 8.7};

        cout << "findMax(int array)    = " << findMax(ia, 5) << endl;
        cout << "findMax(double array) = " << findMax(da, 4) << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Generic Queue: Implement a class template Queue<T> with enqueue/dequeue/front; test with string.
// ---------------------------------------------------------------
namespace diy2 {
    template <typename T>
    class Queue {
        T data[5];                           // fixed capacity, used as a circular buffer
        int head = 0, tail = 0, count = 0;

    public:
        bool enqueue(const T &x) {
            if (count == 5) { cout << "Queue full" << endl; return false; }
            data[tail] = x;
            tail = (tail + 1) % 5;
            ++count;
            return true;
        }

        bool dequeue() {
            if (count == 0) { cout << "Queue empty" << endl; return false; }
            head = (head + 1) % 5;
            --count;
            return true;
        }

        T &front()        { return data[head]; }
        bool empty() const { return count == 0; }
        int  size()  const { return count; }
    };

    int run() {
        Queue<string> q;

        q.enqueue("alpha");
        q.enqueue("beta");
        q.enqueue("gamma");
        cout << "Size  = " << q.size() << ", front = " << q.front() << endl;

        q.dequeue();
        cout << "After one dequeue, front = " << q.front() << endl;

        q.enqueue("delta");
        cout << "Draining queue: ";
        while (!q.empty()) {
            cout << q.front() << " ";
            q.dequeue();
        }
        cout << endl;

        q.dequeue();                         // underflow check
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Frequency counter: Read words from input and use an unordered_map<string,int> to print each word with its count; then print the most frequent word.
// ---------------------------------------------------------------
namespace diy3 {
    int run() {
        string line, w;
        cout << "Enter some words: ";
        getline(cin, line);

        unordered_map<string, int> freq;
        stringstream ss(line);
        while (ss >> w)
            freq[w]++;                       // count each word

        cout << "Word frequencies:" << endl;
        string best;
        int bestCount = 0;

        for (auto &p : freq) {
            cout << "  " << p.first << " : " << p.second << endl;
            if (p.second > bestCount) {
                bestCount = p.second;
                best = p.first;
            }
        }

        cout << "Most frequent word: " << best << " (" << bestCount << " times)" << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 11 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
