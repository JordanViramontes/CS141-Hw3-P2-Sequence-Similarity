#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

struct cell {
    double value = -0.01;
    bool diag = false;
    bool hor = false;
    bool ver = false;
};

double sequence(const string &x, const string &y);
double sequenceH(const string &x, const string &y,  int i,  int j, vector<vector<double>> &scores);
void print2dvec(const string &, const string &, const vector<vector<cell>> &vec);
void printStrings(const string &x, const string &y, string &xFin, string &yFin, int, int, const vector<vector<cell>> &vec);

const double MATCH = 1.0;
const double DELETE = -0.2;
const double INSERT = -0.2;
const double SUB = -0.1; // G<->A, C<->A, G<->T, C<->T
const double ALT_SUB = -0.15; // C<->G, T<->A



int main(int argc, char *argv[]) {
    string x, y;
    if (argc <= 1) {
        x = "";
        y = "";
    }
    else if (argc == 2) {
        x = argv[1];
        y = "";
    }
    else {
        x = argv[1];
        y = argv[2];
    }
    x = "GTACTCAG";
    y = "GGTACTAG";
    cout << "\nx: " << x << "\ty: " << y << endl;
    cout << sequence(x, y) << endl;
    return 0; 
}


// find the sequence similarity score of two strings of characters
// sequence h means sequence helper btw
double sequenceH(const string &x, const string &y,  int i,  int j, vector<vector<cell>> &scores) {
    // Base Cases:
    // On the first row and column, theres only deletions and insertions respectively, therefore it will always be -0.2
    if (scores.at(i).at(j).value != -0.01) return scores.at(i).at(j).value;
    else if (i == 0) {
        scores.at(0).at(j).value = j*DELETE;
        scores.at(0).at(j).ver = true;
    }
    else if (j == 0) {
        scores.at(i).at(0).value = i*INSERT;
        scores.at(i).at(0).hor = true;
    }
    else {
        double temp;
        char xAt = x.at(i-1);
        char yAt = y.at(j-1);
        if (xAt == yAt) temp = MATCH; //we have a match
        else {
            // if a case that has alt sub
            if ((xAt == 'A' && yAt == 'T') || (xAt == 'G' && yAt == 'C')
                || (yAt == 'A' && xAt == 'T') || (yAt == 'G' && xAt == 'C')) {
                temp = ALT_SUB;
            }
            // else sub
            else temp = SUB;
        } 
        scores.at(i).at(j).value = max({sequenceH(x, y, i-1, j-1, scores) + temp, 
                                  sequenceH(x, y, i, j-1, scores) + INSERT,
                                  sequenceH(x, y, i-1, j, scores) + DELETE});
        
        //update bools
        if (scores.at(i).at(j).value == scores.at(i-1).at(j-1).value + temp)    scores.at(i).at(j).diag = true;
        if (scores.at(i).at(j).value == scores.at(i-1).at(j).value + INSERT)    scores.at(i).at(j).hor = true;
        if (scores.at(i).at(j).value == scores.at(i).at(j-1).value + INSERT)    scores.at(i).at(j).ver = true;


    }
    return scores.at(i).at(j).value;
}

double sequence(const string &x, const string &y) {
    // declare a vector of vectors, outside vector (column) holds x scores, each element of outside vector is a vector of length y.size, with each value initialized to -0.01
    // initialize to -0.01 because that is impossible to get from adding in any combination/order the score values we have.
    // first index is the row, second index is the column

    // vector<vector<double>> scores( x.size()+1, vector<double>(y.size()+1, -0.01) ); 
    vector<vector<cell>> scores(x.size()+1, vector<cell>(y.size()+1));

    double returnval = sequenceH(x, y, x.size(), y.size(), scores);
    print2dvec(x, y, scores);
    string xFinal = "";
    string yFinal = "";
    printStrings(x, y, xFinal, yFinal, x.size(), y.size(), scores);

    cout << xFinal << endl << yFinal << endl;
    return returnval;
}

void print2dvec(const string &x, const string &y, const vector<vector<cell>> &vec) {
    //print the top
    for (unsigned int i = 0; i <  x.size(); i++) {
        if (i == 0) cout << "\t";
        cout << "\t" << x.at(i);
    }
    cout << endl;
    for (unsigned j = 0; j < vec.at(0).size(); j++) {
        if (j > 0) {
            cout << y.at(j-1) << "\t";
        }
        else cout << "\t";
        for (unsigned i = 0; i < vec.size(); i++) {
            // cout << "(" << i << "," << j << ")\t";
            if (vec.at(i).at(j).value < 0.01 && vec.at(i).at(j).value > -0.01) cout << "("<< "0.0" << ")\t";
            else cout << "("<< vec.at(i).at(j).value << ")\t";
        }
        cout << "\n";
    }

    cout << endl << "BOOLS (diag, hor, ver): " << endl;
    for (unsigned int i = 0; i <  x.size(); i++) {
        if (i == 0) cout << "\t";
        cout << "\t" << x.at(i);
    }
    cout << endl;
    for (unsigned j = 0; j < vec.at(0).size(); j++) {
        if (j > 0) {
            cout << y.at(j-1) << "\t";
        }
        else cout << "\t";
        for (unsigned i = 0; i < vec.size(); i++) {
            // cout << "(" << i << "," << j << ")\t";
            cout << vec.at(i).at(j).diag << vec.at(i).at(j).hor << vec.at(i).at(j).ver << "\t";
        }
        cout << "\n";
    }
}

void printStrings(const string &x, const string &y, string &xFin, string &yFin, int i, int j, const vector<vector<cell>> &vec) {
    //base cases
    if (i == 0 && j == 0) { //at (0,0)
        return;
    }
    else if (i == 0) { //vertical border
        cout << "i: " << i << "\tj: " << j << "\tvalue:" << vec.at(i).at(j).value << endl;
        xFin.insert(0, 1, '-');
        yFin.insert(0, 1, y.at(j));
        return printStrings(x, y, xFin, yFin, i, j-1, vec);
    }
    else if (j == 0) { //horizontal border
        xFin.insert(0, 1, x.at(i));
        yFin.insert(0, 1, '-');
        return printStrings(x, y, xFin, yFin, i-1, j, vec);
    }
    
    if (vec.at(i).at(j).diag) {
        xFin.insert(0, 1, x.at(i-1));
        yFin.insert(0, 1, y.at(j-1));
        return printStrings(x, y, xFin, yFin, i-1, j-1, vec);
    }
    else if (vec.at(i).at(j).hor) {
        xFin.insert(0, 1, x.at(i-2));
        yFin.insert(0, 1, '-');
        return printStrings(x, y, xFin, yFin, i-1, j, vec);
    }
    else if (vec.at(i).at(j).ver) {
        xFin.insert(0, 1, '-');
        yFin.insert(0, 1, y.at(j-2));
        return printStrings(x, y, xFin, yFin, i, j-1, vec);
    }
    return;
}
// original one by me joran times lmfao (super brute force and awful and terrible and clef made many improvements)
// double sequence(const string x, const string y, unsigned int i, unsigned int j) {
//     // cout << "xAT: " << x.at(i) << "\tyAT: " << y.at(j) << endl;
//     if (i == -1 && j == -1) return 0;
//     else if (j == -1) return sequence(x, y, i-1, -1) + del;
//     else if (i == -1) return sequence(x, y, -1, j-1) + del;

//     double temp;
//     char xAt = x.at(i);
//     char yAt = y.at(j);
    
//     if (xAt == yAt) temp = match; //we have a match
//     else {
//         //AT || GC = -0.15
//         //AG || AC || GT || CT = -0.1
//         if ((xAt == 'A' && yAt == 'T') || (xAt == 'G' && yAt == 'C')
//             || (yAt == 'A' && xAt == 'T') || (yAt == 'G' && xAt == 'C')) {
//             temp = sub_AT_GC;
//         }
//         else temp = sub_else;
//     } 
//     return max({sequence(x, y, i-1, j-1) + temp, sequence(x, y, i-1, j) + del, sequence(x, y,i, j-1) + del});
// }