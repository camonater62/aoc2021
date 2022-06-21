#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Point {
    int x;
    int y;
    int cost;
    int priority;

    Point() {

    }

    Point(int x, int y, int cost, int priority) {
        this->x = x;
        this->y = y;
        this->cost = cost;
        this->priority = priority;
    }

    bool operator==(const Point &otherPoint) const {
        if (this->x == otherPoint.x && this->y == otherPoint.y) {
            return true;
        } else {
            return false;
        }
    }

    friend bool operator<(Point const& a, Point const& b) {
        return a.cost < b.cost;
    }

    struct HashFunction {
        size_t operator()(const Point &point) const {
            size_t xHash = hash<int>()(point.x);
            size_t yHash = hash<int>()(point.y) << 1;
            return xHash ^ yHash;
        }
    };

    struct LessFunction {
        bool operator()(Point a, Point b) {
            return a.priority < b.priority;
        }
    };

    struct GreaterFunction {
        bool operator()(Point a, Point b) {
            return a.priority > b.priority;
        }
    };
};


int find_path(vector<vector<int>> &board) {
    unordered_set<Point, Point::HashFunction> visited;
    vector<Point> points;
    priority_queue<Point, vector<Point>, Point::GreaterFunction> pq(points.begin(), points.end());
    pq.push(Point(0,0,0,0));

    int endx = board[0].size() - 1;
    int endy = board.size() - 1;


    while (!pq.empty()) {
        Point p = pq.top();
        pq.pop();
        visited.emplace(p);

        if (p.x == endx && p.y == endy) {
            return p.cost;
        }

        // UP
        if (p.y > 0) {
            int newx = p.x;
            int newy = p.y - 1;
            int cost = p.cost + board[newy][newx];
            int priority = cost + abs(endx - newx) + abs(endy - newy);
            Point up(newx, newy, cost, priority);
            if (visited.find(up) != visited.end()) {
                Point prev = *visited.find(up);
                if (up.cost < prev.cost) {
                    pq.push(up);
                }
            } else {
                pq.push(up);
            }
        }

        // DOWN
        if (p.y < board.size() - 1) {
            int newx = p.x;
            int newy = p.y + 1;
            int cost = p.cost + board[newy][newx];
            int priority = cost + abs(endx - newx) + abs(endy - newy);
            Point down(newx, newy, cost, priority);

            if (visited.find(down) != visited.end()) {
                Point prev = *visited.find(down);
                if (down.cost < prev.cost) {
                    pq.push(down);
                }
            } else {
                pq.push(down);
            }
        }

        // LEFT
        if (p.x > 0) {
            int newx = p.x - 1;
            int newy = p.y;
            int cost = p.cost + board[newy][newx];
            int priority = cost + abs(endx - newx) + abs(endy - newy);
            Point left(newx, newy, cost, priority);

            if (visited.find(left) != visited.end()) {
                Point prev = *visited.find(left);
                if (left.cost < prev.cost) {
                    pq.push(left);
                }
            } else {
                pq.push(left);
            }
        }

        // RIGHT
        if (p.x < board[p.y].size() - 1) {
            int newx = p.x + 1;
            int newy = p.y;
            int cost = p.cost + board[newy][newx];
            int priority = cost + abs(endx - newx) + abs(endy - newy);
            Point right(newx, newy, cost, priority);

            if (visited.find(right) != visited.end()) {
                Point prev = *visited.find(right);
                if (right.cost < prev.cost) {
                    pq.push(right);
                }
            } else {
                pq.push(right);
            }
        }
        // cout << pq.size() << endl;
    }
    return -1;
}

int main() {
    ifstream input("input.txt");

    vector<vector<int>> board;

    string line;
    while (getline(input, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        board.push_back(row);
    }

    cout << "P1: " << find_path(board) << endl;

    vector<vector<int>> big_board;
    for (int oy = 0; oy < 5; oy++) {
        for (int y = 0; y < board.size(); y++) {
            vector<int> row;
            for (int ox = 0; ox < 5; ox++) {
                for (int x = 0; x < board[y].size(); x++) {
                    row.push_back(board[y][x] + oy + ox);
                    if (row[row.size() - 1] > 9) {
                        row[row.size() - 1] -= 9;
                    }
                    // cout << row[row.size() - 1];
                }
            }
            big_board.push_back(row);
            // cout << endl;
        }
    }

    cout << "P2: " << find_path(big_board) << endl;

    return 0;
}
