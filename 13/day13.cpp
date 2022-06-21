#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;

    Point() {
    }
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Point &otherPoint) const {
        if (this->x == otherPoint.x && this->y == otherPoint.y)
            return true;
        else
            return false;
    }

    struct HashFunction {
        size_t operator()(const Point &point) const {
            size_t xHash = std::hash<int>()(point.x);
            size_t yHash = std::hash<int>()(point.y) << 1;
            return xHash ^ yHash;
        }
    };
};

int main() {
    unordered_set<Point, Point::HashFunction> points;

    string line;

    ifstream input("input.txt");

    bool reading_points = true;
    bool part1 = true;

    while (getline(input, line)) {
        if (line.length() == 0) {
            reading_points = false;
            continue;
        }

        if (reading_points) {
            int x = stoi(line.substr(0, line.find(',')));
            int y = stoi(line.substr(line.find(',') + 1));
            Point p;
            p.x = x;
            p.y = y;
            points.insert(p);
        } else {
            // folding
            int eqpos = line.find('=');
            char axis = line.substr(eqpos-1,eqpos)[0];
            int val = stoi(line.substr(eqpos+1));

            if (axis == 'y') {
                vector<Point> temp = vector<Point>(points.begin(), points.end());
                points.clear();
                for (Point p : temp) {
                    if (p.y > val) {
                        p.y = val - p.y + val;
                    }
                    points.insert(p);
                }
            } else {
                // axis == 'x'
                vector<Point> temp = vector<Point>(points.begin(), points.end());
                points.clear();
                for (Point p : temp) {
                    if (p.x > val) {
                        p.x = val - p.x + val;
                    }
                    points.insert(p);
                }
            }
            if (part1) {
                cout << "P1: " << points.size() << endl;
                part1 = false;
            }
        }
    }

    int maxx = -1, maxy = -1;

    for (Point p : points) {
        maxx = max(p.x, maxx);
        maxy = max(p.y, maxy);
    }

    string res = "";

    for (int y = 0; y < maxy + 1; y++) {
        for (int x = 0; x < maxx + 1; x++) {
            bool found = false;
            for (Point p : points) {
                if (p.x == x && p.y == y) {
                    found = true;
                }
            }
            if (found) {
                res += '#';
            } else {
                res += ' ';
            }
        }
        res += '\n';
    }

    cout << res;

    return 0;
}
