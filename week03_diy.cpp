// Experiment 3 (Week 3) - DIY programs: Classes and Objects
// Compile: g++ week03_diy.cpp -o week03_diy

#include <iostream>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Rectangle Class: Create a class with private length and width, public setters with validation to reject negative values, and area() and perimeter() getter functions.
// ---------------------------------------------------------------
namespace diy1 {
    class Rectangle {
    private:
        double length, width;

    public:
        Rectangle() : length(0), width(0) {}

        bool setLength(double l) {           // validation: reject negative values
            if (l < 0) {
                cout << "Error: length cannot be negative" << endl;
                return false;
            }
            length = l;
            return true;
        }

        bool setWidth(double w) {
            if (w < 0) {
                cout << "Error: width cannot be negative" << endl;
                return false;
            }
            width = w;
            return true;
        }

        double area() const      { return length * width; }
        double perimeter() const { return 2 * (length + width); }
    };

    int run() {
        Rectangle r;
        double l, w;

        cout << "Enter length: ";
        cin >> l;
        cout << "Enter width : ";
        cin >> w;

        r.setLength(l);
        r.setWidth(w);

        cout << "Area      = " << r.area() << endl;
        cout << "Perimeter = " << r.perimeter() << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Counter Array: Create a Counter class with increment(), reset() and get() functions. Create an array of 3 Counter objects and perform operations on them.
// ---------------------------------------------------------------
namespace diy2 {
    class Counter {
        int count;

    public:
        Counter() : count(0) {}
        void increment() { ++count; }
        void reset()     { count = 0; }
        int  get() const { return count; }
    };

    int run() {
        Counter c[3];                         // array of 3 Counter objects

        for (int i = 0; i < 3; ++i) c[0].increment();   // counter 0 -> 3
        c[1].increment();                               // counter 1 -> 1
        for (int i = 0; i < 5; ++i) c[2].increment();   // counter 2 -> 5

        cout << "Before reset:" << endl;
        for (int i = 0; i < 3; ++i)
            cout << "  Counter[" << i << "] = " << c[i].get() << endl;

        c[2].reset();                                   // reset only the last one

        cout << "After resetting Counter[2]:" << endl;
        for (int i = 0; i < 3; ++i)
            cout << "  Counter[" << i << "] = " << c[i].get() << endl;

        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Complex Number Class: Create a class to store real and imag values. Provide setData() and display() functions, and print a small array of complex numbers.
// ---------------------------------------------------------------
namespace diy3 {
    class Complex {
        double real, imag;

    public:
        void setData(double r, double i) {
            real = r;
            imag = i;
        }

        void display() const {
            cout << real << (imag >= 0 ? " + " : " - ")
                 << (imag >= 0 ? imag : -imag) << "i" << endl;
        }
    };

    int run() {
        Complex arr[3];                       // small array of complex numbers

        arr[0].setData(3, 4);
        arr[1].setData(-1.5, 2);
        arr[2].setData(7, -5);

        for (int i = 0; i < 3; ++i) {
            cout << "arr[" << i << "] = ";
            arr[i].display();
        }
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 3 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
