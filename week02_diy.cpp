// Experiment 2 (Week 2) - DIY programs: Function Overloading, Default Arguments and Inline Functions
// Compile: g++ week02_diy.cpp -o week02_diy

#include <iostream>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Overloaded Volume: Write three overloaded functions to compute the volume of: Cube (1 argument), Cuboid (3 arguments) and Cylinder (2 arguments: radius and height).
// ---------------------------------------------------------------
namespace diy1 {
    const double PI = 3.14159;

    double volume(double side)                       // cube      : 1 argument
    {
        return side * side * side;
    }

    double volume(double l, double b, double h)      // cuboid    : 3 arguments
    {
        return l * b * h;
    }

    double volume(double r, double h)                // cylinder  : 2 arguments
    {
        return PI * r * r * h;
    }

    int run() {
        cout << "Cube     (side=4)           : " << volume(4.0) << endl;
        cout << "Cuboid   (5 x 3 x 2)        : " << volume(5.0, 3.0, 2.0) << endl;
        cout << "Cylinder (radius=3, h=10)   : " << volume(3.0, 10.0) << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Default-Argument Calculator: Write power(int base, int exp = 2) such that power(5) gives 25 and power(2,10) gives 1024.
// ---------------------------------------------------------------
namespace diy2 {
    // 'exp' defaults to 2, so power(5) means 5 squared
    int power(int base, int exp = 2) {
        int result = 1;
        for (int i = 0; i < exp; ++i)
            result *= base;
        return result;
    }

    int run() {
        cout << "power(5)     = " << power(5) << endl;        // default exponent
        cout << "power(2,10)  = " << power(2, 10) << endl;    // exponent supplied
        cout << "power(3,4)   = " << power(3, 4) << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Inline Min: Write an inline overloaded minVal function that returns the smaller of two integers and, using a second overload, the smallest of three integers.
// ---------------------------------------------------------------
namespace diy3 {
    // smaller of two integers
    inline int minVal(int a, int b) {
        return (a < b) ? a : b;
    }

    // overload: smallest of three integers (re-uses the two-argument version)
    inline int minVal(int a, int b, int c) {
        return minVal(minVal(a, b), c);
    }

    int run() {
        cout << "minVal(8, 3)      = " << minVal(8, 3) << endl;
        cout << "minVal(12, 5, 9)  = " << minVal(12, 5, 9) << endl;
        cout << "minVal(7, 7, 2)   = " << minVal(7, 7, 2) << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 2 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
