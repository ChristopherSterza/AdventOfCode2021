#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Struct containing a direction and value
struct direction {
    string direction;
    int value;
};

// function headers
int partOne(vector<direction>);
int partTwo(vector<direction>);

int main(int argc, char** argv) {

    // Fill a vector with direction objects
    ifstream input(argv[1]);
    vector<direction> dirs;
    string dir;
    int value;

    while (input >> dir >> value) {
        // Create direction object
        direction tmp;
        tmp.direction = dir;
        tmp.value = value;

        // Push it onto the stack
        dirs.push_back(tmp);
    }

    // Print results
    cout << "Part One Answer: " << partOne(dirs) << endl;
    cout << "Part Two Answer: " << partTwo(dirs) << endl;
    return 0;
}

// Returns the product of the final horizontal position and depth
int partOne(vector<direction> dirs) {
    int horiz = 0, depth = 0;

    for (vector<direction>::iterator it = dirs.begin(); it < dirs.end(); it++) {
        if (it->direction == "forward") {
            horiz += it->value;
        } else if (it->direction == "down") {
            depth += it->value;
        } else if (it->direction == "up") {
            depth -= it->value;
            // Check if we surfaced.
            if (depth < 0) depth = 0;
        }
    }

    return horiz * depth;
}

// Returns the product of the final horizontal position and depth.
// Depth is now based on forward movement and the "aim" of the submarine.
int partTwo(vector<direction> dirs) {
    int horiz = 0, depth = 0, aim = 0;

    for (vector<direction>::iterator it = dirs.begin(); it < dirs.end(); it++) {
        if (it->direction == "forward") {
            horiz += it->value;
            depth += aim * it->value;
            // Check if we surfaced.
            if (depth < 0) depth = 0;
        } else if (it->direction == "down") {
            aim += it->value;
        } else if (it->direction == "up") {
            aim -= it->value;
        }
    }

    return horiz * depth;
}