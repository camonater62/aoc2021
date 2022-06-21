#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    // p1 vals
    int dep = 0;
    int hor = 0;

    // p2 vals
    int dep2 = 0;

    ifstream input("input.txt");

    char line[128];

    while (!input.eof()) {
        input.getline(line, 128);

        if (strlen(line) == 0) {
            break;
        }

        char * cmd = strtok(line, " ");
        int val = stoi(strtok(NULL, " "));

        if (strcmp(cmd, "forward") == 0) {
            hor += val;
            dep2 += dep * val;
        } else if (strcmp(cmd, "up") == 0) {
            dep -= val;
        } else if (strcmp(cmd, "down") == 0) {
            dep += val;
        }
    }

    cout << "P1: " << hor * dep << endl;
    cout << "P2: " << hor * dep2 << endl;

    return 0;
}
