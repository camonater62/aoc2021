#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream input("input.txt");
    string line;

    int p1count = 0;
    vector<long> p2vals;

    while (getline(input, line)) {
        std::stack<char> S;

        bool incomplete = true;

        for (char c : line) {
            if (c == '('
            ||  c == '['
            ||  c == '{'
            ||  c == '<') {
                S.push(c);
            } else {
                char t = S.top();
                S.pop();
                if ((t == '(' && c == ')')
                ||  (t == '[' && c == ']')
                ||  (t == '{' && c == '}')
                ||  (t == '<' && c == '>')) {
                    continue;
                }

                switch (c) {
                    case ')': p1count += 3; break;
                    case ']': p1count += 57; break;
                    case '}': p1count += 1197; break;
                    case '>': p1count += 25137; break;
                }
                incomplete = false;
                break;
            }
        }

        if (!incomplete) {
            continue;
        }

        long points = 0;

        while (!S.empty()) {
            char t = S.top();
            S.pop();

            points *= 5;

            switch (t) {
                case '<': points++;
                case '{': points++;
                case '[': points++;
                case '(': points++; break;
            }
        }

        if (points != 0) {
            p2vals.push_back(points);
        }
    }

    sort(p2vals.begin(), p2vals.end());

    cout << "P1: " << p1count << endl;
    cout << "P2: " << p2vals[p2vals.size() / 2] << endl;
}
