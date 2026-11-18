// Experiment 6 (Week 6) - DIY programs: Operator Overloading
// Compile: g++ week06_diy.cpp -o week06_diy

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Money arithmetic: a Money class (rupees, paise); overload + and - with correct carry/borrow of paise into rupees.
// ---------------------------------------------------------------
namespace diy1 {
    class Money {
        long rupees;
        int  paise;

    public:
        Money(long r = 0, int p = 0) : rupees(r), paise(p) {
            if (paise >= 100) { rupees += paise / 100; paise %= 100; }
        }

        Money operator+(const Money &o) const {
            long r = rupees + o.rupees;
            int  p = paise + o.paise;
            if (p >= 100) { p -= 100; ++r; }          // carry 100 paise -> 1 rupee
            return Money(r, p);
        }

        Money operator-(const Money &o) const {
            long r = rupees - o.rupees;
            int  p = paise - o.paise;
            if (p < 0) { p += 100; --r; }             // borrow 1 rupee -> 100 paise
            if (r < 0) throw runtime_error("result would be negative");
            return Money(r, p);
        }

        friend ostream &operator<<(ostream &os, const Money &m) {
            os << "Rs. " << m.rupees << "." << setfill('0') << setw(2) << m.paise;
            return os;
        }
    };

    int run() {
        Money a(25, 75), b(10, 50);
        cout << a << " + " << b << " = " << (a + b) << "   (paise carry)" << endl;

        Money c(50, 20), d(19, 75);
        cout << c << " - " << d << " = " << (c - d) << "   (paise borrow)" << endl;

        try {
            Money e(5, 0), f(7, 50);
            Money g = e - f;                       // throws: 5.00 is less than 7.50
            cout << e << " - " << f << " = " << g << endl;
        }
        catch (const exception &ex) {
            cout << "Rs. 5.00 - Rs. 7.50 -> error: " << ex.what() << endl;
        }
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Fraction I/O: a Fraction class; overload << and >> and auto-simplify (divide by GCD) on construction.
// ---------------------------------------------------------------
namespace diy2 {
    int gcd(int a, int b) {                  // Euclid's algorithm
        return b == 0 ? a : gcd(b, a % b);
    }

    class Fraction {
        int num, den;

        void simplify() {
            if (den < 0) { num = -num; den = -den; }  // keep the sign in the numerator
            int g = gcd(abs(num), den);
            if (g > 1) { num /= g; den /= g; }        // divide by the GCD
        }

    public:
        Fraction(int n = 0, int d = 1) : num(n), den(d) {
            if (den == 0) den = 1;
            simplify();                               // auto-simplify on construction
        }

        friend istream &operator>>(istream &is, Fraction &f) {
            int n, d;
            char slash;
            is >> n >> slash >> d;                    // reads input like 12/18
            if (d == 0) {
                cout << "Denominator cannot be zero, using 1" << endl;
                d = 1;
            }
            f = Fraction(n, d);
            return is;
        }

        friend ostream &operator<<(ostream &os, const Fraction &f) {
            os << f.num << "/" << f.den;
            return os;
        }
    };

    int run() {
        Fraction f1, f2;

        cout << "Enter first fraction  (a/b): ";
        cin >> f1;
        cout << "Enter second fraction (a/b): ";
        cin >> f2;

        cout << "First  in lowest terms : " << f1 << endl;
        cout << "Second in lowest terms : " << f2 << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Safe array: a class wrapping a dynamic array; overload operator[] to throw / report an error on out-of-range access instead of corrupting memory.
// ---------------------------------------------------------------
namespace diy3 {
    class SafeArray {
        int *a;
        int n;

    public:
        SafeArray(int size) : n(size) { a = new int[n](); }   // () zero-initialises
        SafeArray(const SafeArray &) = delete;
        SafeArray &operator=(const SafeArray &) = delete;
        ~SafeArray() { delete[] a; }

        int &operator[](int i) {
            if (i < 0 || i >= n)                              // bounds check
                throw out_of_range("index " + to_string(i) + " is outside 0.." + to_string(n - 1));
            return a[i];
        }

        int size() const { return n; }
    };

    int run() {
        SafeArray arr(5);

        for (int i = 0; i < arr.size(); ++i)
            arr[i] = (i + 1) * 10;

        cout << "Array contents: ";
        for (int i = 0; i < arr.size(); ++i)
            cout << arr[i] << " ";
        cout << endl;

        try {
            cout << "Writing arr[7] = 100 ..." << endl;
            arr[7] = 100;                                     // out of range
        }
        catch (const out_of_range &e) {
            cout << "Error caught: " << e.what() << endl;
        }

        cout << "Program continues safely" << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 6 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
