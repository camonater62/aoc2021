#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void update_counts(vector<vector<int>> &board, int x, int y, bool * visited) {
    if (board[y][x] >= 10 && !visited[y * board[y].size() + x]) {
        visited[y * board[y].size() + x] = true;
        for (int oy = -1; oy < 2; oy++) {
            for (int ox = -1; ox < 2; ox++) {
                if (y + oy < 0 || y + oy > board.size() - 1 || x + ox < 0
                    || x + ox > board[y].size() - 1 || (oy == 0 && ox == 0)) {
                } else {
                    board[y + oy][x + ox] += 1;
                    update_counts(board, x + ox, y + oy, visited);
                }
            }
        }
    }
}

int main() {
    string line;

    ifstream input("input.txt");

    vector<vector<int>> board;

    while (getline(input, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        board.push_back(row);
    }

    int p1count = 0;

        vector<vector<int>> upcoming = vector<vector<int>>(board.size(), vector<int>(board[0].size(), 0));
        bool * visited = new bool[board.size() * board[0].size()];
    bool all_flash = false;
    int step = 0;
    for (step = 0; !all_flash; step++) {
        for (int y = 0; y < board.size(); y++) {
            for (int x = 0; x < board[y].size(); x++) {
                upcoming[y][x] += board[y][x] + 1;
                update_counts(upcoming, x, y, visited);
            }
        }
        all_flash = true;
        for (int y = 0; y < board.size(); y++) {
            for (int x = 0; x < board[y].size(); x++) {
                board[y][x] = upcoming[y][x];
                if (board[y][x] >= 10) {
                    board[y][x] = 0;
                    if (step < 100) {
                        p1count++;
                    }
                //    cout << "\033[0m\033[1m";
                } else {
                //    cout << "\033[0m\033[2m";
                    all_flash = false;
                }
                // cout << board[y][x];
                upcoming[y][x] = 0;
                visited[y * board[y].size() + x] = false;
            }
        //   cout << endl;
        }
        // cout << endl << endl << endl;
    }
    // cout << "\033[0m";
        delete[] visited;

    cout << "P1: " << p1count << endl;
    cout << "P2: " << step << endl;

    return 0;
}
