// Experiment 7 (Week 7) - DIY programs: Inheritance
// Compile: g++ week07_diy.cpp -o week07_diy

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Employee hierarchy: base Employee (name, id); derive Manager (adds team size) and Engineer (adds skill); print details of each.
// ---------------------------------------------------------------
namespace diy1 {
    class Employee {
    protected:
        string name;
        int id;

    public:
        Employee(string n, int i) : name(n), id(i) {}

        void display() const {
            cout << "Name: " << name << ", ID: " << id;
        }
    };

    class Manager : public Employee {
        int teamSize;

    public:
        Manager(string n, int i, int t) : Employee(n, i), teamSize(t) {}

        void display() const {
            Employee::display();
            cout << ", Team size: " << teamSize << endl;
        }
    };

    class Engineer : public Employee {
        string skill;

    public:
        Engineer(string n, int i, string s) : Employee(n, i), skill(s) {}

        void display() const {
            Employee::display();
            cout << ", Skill: " << skill << endl;
        }
    };

    int run() {
        Manager  m("Anita Rao", 101, 8);
        Engineer e("Kiran Shetty", 202, "Embedded C++");

        cout << "--- Manager ---" << endl;
        m.display();
        cout << "--- Engineer ---" << endl;
        e.display();
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Multilevel shapes: Shape -> Polygon -> Rectangle; each level adds one field; demonstrate the constructor call order with print statements.
// ---------------------------------------------------------------
namespace diy2 {
    class Shape {                                   // level 1 : adds 'name'
    protected:
        string name;

    public:
        Shape(string n) : name(n) { cout << "Shape constructor     (name = " << name << ")" << endl; }
        ~Shape()                  { cout << "Shape destructor" << endl; }
    };

    class Polygon : public Shape {                  // level 2 : adds 'sides'
    protected:
        int sides;

    public:
        Polygon(string n, int s) : Shape(n), sides(s) {
            cout << "Polygon constructor   (sides = " << sides << ")" << endl;
        }
        ~Polygon() { cout << "Polygon destructor" << endl; }
    };

    class Rectangle : public Polygon {              // level 3 : adds 'area'
        double area;

    public:
        Rectangle(double a) : Polygon("Rectangle", 4), area(a) {
            cout << "Rectangle constructor (area = " << area << ")" << endl;
        }
        ~Rectangle() { cout << "Rectangle destructor" << endl; }

        void display() const {
            cout << name << " has " << sides << " sides and area " << area << endl;
        }
    };

    int run() {
        cout << "Creating object..." << endl;
        {
            Rectangle r(24.5);
            r.display();
            cout << "Leaving block..." << endl;
        }
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Resolve a diamond: build Person -> Student, Person -> Employee, then TA (teaching assistant) inheriting both; use a virtual base so Person appears once.
// ---------------------------------------------------------------
namespace diy3 {
    class Person {
    protected:
        string name;

    public:
        Person(string n = "Unknown") : name(n) {
            cout << "Person constructor  (" << name << ")" << endl;
        }
    };

    class Student : virtual public Person {          // virtual base
    public:
        Student(string n) : Person(n) { cout << "Student constructor" << endl; }
    };

    class Employee : virtual public Person {         // virtual base
    public:
        Employee(string n) : Person(n) { cout << "Employee constructor" << endl; }
    };

    class TA : public Student, public Employee {
    public:
        // with a virtual base, the MOST DERIVED class initialises Person
        TA(string n) : Person(n), Student(n), Employee(n) {
            cout << "TA constructor" << endl;
        }

        void show() const { cout << "TA name: " << name << endl; }   // no ambiguity
    };

    int run() {
        TA t("Rahul");
        t.show();
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 7 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
