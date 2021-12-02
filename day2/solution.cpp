#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Struct containing a direction and value
struct direction
{
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

    while (input >> dir >> value)
    {
        // Create direction object
        direction tmp;
        tmp.direction = dir;
        tmp.value = value;

        // Push it onto the stack
        dirs.push_back(tmp);
    }

    // Print results
    cout << "Part One Answer: " << partOne(dirs) << endl;
    return 0;
}

// Returns the product of the final horizontal position and depth
int partOne(vector<direction> dirs) {
    int horiz = 0, depth = 0;

    for (vector<direction>::iterator it = dirs.begin(); it < dirs.end(); it++)
    {
        if (it->direction == "forward")
        {
            horiz += it->value;
        } else if (it->direction == "down")
        {
            depth += it->value;
        } else if (it->direction == "up")
        {
            // Check if already at surface
            if (depth < it->value)
            {
                depth = 0;
            } else {
                depth -= it->value;
            }
        }
    }

    return horiz * depth;
}

int partTwo(vector<direction> dirs) {
    int result = 0;
    return result;
}