#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

double sequence(const string &x, const string &y);
double sequenceH(const string &x, const string &y, unsigned int i, unsigned int j, vector<vector<double>> &scores);
void print2dvec(const vector<vector<double>> &vec);

const double MATCH = 1.0;
const double DELETE = -0.2;
const double INSERT = -0.2;
const double SUB = -0.1; // G<->A, C<->A, G<->T, C<->T
const double ALT_SUB = -0.15; // C<->G, T<->A
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

    cout << "lmfao: \n" << sequence(x, y) << endl;
    return 0;
}

// find the sequence similarity score of two strings of characters
// FIXME: does not work for long strings (len greater than 5 💀)
// sequence h means sequence helper btw
double sequenceH(const string &x, const string &y, unsigned int i, unsigned int j, vector<vector<double>> &scores) {
    // cout << "xAT: " << x.at(i) << "\tyAT: " << y.at(j) << endl;
    if (scores.at(j).at(i) != -0.01) { // -0.01 is the value we initialized the empty 2d vector to, it's our filler value to indicate that space hasn't been filled in yet
        return scores.at(j).at(i);
    }
    else if (i == 0) {
        scores.at(j).at(0) = j*DELETE; // on the first row, so there's only deletions left
        //return scores.at(j).at(0);
    }
    else if (j == 0) {
        scores.at(0).at(i) = i*INSERT; // on the first column, so there's only insertions left
        //return scores.at(0).at(i); 
    }

    else if (x.at(i) == y.at(j)) { // same character at i and j (match)
        scores.at(j).at(i) = sequenceH(x, y, i-1, j-1, scores) + MATCH;
        //return scores.at(j).at(i);
    }
    
    else { // different character at i and j, assign this value in the array to the minimum of sub insert and delete
        scores.at(j).at(i) = max({sequenceH(x, y, i-1, j-1, scores) + SUB, 
                                    sequenceH(x, y, i, j-1, scores) + INSERT,
                                    sequenceH(x, y, i-1, j, scores) + DELETE});
    }
    return scores.at(i).at(j);
}

double sequence(const string &x, const string &y) {
    // declare a vector of vectors, outside vector (column) holds x scores, each element of outside vector is a vector of length y.size, with each value initialized to -0.01
    // initialize to -0.01 because that is impossible to get from adding in any combination/order the score values we have.
    // first index is the row, second index is the column
    vector<vector<double>> scores( y.size(), vector<double>(x.size(), -0.01) ); 
    //double scores[y.size()][x.size()];
    // for (unsigned j = 0; j < y.size(); j++) {
    //     for (unsigned i = 0; i < x.size(); i++) {
    //         scores[j][i] = -0.01;
    //     }
    // }
    double returnval = sequenceH(x, y, x.size() - 1, y.size() - 1, scores);
    print2dvec(scores);
    return returnval;
}

void print2dvec(const vector<vector<double>> &vec) {
    for (unsigned j = 0; j < vec.at(0).size(); j++) {
        for (unsigned i = 0; i < vec.size(); i++) {
            cout << vec.at(i).at(j) << " ";
        }
        cout << "\n";
    }
}

// void print2darray(const double &arr) {

// }

// old sequence function algorithm
// double sequence(const string x, const string y, unsigned int i, unsigned int j) {
//     // cout << "xAT: " << x.at(i) << "\tyAT: " << y.at(j) << endl;
//     if (i == -1 && j == -1) { // use -1 instead of 0 because strings are 0-indexed
//         return 0;
//     }
//     else if (j == -1) {
//         return sequence(x, y, i-1, -1) + del;
//     }
//     else if (i == -1) {
//         return sequence(x, y, -1, j-1) + del;
//     }
//     double temp;
//     if (x.at(i) == y.at(j)) {
//         temp = match; // we have a match
//     }
//     else {
//         temp = sub;
//     }
    
//     return max({sequence(x, y, i-1, j-1) + temp, sequence(x, y, i-1, j) + del, sequence(x, y,i, j-1) + del});
// }