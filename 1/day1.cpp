#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    int count = 0;
    vector<int> nums;

    for (int prev = -1, current = 0; input >> current; prev = current) {
        nums.push_back(current);
        if (prev != -1 && current > prev) {
            count++;
        }
    }

    cout << "P1: " << count << endl;
    count = 0;

    int prev = -1;
    for (int i = 0; i < nums.size() - 2; i++) {
        int current = 0;
        for (int j = 0; j < 3; j++) {
            current += nums[i + j];
        }
        if (prev != -1 && current > prev) {
            count++;
        }
        prev = current;
    }

    cout << "P2: " << count << endl;
}
