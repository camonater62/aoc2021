#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");

    const int LEN = 12;
    int count[LEN];

    string line = "";

    vector<string> raw;

    while (input >> line) {
        raw.push_back(line);
        for (int i = 0; i < LEN; i++) {
            switch (line[i]) {
            case '0': count[i]--; break;
            case '1': count[i]++; break;
            }
        }
    }

    int gamma = 0;
    int epsilon = 0;
    for (int i = 0; i < LEN; i++) {
        gamma <<= 1;
        epsilon <<= 1;
        if (count[i] >= 0) {
            gamma |= 1;
        } else {
            epsilon |= 1;
        }
    }

    cout << "P1: " << gamma * epsilon << endl;


    vector<string> o2 = vector<string>(raw);
    vector<string> co2 = vector<string>(raw);

    for (int i = 0; i < LEN; i++) {
        int localcount = 0;
        for (int j = 0; j < o2.size(); j++) {
            if (o2[j][i] == '1') {
                localcount++;
            } else {
                localcount--;
            }
        }
        char compare = localcount >= 0 ? '1' : '0';
        for (int j = 0; o2.size() > 1 && j < o2.size(); j++) {
            if (o2[j][i] != compare) {
                o2.erase(o2.begin() + j);
                j--;
            }
        }

        localcount = 0;
        for (int j = 0; j < co2.size(); j++) {
            if (co2[j][i] == '1') {
                localcount++;
            } else {
                localcount--;
            }
        }
        compare = localcount >= 0 ? '0' : '1';
        for (int j = 0; co2.size() > 1 && j < co2.size(); j++) {
            if (co2[j][i] != compare) {
                co2.erase(co2.begin() + j);
                j--;
            }
        }
    }

    int o2val = stoi(o2[0].c_str(), NULL, 2);
    int co2val = stoi(co2[0].c_str(), NULL, 2);

    cout << "P2: " << o2val * co2val << endl;

    return 0;
}
