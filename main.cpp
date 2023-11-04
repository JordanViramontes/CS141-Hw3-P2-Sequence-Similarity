#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

const vector<char> CHARACTERS = {'A', 'G', 'C', 'T'};

string generateRandomString(const unsigned int);

int main() {
    srand(time(0));

    int n = 100;
    string x = generateRandomString(n);
    string y = generateRandomString(n);

    // cout << "x:\t" << x << "\n";
    // cout << "y:\t" << y << "\n";

    return 0;
}

// generate random string of length n that consists of characters in the set {A, G, C, T}
string generateRandomString(const unsigned int n) {
    string s;
    for (unsigned int i = 0; i < n; i++) {
        // push back to the string a random character in CHARACTERS
        s.push_back(CHARACTERS.at(rand() % 3));
    }
    return s;
}