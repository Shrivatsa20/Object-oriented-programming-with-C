// Experiment 1 (Week 1) - DIY programs: References, Pointers and String Handling in C++
// Compile: g++ week01_diy.cpp -o week01_diy

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

// ---------------------------------------------------------------
// DIY 1: Vowel & Consonant Counter: Read a sentence using getline(cin, s) and print the number of vowels and consonants.
// ---------------------------------------------------------------
namespace diy1 {
    int run() {
        string s;
        cout << "Enter a sentence: ";
        getline(cin, s);                      // reads the whole line, spaces included

        int vowels = 0, consonants = 0;

        for (char ch : s) {
            if (isalpha((unsigned char)ch)) { // ignore spaces, digits, punctuation
                char c = tolower(ch);
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
                    vowels++;
                else
                    consonants++;
            }
        }

        cout << "Vowels     : " << vowels << endl;
        cout << "Consonants : " << consonants << endl;
        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 2: Anagram Test: Read two words and determine whether one is an anagram of the other. (Hint: use character frequency counting or sort both words.)
// ---------------------------------------------------------------
namespace diy2 {
    // Lower-case the word and sort its letters; anagrams give the same result
    string normalise(string w) {
        for (char &c : w) c = tolower((unsigned char)c);
        sort(w.begin(), w.end());
        return w;
    }

    int run() {
        string a, b;

        cout << "Enter first word  : ";
        cin >> a;
        cout << "Enter second word : ";
        cin >> b;

        if (normalise(a) == normalise(b))
            cout << a << " and " << b << " are anagrams" << endl;
        else
            cout << a << " and " << b << " are NOT anagrams" << endl;

        return 0;
    }
}

// ---------------------------------------------------------------
// DIY 3: Reverse the Words: Read a sentence such as "hello world cpp" and print "cpp world hello". Reverse only the word order, not the characters.
// ---------------------------------------------------------------
namespace diy3 {
    int run() {
        string line, w;
        cout << "Enter a sentence: ";
        getline(cin, line);

        vector<string> words;
        stringstream ss(line);
        while (ss >> w)                       // split the line into words
            words.push_back(w);

        cout << "Reversed order : ";
        for (int i = (int)words.size() - 1; i >= 0; --i) {
            cout << words[i];                 // characters inside a word stay as they are
            if (i > 0) cout << " ";
        }
        cout << endl;
        return 0;
    }
}

int main() {
    int choice;
    cout << "Week 1 DIY - choose 1, 2, 3 (0 = run all): ";
    cin >> choice;
    cin.ignore(10000, '\n');
    if (choice == 1 || choice == 0) { cout << "\n--- DIY 1 ---" << endl; diy1::run(); }
    if (choice == 2 || choice == 0) { cout << "\n--- DIY 2 ---" << endl; diy2::run(); }
    if (choice == 3 || choice == 0) { cout << "\n--- DIY 3 ---" << endl; diy3::run(); }
    return 0;
}
