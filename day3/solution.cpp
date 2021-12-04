#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

// Change this to match the number of bits in the input. Sample input is 5 bits, my input is 12.
const int numBits = 12;

using namespace std;

// function headers
int partOne(vector<bitset<numBits> >, int);
int partTwo(vector<bitset<numBits> >, int);

int main(int argc, char** argv) {
    vector<bitset<numBits> > bitstrings; // Vector of bit strings
    ifstream input(argv[1]);
    string tmp;
    int count = 0; // Number of strings from input

    // Put strings into a bitset and then push it to the vector
    while (input >> tmp) {
        bitstrings.push_back(bitset<numBits>(tmp));
        count++;
    }

    // Print results
    cout << "Part One Answer: " << partOne(bitstrings, count) << endl;
    cout << "Part Two Answer: " << partTwo(bitstrings, count) << endl;
    return 0;
}

// Counts the number of 1s in each position of the bitstrings.
// Then creates a new "bitstring" where each position is the majority value
// of all the bitstrings. Then calculates the gamma and epsilon and returns
// their product.
int partOne(vector<bitset<numBits> > bitstrings, int count) {
    // Array to track number of 0s in each position.
    int res[numBits] = { 0 };
    int gamma = 0;
    int epsilon = 0;

    // Counts the number of ones in each position and places it in the res array
    for (vector<bitset<numBits> >::iterator it = bitstrings.begin(); it < bitstrings.end(); it++) {
        for (int i = 0; i < numBits; i++) {
            //test(i) reads the ith bit from the right. NOT LEFT.
            res[(numBits - 1) - i] += it->test(i);
        }
    }

    // Reduce the resulting array counts to either 0 or 1 if there are more 0s or 1s
    for (int i = 0; i < numBits; i++) {
        (res[i] <= count / 2) ? res[i] = 0 : res[i] = 1;
    }

    // Convert array to decimal values for gamma and epsilon
    for (int i = 0; i < numBits; i++) {
        gamma = gamma * 2 + res[i];
        epsilon = epsilon * 2 + (1 - res[i]);
    }
    return gamma * epsilon;
}

// Finds the most popular bit in each position of the bitstrings and then eliminates strings
// that either match the bit (to find the oxygen string) or don't match the bit (to find the CO2 string).
// Once these strings are found, convert them to binary and return their product.
int partTwo(vector<bitset<numBits> > bitstrings, int count) {
    // Array to track number of 0s in each position.
    vector<bitset<numBits> > cpybitstrings = bitstrings;
    int tmpCount = count; // Number of strings decreases with each elimination
    int oxygen = 0;
    int carbonDioxide = 0;

    // Find oxygen string
    for (int i = 0; i < numBits; i++) {
        // Count the number of 1s in the ith position (from the left) of the remaining strings
        int oneCount = 0;
        for (vector<bitset<numBits> >::iterator it = bitstrings.begin(); it < bitstrings.end(); it++) {
            if (it->test((numBits - 1) - i) == 1) oneCount++;
        }
        // If 1s are the majority, let 1 be the filter bit. Otherwise let it be 0.
        oneCount = (2 * oneCount >= tmpCount) ? 1 : 0;
        // Remove strings that don't match the filter bit
        for (vector<bitset<numBits> >::iterator it = bitstrings.begin(); it < bitstrings.end(); it++) {
            if (it->test((numBits - 1) - i) != oneCount) {
                // Erase and move iterator back as to not skip a string
                it = bitstrings.erase(it);
                it--;
            }
        }
        // Update the number of strings left
        tmpCount = bitstrings.size();
        if (tmpCount == 1) i = numBits;
    }

    // Find CO2 string
    tmpCount = count;
    for (int i = 0; i < numBits; i++) {
        // Count the number of 1s in the ith position (from the left) of the remaining strings
        int oneCount = 0;
        for (vector<bitset<numBits> >::iterator it = cpybitstrings.begin(); it < cpybitstrings.end(); it++) {
            if (it->test((numBits - 1) - i) == 1) oneCount++;
        }
        // If 1s are the majority, let 1 be the filter bit. Otherwise let it be 0.
        oneCount = (2 * oneCount < tmpCount) ? 0 : 1;
        // remove strings that match the filter bit
        for (vector<bitset<numBits> >::iterator it = cpybitstrings.begin(); it < cpybitstrings.end(); it++) {
            if (it->test((numBits - 1) - i) == oneCount) {
                // Erase and move iterator back as to not skip a string
                it = cpybitstrings.erase(it);
                it--;
            }
        }
        // Update the number of strings left
        tmpCount = cpybitstrings.size();
        if (tmpCount == 1) i = numBits;
    }

    // Convert the remaining strings to decimal
    oxygen = bitstrings.front().to_ulong();
    carbonDioxide = cpybitstrings.front().to_ulong();

    return oxygen * carbonDioxide;
}