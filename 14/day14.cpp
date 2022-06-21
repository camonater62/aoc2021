#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

long get_difference(unordered_map<string, long> counts, char first, char last) {
    unordered_map<char, long> freq;
    for (auto [key, val] : counts) {
        freq[key[0]] += val;
        freq[key[1]] += val;
    }

    // have to add one for the first and last characters so the /2 works properly
    freq[first]++;
    freq[last]++;

    for (auto [key, val] : freq) {
        freq[key] /= 2;
    }

    // starting value not important
    char min = first;
    char max = last;

    for (auto [key, val]: freq) {
        if (freq[key] < freq[min]) {
            min = key;
        }
        if (freq[key] > freq[max]) {
            max = key;
        }
    }

    return freq[max] - freq[min];
}

int main() {
    ifstream input("input.txt");

    string polymer;

    getline(input, polymer);

    string line;
    getline(input, line); // empty line

    unordered_map<string, string> mapping;

    while (getline(input, line)) {
        string k = line.substr(0, line.find(' '));
        string v = line.substr(line.find_last_of(' ') + 1);

        mapping.emplace(k, v);
    }

    unordered_map<string, long> counts;

    // decompose the polymer
    char first = polymer[0];
    char last = polymer[polymer.length() - 1];
    for (int i = 0; i < polymer.length() - 1; i++) {
        counts[polymer.substr(i, 2)]++;
    }

    for (int step = 0; step < 40; step++) {
        unordered_map<string, long> next_counts;
        for (auto [key, val] : counts) {
            string new_char = mapping[key];
            next_counts[key[0] + new_char] += val;
            next_counts[new_char + key[1]] += val;
        }
        counts = next_counts;
        if (step == 9) {
            cout << "P1: " << get_difference(counts, first, last) << endl;
        }
    }

    cout << "P2: " << get_difference(counts, first, last) << endl;

    return 0;

}
