#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");

    int grid[1000 * 1000] = {0};

    string line;
    int x1, y1, x2, y2;
    while (getline(input, line)) {
        int index = line.find(',');
        x1 = stoi(line.substr(0, index));
        line = line.substr(index + 1);
        index = line.find(' ');
        y1 = stoi(line.substr(0, index));
        line = line.substr(index + 1);
        index = line.find(' ');
        line = line.substr(index);
        index = line.find(',');
        x2 = stoi(line.substr(0, index));
        line = line.substr(index + 1);
        y2 = stoi(line);

        if (x1 == x2) {
            // vert
            for (int smaller = min(y1, y2); smaller <= max(y1, y2); smaller++) {
                grid[smaller * 1000 + x1]++;
            }

        } else if (y1 == y2) {
            // hor
            for (int smaller = min(x1, x2); smaller <= max(x1, x2); smaller++) {
                grid[y1 * 1000 + smaller]++;
            }
        } else if ((y1 > y2 && x1 > x2) || (y1 < y2 && x1 < x2)) {
            // diag (\)
            for (int sx = min(x1, x2), sy = min(y1, y2); sx <= max(x1, x2); sx++, sy++) {
                grid[sy * 1000 + sx]++;
            }
        } else {
            // diag /
            for (int sx = min(x1, x2), sy = max(y1, y2); sx <= max(x1, x2); sx++, sy--) {
                grid[sy * 1000 + sx]++;
            }
        }
    }

    int count = 0;
    for (int y = 0; y < 1000; y++) {
        for (int x = 0; x < 1000; x++) {
            if (grid[y * 1000 + x] >= 2) {
                count++;
            }
        }
    }

    cout << count << endl;

    return 0;
}
