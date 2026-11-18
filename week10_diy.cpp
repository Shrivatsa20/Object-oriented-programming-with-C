// Experiment 10 (Week 10) - DIY programs: File Handling
// Compile: g++ week10_diy.cpp -o week10_diy

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Number stats from file: read an unknown count of integers from nums.txt and print their count, sum, min and max.
// ---------------------------------------------------------------
namespace diy1 {
    int run() {
        ifstream in("nums.txt");
        if (!in) {
            cerr << "Cannot open nums.txt" << endl;
            return 1;
        }

        int x, count = 0, sum = 0, mn = 0, mx = 0;

        while (in >> x) {                    // reads until end-of-file, any count of numbers
            if (count == 0) mn = mx = x;
            if (x < mn) mn = x;
            if (x > mx) mx = x;
            sum += x;
            ++count;
        }

        if (count == 0) {
            cout << "File is empty" << endl;
            return 0;
        }

        cout << "Count = " << count << endl;
        cout << "Sum   = " << sum   << endl;
        cout << "Min   = " << mn    << endl;
        cout << "Max   = " << mx    << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Line-numbered copy: read in.txt and write out.txt with each line prefixed by its line number.
// ---------------------------------------------------------------
namespace diy2 {
    int run() {
        ifstream in("in.txt");
        ofstream out("out.txt");

        if (!in || !out) {
            cerr << "File open failed" << endl;
            return 1;
        }

        string line;
        int n = 0;

        while (getline(in, line))            // read one full line at a time
            out << ++n << ": " << line << "\n";

        cout << n << " line(s) copied from in.txt to out.txt" << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Records into objects: store name, marks pairs in a file, read them back into an array of Student objects, and print the topper.
// ---------------------------------------------------------------
namespace diy3 {
    class Student {
    public:
        string name;
        int marks;
    };

    int run() {
        // --- store name, marks pairs in a file ---
        ofstream out("records.txt");
        out << "Asha 91\n" << "Ravi 78\n" << "Meera 88\n" << "Kiran 95\n" << "Divya 82\n";
        out.close();

        // --- read them back into an array of Student objects ---
        ifstream in("records.txt");
        if (!in) { cerr << "Cannot open records.txt" << endl; return 1; }

        Student s[10];
        int n = 0;
        while (n < 10 && in >> s[n].name >> s[n].marks)
            ++n;

        cout << "Records read: " << n << endl;
        for (int i = 0; i < n; ++i)
            cout << "  " << s[i].name << " - " << s[i].marks << endl;

        // --- find the topper ---
        int top = 0;
        for (int i = 1; i < n; ++i)
            if (s[i].marks > s[top].marks) top = i;

        cout << "Topper: " << s[top].name << " with " << s[top].marks << " marks" << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 10 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
