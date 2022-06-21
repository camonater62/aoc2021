#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");

    vector<int> nums;
    string line;

    getline(input, line);
    while (line.size() > 0) {
        int ci = line.find(',');
        int n = 0;
        if (ci != string::npos) {
            n = stoi(line.substr(0, ci));
            line = line.substr(ci + 1);
        } else {
            n = stoi(line);
            line = "";
        }

        // cout << n << endl;
        nums.push_back(n);
    }

    int win_val = -1;
    int win_time = 10000;

    int worst_val = -1;
    int worst_time = 0;

    while (!input.eof()) {
        int board[5][5] = {{0}};
        bool found[5][5] = {{0}};

        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (input >> board[y][x]) {
                } else {
                    goto bad_practice;
                }
            }
        }

        bool win = false;
        for (int i = 0; !win && i < nums.size(); i++) {
            for (int y = 0; y < 5; y++) {
                for (int x = 0; x < 5; x++) {
                    if (board[y][x] == nums[i]) {
                        found[y][x] = true;
                    }
                }
            }

            for (int y = 0; y < 5; y++) {
                bool val = true;
                for (int x = 0; x < 5; x++) {
                    val = val && found[y][x];
                }
                if (val) {
                    win = val;
                }
            }

            for (int x = 0; x < 5; x++) {
                bool val = true;
                for (int y = 0; y < 5; y++) {
                    val = val && found[y][x];
                }
                if (val) {
                    win = val;
                }
            }

            if (win && i < win_time) {
                int sum = 0;
                for (int y = 0; y < 5; y++) {
                    for (int x = 0; x < 5; x++) {
                        if (!found[y][x]) {
                            sum += board[y][x];
                        }
                    }
                }
                win_time = i;
                win_val = sum * nums[i];
            }
            if (win && i > worst_time) {
                int sum = 0;
                for (int y = 0; y < 5; y++) {
                    for (int x = 0; x < 5; x++) {
                        if (!found[y][x]) {
                            sum += board[y][x];
                        }
                    }
                }
                worst_time = i;
                worst_val = sum * nums[i];

            }
        }
    }
bad_practice:

    cout << "P1: " << win_val << endl;
    cout << "P2: " << worst_val << endl;

    return 0;
}
