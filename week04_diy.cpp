// Experiment 4 (Week 4) - DIY programs: Constructors, Destructors and Dynamic Memory
// Compile: g++ week04_diy.cpp -o week04_diy
// Note: DIY 3 (lifetime logger): build with -fsanitize=address -g ; add -DNO_DELETE to see the leak.

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Dynamic Matrix: a Matrix class that allocates an m x n grid with new, provides a deep copy constructor, and frees it in the destructor.
// ---------------------------------------------------------------
namespace diy1 {
    class Matrix {
        int rows, cols;
        int **data;

    public:
        Matrix(int r, int c) : rows(r), cols(c) {
            data = new int*[rows];                       // allocate m rows
            for (int i = 0; i < rows; ++i) {
                data[i] = new int[cols];                 // allocate n columns per row
                for (int j = 0; j < cols; ++j) data[i][j] = 0;
            }
        }

        Matrix(const Matrix &o) : rows(o.rows), cols(o.cols) {   // DEEP copy constructor
            data = new int*[rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; ++j) data[i][j] = o.data[i][j];
            }
        }

        ~Matrix() {                                      // release every row, then the array of rows
            for (int i = 0; i < rows; ++i) delete[] data[i];
            delete[] data;
            cout << "Matrix " << rows << "x" << cols << " freed" << endl;
        }

        void set(int i, int j, int v) { data[i][j] = v; }

        void print(const string &name) const {
            cout << name << ":" << endl;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) cout << "  " << data[i][j];
                cout << endl;
            }
        }
    };

    int run() {
        Matrix a(2, 3);
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 3; ++j)
                a.set(i, j, i * 3 + j + 1);

        Matrix b = a;                    // copy constructor -> independent copy
        b.set(0, 0, 99);                 // change only the copy

        a.print("Matrix a (original)");
        b.print("Matrix b (copy, element [0][0] changed)");
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Stack with destructor: an integer Stack backed by a dynamic array; push/pop plus a destructor that releases the buffer.
// ---------------------------------------------------------------
namespace diy2 {
    class Stack {
        int *arr;                                 // dynamic buffer
        int top, cap;

    public:
        Stack(int c) : top(-1), cap(c) {
            arr = new int[cap];
            cout << "Stack created (capacity " << cap << ")" << endl;
        }

        Stack(const Stack &) = delete;            // copying would cause a double delete
        Stack &operator=(const Stack &) = delete;

        ~Stack() {
            delete[] arr;                         // destructor releases the buffer
            cout << "Stack buffer released" << endl;
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
        s.push(40);                               // exceeds capacity

        while (s.pop(v))
            cout << "popped " << v << endl;

        return 0;                                 // destructor runs here
    }
}

// ---------------------------------------------------------------
// DIY 3: Lifetime logger: extend Program 4.1 so each Tracer is created with new inside a loop and deleted; observe how forgetting delete leaks (run with g++ -fsanitize=address).
// ---------------------------------------------------------------
namespace diy3 {
    class Tracer {
        int id;

    public:
        Tracer(int i) : id(i) { cout << "Construct #" << id << endl; }
        ~Tracer()             { cout << "Destruct #" << id << endl; }
    };

    int run() {
        for (int i = 1; i <= 3; ++i) {
            Tracer *t = new Tracer(i);       // object created on the heap inside the loop
#ifndef NO_DELETE
            delete t;                        // normal build: every object is deleted
#endif                                   // -DNO_DELETE build: the delete is "forgotten"
        }
        cout << "Loop finished" << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 4 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
