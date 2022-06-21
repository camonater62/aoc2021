#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    ifstream input("input.txt");

    long Q[9] = {0};
    long total = 0;

    char buffer[1024];
    input.getline(buffer, 1024);

    char* token = strtok(buffer, ",");
    while (token != NULL) {
        int index = stoi(token);
        Q[index] += 1;
        total++;

        token = strtok(NULL, ",");
    }

    for (int i = 0; i < 256; i++) {
        total += Q[i % 10];
        Q[(i + 9) % 10] += Q[i % 10];
        Q[(i + 7) % 10] += Q[i % 10];
        Q[i % 10] = 0;

        if (i == 79) {
            cout << "P1: " << total << endl;
        }
    }

    cout << "P2: " << total << endl;

    input.close();

    return 0;
}
