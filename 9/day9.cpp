#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int explore(int x, int y, vector<vector<int>> points, bool * visited) {
    if (visited[y * points[y].size() + x] || points[y][x] == 9) {
        return 0;
    }

    visited[y * points[y].size() + x] = true;

    int count = 1;

    if (x > 0) {
        count += explore(x - 1, y, points, visited);
    }
    if (x < points[y].size() - 1) {
        count += explore(x + 1, y, points, visited);
    }
    if (y > 0) {
        count += explore(x, y - 1, points, visited);
    }
    if (y < points.size() - 1) {
        count += explore(x, y + 1, points, visited);
    }

    return count;
}

int main() {
    ifstream input("input.txt");

    vector<vector<int>> points;

    string line;

    while (getline(input, line)) {
        vector<int> row;
        for (char c : line) {
           // cout << c - '0';
            row.push_back(c - '0');
        }
        // cout << endl;
        points.push_back(row);
    }

    int p1count = 0;

    bool * visited = new bool[points.size() * points[0].size()];

    vector<int> basins;

    for (int y = 0; y < points.size(); y++) {
        for (int x = 0; x < points[y].size(); x++) {
            bool local_low = true;
            if (y > 0 && points[y-1][x] <= points[y][x]) {
                local_low = false;
            }
            if (y < points.size()-1 && points[y+1][x] <= points[y][x]) {
                local_low = false;
            }
            if (x > 0 && points[y][x-1] <= points[y][x]) {
                local_low = false;
            }
            if (x < points[y].size()-1 && points[y][x+1] <= points[y][x]) {
                local_low = false;
            }
            if (local_low) {
            //    cout << "\033[1;32m" << points[y][x];
                p1count += 1 + points[y][x];
            } else {
            //    cout << "\033[0m" << points[y][x];
            }
            if (points[y][x] != 9 && !visited[y * points[y].size() + x]) {
                basins.push_back(explore(x, y, points, visited));
            }
        }
        // cout << endl;
    }

    delete[] visited;

    sort(basins.begin(), basins.end());

    int p2count = 1;
    for (int i = basins.size() - 3; i < basins.size(); i++) {
        p2count *= basins[i];
    }

    cout << "P1: " << p1count << endl;
    cout << "P2: " << p2count << endl;

    return 0;
}
