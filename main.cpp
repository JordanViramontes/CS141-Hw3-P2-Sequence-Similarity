#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

double sequence(const string x, const string y, unsigned int i, unsigned int j);

double match = 1;
double del = -0.2;
double sub = -0.15;
// double match = 1;
// double del = -2;
// double sub = -1;


int main() {
    // string x = "AACCTGACAT";
    // string y = "CCAGCGTCAA";
    string x = "GTG";
    string y = "AGC";
    unsigned int xMAX = x.size()-1;
    unsigned int yMAX = y.size()-1;

    // cout << x.at(xMAX) << "\t" << y.at(yMAX) << endl;

    cout << "lmfao: " << sequence(x, y, xMAX, yMAX) << endl;
    return 0;
}

double sequence(const string x, const string y, unsigned int i, unsigned int j) {
    // cout << "xAT: " << x.at(i) << "\tyAT: " << y.at(j) << endl;
    if (i == -1 && j == -1) {
        return 0;
    }
    else if (j == -1) {
        return sequence(x, y, i-1, -1) + del;
    }
    else if (i == -1) {
        return sequence(x, y, -1, j-1) + del;
    }

    double temp;
    if (x.at(i) == y.at(j)) {
        temp = match; //we have a match
    }
    else {
        temp = sub;
    }
    
    return max({sequence(x, y, i-1, j-1) + temp, sequence(x, y, i-1, j) + del, sequence(x, y,i, j-1) + del});
}