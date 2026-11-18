// Experiment 13 (Week 13) - DIY programs: Smart Pointers, Design Patterns and Multithreading
// Compile: g++ week13_diy.cpp -o week13_diy
// Note: Build with -pthread. DIY 3 (race): add -DNO_LOCK to remove the lock_guard.

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Raw to smart: take any Week-4 program that used new/delete and rewrite it with unique_ptr so no explicit delete remains.
// ---------------------------------------------------------------
namespace diy1 {
    // Week-4 Stack rewritten with unique_ptr: no new, no delete, no destructor needed
    class Stack {
        unique_ptr<int[]> arr;               // owns the buffer, frees it automatically
        int top, cap;

    public:
        Stack(int c) : arr(make_unique<int[]>(c)), top(-1), cap(c) {
            cout << "Stack created (capacity " << cap << ")" << endl;
        }

        bool push(int x) {
            if (top == cap - 1) { cout << "Stack full, cannot push " << x << endl; return false; }
            arr[++top] = x;
            return true;
        }

        bool pop(int &x) {
            if (top < 0) { cout << "Stack empty" << endl; return false; }
            x = arr[top--];
            return true;
        }
    };

    int run() {
        Stack s(3);
        int v;

        s.push(10);
        s.push(20);
        s.push(30);
        s.push(40);                          // exceeds capacity

        while (s.pop(v))
            cout << "popped " << v << endl;

        cout << "End of main - buffer freed automatically" << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Shape factory v2: extend Program 13.1 with a Triangle and let the user type the shape name at run time; store the created shapes in a vector<unique_ptr<Shape>>.
// ---------------------------------------------------------------
namespace diy2 {
    struct Shape {
        virtual double area() const = 0;
        virtual string name() const = 0;
        virtual ~Shape() {}
    };

    struct Circle : Shape {
        double r;
        Circle(double r) : r(r) {}
        double area() const override { return 3.14159 * r * r; }
        string name() const override { return "Circle"; }
    };

    struct Square : Shape {
        double s;
        Square(double s) : s(s) {}
        double area() const override { return s * s; }
        string name() const override { return "Square"; }
    };

    struct Triangle : Shape {                          // new shape added in v2
        double b, h;
        Triangle(double b, double h) : b(b), h(h) {}
        double area() const override { return 0.5 * b * h; }
        string name() const override { return "Triangle"; }
    };

    // Factory: the shape name typed by the user decides which object is created
    unique_ptr<Shape> makeShape(const string &kind) {
        if (kind == "circle")   return make_unique<Circle>(2.0);
        if (kind == "square")   return make_unique<Square>(3.0);
        if (kind == "triangle") return make_unique<Triangle>(3.0, 4.0);
        return nullptr;                                // unknown name
    }

    int run() {
        vector<unique_ptr<Shape>> shapes;
        string kind;

        while (true) {
            cout << "Enter shape (circle/square/triangle, done to finish): ";
            cin >> kind;
            if (kind == "done") break;

            auto s = makeShape(kind);
            if (!s) { cout << "Unknown shape: " << kind << endl; continue; }
            shapes.push_back(move(s));                 // vector takes ownership
        }

        cout << "Shapes created: " << shapes.size() << endl;
        for (const auto &s : shapes)
            cout << "  " << s->name() << " area = " << s->area() << endl;

        return 0;                                      // vector frees every shape automatically
    }
}

// ---------------------------------------------------------------
// DIY 3: Prove the race: run Program 13.3 without the lock_guard, observe the wrong total over several runs, then restore the lock and confirm the expected total.
// ---------------------------------------------------------------
namespace diy3 {
    const int TIMES = 5000000;             // increments per thread (large enough for the threads to overlap)

    long counter = 0;
    mutex m;

    void addTask(int times) {
        for (int i = 0; i < times; ++i) {
#ifndef NO_LOCK
            lock_guard<mutex> lk(m);       // protected critical section
#endif
            ++counter;                     // with -DNO_LOCK this line is unprotected
        }
    }

    int run() {
        thread t1(addTask, TIMES);
        thread t2(addTask, TIMES);

        t1.join();
        t2.join();

        cout << "counter = " << counter
             << " (expected " << 2L * TIMES << ")" << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 13 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
