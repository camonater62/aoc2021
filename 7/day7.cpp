#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ifstream input("input.txt");
    vector<int> nums;

    char line[4096];

    input.getline(line, 4096);

    char * token = strtok(line, ",");
    int sum = 0;
    while (token) {
        int n = stoi(token);
        sum += n;
        nums.push_back(n);
        token = strtok(NULL, ",");
    }

    double avg = (double)sum / nums.size();
    cout << avg << endl;

    sort(nums.begin(), nums.end());

    int median = nums[nums.size() / 2];
    int total1 = 0;
    int total2 = 0;

    for (int i = 0; i < nums.size(); i++) {
        total1 += abs(nums[i] - median);
        double diff = ceil(abs(nums[i] - avg));
        total2 += diff * (diff + 1) / 2;
    }

    cout << "P1: " << total1 << endl;
    cout << "P2: " << (int)total2 << endl;

    int min_val = (int)1e31;

    for (int i = 0; i < nums[nums.size()-1]; i++) {
        int current = 0;
        for (int j = 0; current < min_val && j < nums.size(); j++) {
            int diff = abs(i - nums[j]);
            current += diff * (diff + 1) / 2;
        }
        if (current < min_val) {
            min_val = current;
        }
    }

    cout << "P2: " << min_val << endl;
}
