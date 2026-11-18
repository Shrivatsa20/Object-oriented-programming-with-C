// Experiment 5 (Week 5) - DIY programs: Static Members and Friend Functions
// Compile: g++ week05_diy.cpp -o week05_diy

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Object Counter: Add a static member to your Week-3 Counter class that reports how many Counter objects have ever been created and how many are currently alive.
// ---------------------------------------------------------------
namespace diy1 {
    class Counter {
        int v;
        static int created;                  // objects ever created
        static int alive;                    // objects currently alive

    public:
        Counter() : v(0)          { ++created; ++alive; }
        Counter(const Counter &o) : v(o.v) { ++created; ++alive; }   // copies count too
        ~Counter()                { --alive; }

        void increment() { ++v; }
        int  get() const { return v; }

        static int totalCreated()     { return created; }
        static int currentlyAlive()   { return alive; }
    };

    int Counter::created = 0;                // definition of the static members
    int Counter::alive   = 0;

    void report(const char *when) {
        cout << when << ": created = " << Counter::totalCreated()
             << ", alive = " << Counter::currentlyAlive() << endl;
    }

    int run() {
        Counter a, b;
        report("After a, b");

        {
            Counter c;
            Counter d = c;                   // copy constructor
            report("Inside block (c, d)");
        }                                    // c and d are destroyed here

        report("After block");
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Friend Comparison: Write a Time class (hh:mm) and a friend function laterOf(Time, Time) returning the later of two times.
// ---------------------------------------------------------------
namespace diy2 {
    class Time {
        int hh, mm;                          // private

    public:
        Time(int h = 0, int m = 0) : hh(h), mm(m) {}

        void show() const {
            cout << setfill('0') << setw(2) << hh << ":" << setw(2) << mm << endl;
        }

        friend Time laterOf(Time a, Time b); // friend can read hh and mm directly
    };

    Time laterOf(Time a, Time b) {
        if (a.hh != b.hh) return (a.hh > b.hh) ? a : b;
        return (a.mm >= b.mm) ? a : b;
    }

    int run() {
        int h1, m1, h2, m2;

        cout << "Enter first time  (hh mm): ";
        cin >> h1 >> m1;
        cout << "Enter second time (hh mm): ";
        cin >> h2 >> m2;

        Time t1(h1, m1), t2(h2, m2);
        cout << "Later time is: ";
        laterOf(t1, t2).show();
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Unique ID Factory: Use a static member so every new Order object automatically receives the next ID (1001, 1002, ...) in its constructor.
// ---------------------------------------------------------------
namespace diy3 {
    class Order {
        int id;
        string item;
        static int nextId;                   // shared by all Order objects

    public:
        Order(const string &it) : id(nextId++), item(it) {}   // next ID assigned automatically

        void show() const {
            cout << "Order ID " << id << " -> " << item << endl;
        }
    };

    int Order::nextId = 1001;                // first order gets 1001

    int run() {
        Order o1("Keyboard");
        Order o2("Mouse");
        Order o3("Monitor");
        Order o4("Webcam");

        o1.show();
        o2.show();
        o3.show();
        o4.show();
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 5 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
