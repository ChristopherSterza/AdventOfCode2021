#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

const int numBits = 12;

using namespace std;

// function headers
int partOne(vector<bitset<numBits> >, int);
int partTwo(vector<bitset<numBits> >, int);

int main(int argc, char** argv) {
    vector<bitset<numBits> > bitstrings;

    ifstream input(argv[1]);
    string tmp;
    int count = 0;

    while (input >> tmp) {
        bitstrings.push_back(bitset<numBits>(tmp));
        count++;
    }

    // Print results
    cout << "Part One Answer: " << partOne(bitstrings, count) << endl;
    //cout << "Part Two Answer: " << partTwo(dirs) << endl;
    return 0;
}

int partOne(vector<bitset<numBits> > bitstrings, int count) {
    // Array to track number of 0s in each position.
    int res[numBits] = { 0 };
    int gamma = 0;
    int epsilon = 0;
    for (vector<bitset<numBits> >::iterator it = bitstrings.begin(); it < bitstrings.end(); it++) {
        for (int i = 0; i < numBits; i++) {
            //test(i) reads the ith bit from the right. NOT LEFT.
            res[(numBits - 1) - i] += it->test(i);
        }
    }

    // Reduce the resulting array counts to either 0 or 1 if there are more 0s or 1s.
    for (int i = 0; i < numBits; i++) {
        (res[i] <= count / 2) ? res[i] = 0 : res[i] = 1;
    }

    // Convert array to decimal to return.
    for (int i = 0; i < numBits; i++) {
        gamma = gamma * 2 + res[i];
        epsilon = epsilon * 2 + (1 - res[i]);
    }
    return gamma * epsilon;
}

int partTwo(vector<bitset<numBits> > bitstrings, int count) {
    // Array to track number of 0s in each position.
    vector<bitset<numBits> > cpybitstrings = bitstrings;
    int res[numBits] = { 0 };
    int oxygen = 0;
    int carbonDioxide = 0;
    for (vector<bitset<numBits> >::iterator it = bitstrings.begin(); it < bitstrings.end(); it++) {
        for (int i = 0; i < numBits; i++) {
            //test(i) reads the ith bit from the right. NOT LEFT.
            res[(numBits - 1) - i] += it->test(i);
        }
    }

    // Reduce the resulting array counts to either 0 or 1 if there are more 0s or 1s.
    for (int i = 0; i < numBits; i++) {
        (res[i] <= count / 2) ? res[i] = 0 : res[i] = 1;
    }

    // Clear strings from the vector until oxygen string found
    for (int i = 0; i < numBits; i++) {
        for (vector<bitset<numBits> >::iterator it = bitstrings.begin(); it < bitstrings.end(); it++) {
            if (it->test((numBits - 1) - i) != res[i]) it = bitstrings.erase(it);
        }
        if (bitstrings.size() == 1) i = numBits;
    }

    // Clear strings from the vector until carbonDioxide string found
    for (int i = 0; i < numBits; i++) {
        for (vector<bitset<numBits> >::iterator it = cpybitstrings.begin(); it < cpybitstrings.end(); it++) {
            if (it->test((numBits - 1) - i) == res[i]) it = cpybitstrings.erase(it);
        }
        if (bitstrings.size() == 1) i = numBits;
    }

    oxygen = bitstrings.front().to_ulong();
    carbonDioxide = cpybitstrings.front().to_ulong();

    return oxygen * carbonDioxide;
}