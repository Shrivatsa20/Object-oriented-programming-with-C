// Experiment 8 (Week 8) - DIY programs: Polymorphism and Virtual Functions
// Compile: g++ week08_diy.cpp -o week08_diy
// Note: DIY 3 (virtual destructor bug): build with -fsanitize=address -g ; add -DFIX for the fixed version.

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Abstract Account: pure-virtual calculateInterest(); derive Savings and Current with different rates; process an array of Account*.
// ---------------------------------------------------------------
namespace diy1 {
    class Account {
    protected:
        double balance;

    public:
        Account(double b) : balance(b) {}
        virtual double calculateInterest() const = 0;   // pure virtual -> abstract class
        virtual string type() const = 0;
        double getBalance() const { return balance; }
        virtual ~Account() {}
    };

    class Savings : public Account {
    public:
        Savings(double b) : Account(b) {}
        double calculateInterest() const override { return balance * 0.04; }   // 4 %
        string type() const override { return "Savings"; }
    };

    class Current : public Account {
    public:
        Current(double b) : Account(b) {}
        double calculateInterest() const override { return balance * 0.01; }   // 1 %
        string type() const override { return "Current"; }
    };

    int run() {
        Account *accts[] = { new Savings(50000), new Current(20000), new Savings(75000) };

        for (Account *a : accts)
            cout << a->type() << " account: balance = " << a->getBalance()
                 << ", yearly interest = " << a->calculateInterest() << endl;

        for (Account *a : accts) delete a;               // virtual destructor -> safe
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Polymorphic logger: abstract Logger with write(string); derive ConsoleLogger and FileLogger; switch at run time.
// ---------------------------------------------------------------
namespace diy2 {
    class Logger {
    public:
        virtual void write(const string &msg) = 0;
        virtual ~Logger() {}
    };

    class ConsoleLogger : public Logger {
    public:
        void write(const string &msg) override {
            cout << "[CONSOLE] " << msg << endl;
        }
    };

    class FileLogger : public Logger {
        ofstream out;
    public:
        FileLogger(const string &file) : out(file, ios::app) {}
        void write(const string &msg) override {
            out << "[FILE] " << msg << endl;
            cout << "(written to file)" << endl;
        }
    };

    int run() {
        Logger *log = nullptr;
        int choice;

        while (true) {
            cout << "Select logger (1=Console, 2=File, 0=Exit): ";
            cin >> choice;
            if (choice == 0) break;

            delete log;                                       // switch logger at run time
            if (choice == 1)      log = new ConsoleLogger();
            else if (choice == 2) log = new FileLogger("app.log");
            else { cout << "Invalid choice" << endl; log = nullptr; continue; }

            log->write("message sent through logger " + to_string(choice));
        }

        delete log;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Prove the bug: build a Base/Derived pair where Derived allocates memory; show the leak when the destructor is not virtual, then fix it (use g++ -fsanitize=address).
// ---------------------------------------------------------------
namespace diy3 {
    class Base {
    public:
#ifdef FIX
        virtual ~Base() { cout << "Base destructor" << endl; }     // fixed version
#else
        ~Base()         { cout << "Base destructor" << endl; }     // BUG: not virtual
#endif
    };

    class Derived : public Base {
        int *buf;

    public:
        Derived() {
            buf = new int[100];                 // Derived owns heap memory
            cout << "Derived: buffer allocated" << endl;
        }
        ~Derived() {
            delete[] buf;
            cout << "Derived: buffer released" << endl;
        }
    };

    int run() {
        Base *p = new Derived();                // base pointer -> derived object
        delete p;                               // which destructor runs?
        cout << "Done" << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 8 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
