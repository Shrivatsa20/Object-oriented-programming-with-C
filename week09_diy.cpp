// Experiment 9 (Week 9) - DIY programs: Exception Handling
// Compile: g++ week09_diy.cpp -o week09_diy
// Note: DIY 3 (catch order): build with -Wall ; add -DWRONG_ORDER for the wrong handler order.

#include <iostream>
#include <exception>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Safe withdrawal: extend the Week-3 BankAccount to throw a custom InsufficientFunds exception instead of returning false.
// ---------------------------------------------------------------
namespace diy1 {
    class InsufficientFunds : public exception {
        double balance, requested;

    public:
        InsufficientFunds(double b, double r) : balance(b), requested(r) {}
        const char *what() const noexcept override { return "Insufficient funds"; }
        double getBalance()   const { return balance; }
        double getRequested() const { return requested; }
    };

    class BankAccount {
        double balance;

    public:
        BankAccount(double b) : balance(b) {}

        void deposit(double amt) { if (amt > 0) balance += amt; }

        void withdraw(double amt) {
            if (amt > balance)
                throw InsufficientFunds(balance, amt);   // instead of returning false
            balance -= amt;
        }

        double getBalance() const { return balance; }
    };

    int run() {
        BankAccount acc(1000);

        try {
            acc.withdraw(300);
            cout << "Withdrew 300, balance = " << acc.getBalance() << endl;

            acc.withdraw(2000);                          // too much -> exception
            cout << "This line is never reached" << endl;
        }
        catch (const InsufficientFunds &e) {
            cout << "Error: " << e.what() << " (balance " << e.getBalance()
                 << ", requested " << e.getRequested() << ")" << endl;
        }

        acc.deposit(500);
        cout << "Balance after deposit = " << acc.getBalance() << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Stack over/underflow: give your Week-4 Stack custom Overflow and Underflow exceptions and handle them in main.
// ---------------------------------------------------------------
namespace diy2 {
    class Overflow : public exception {
    public:
        const char *what() const noexcept override { return "Stack overflow: stack is full"; }
    };

    class Underflow : public exception {
    public:
        const char *what() const noexcept override { return "Stack underflow: stack is empty"; }
    };

    class Stack {
        int arr[3];                                  // small capacity to force overflow
        int top = -1;

    public:
        void push(int x) {
            if (top == 2) throw Overflow();
            arr[++top] = x;
        }

        int pop() {
            if (top < 0) throw Underflow();
            return arr[top--];
        }
    };

    int run() {
        Stack s;

        try {
            for (int i = 1; i <= 4; ++i) {
                s.push(i * 10);
                cout << "pushed " << i * 10 << endl;
            }
        }
        catch (const Overflow &e) {
            cout << "Caught: " << e.what() << endl;
        }

        try {
            for (int i = 1; i <= 4; ++i) {
                int v = s.pop();                 // throws on the 4th pop
                cout << "popped " << v << endl;
            }
        }
        catch (const Underflow &e) {
            cout << "Caught: " << e.what() << endl;
        }
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Ordering demo: define MathError and a derived DivideByZero; show that catching MathError first hides DivideByZero, then fix the order.
// ---------------------------------------------------------------
namespace diy3 {
    class MathError : public exception {             // base exception
    public:
        const char *what() const noexcept override { return "MathError"; }
    };

    class DivideByZero : public MathError {          // derived exception
    public:
        const char *what() const noexcept override { return "DivideByZero"; }
    };

    double divide(double a, double b) {
        if (b == 0) throw DivideByZero();
        return a / b;
    }

    int run() {
        try {
            divide(10, 0);
        }
#ifdef WRONG_ORDER
        catch (const MathError &e) {                 // base first: it catches EVERYTHING derived
            cout << "MathError handler ran  -> " << e.what() << endl;
        }
        catch (const DivideByZero &e) {              // never reached
            cout << "DivideByZero handler ran -> " << e.what() << endl;
        }
#else
        catch (const DivideByZero &e) {              // most specific (derived) first
            cout << "DivideByZero handler ran -> " << e.what() << endl;
        }
        catch (const MathError &e) {                 // general (base) last
            cout << "MathError handler ran  -> " << e.what() << endl;
        }
#endif
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 9 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
