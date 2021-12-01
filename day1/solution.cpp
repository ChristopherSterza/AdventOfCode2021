#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// function headers
int partOne(vector<int>);
int partTwo(vector<int>);

int main(int argc, char** argv) {

    // Fill a vector with the input
    ifstream input(argv[1]);
    vector<int> vals;
    int line;
    while (input >> line)
    {
        vals.push_back(line);
    }

    // Print results
    cout << "Part One Answer: " << partOne(vals) << endl;
    cout << "Part Two Answer: " << partTwo(vals) << endl;

    return 0;
}

// Returns the number of times an input was larger than its previous input.
int partOne(vector<int> vals) {
    int count = 0, curr = 0, prev = vals[0];
    for (vector<int>::iterator it = vals.begin(); it < vals.end(); it++)
    {
        curr = *it;
        if (curr > prev) count++;
        prev = curr;
    }
    return count;
}

// Returns the number of times a sum of three continuous inputs was larger than its previous three continious inputs
// Essentially part one with "noise reduction"
int partTwo(vector<int> vals) {
    int count = 0, firstSum = 0, secondSum = 0;

    // This loop initializes both sums but the i counter focuses on firstSum
    for (int i = 0; i < 3; i++)
    {
        firstSum += vals[i];
        secondSum += vals[i + 1];
    }

    // First comparison
    if (secondSum > firstSum) count++;

    // This i counter focuses on secondSum
    for (int i = 4; i < vals.size(); i++)
    {
        firstSum = secondSum;
        secondSum -= vals[i - 3];
        secondSum += vals[i];

        if (secondSum > firstSum) count++;
    }

    return count;
}