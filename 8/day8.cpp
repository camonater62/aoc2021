#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
 * 0:
 * 1:
 * 2: 1
 * 3: 7
 * 4: 4
 * 5: 2, 3, 5
 * 6: 0, 6, 9
 * 7: 8
 */

void stov(vector<string> &vec, string s, string sep) {
    int prev = -1, curr = 0;
    for (curr = s.find(sep); curr < s.size() && curr != string::npos;
         prev = curr, curr = s.find(sep, curr + 1)) {
        vec.push_back(s.substr(prev + 1, curr - prev - 1));
    }
    vec.push_back(s.substr(prev + 1));
}

int main() {
    ifstream input("input.txt");

    string line;

    int p1count = 0;
    int p2count = 0;

    unordered_map<string, int> charstoval;
    charstoval.emplace("abcefg", 0);
    charstoval.emplace("cf", 1);
    charstoval.emplace("acdeg", 2);
    charstoval.emplace("acdfg", 3);
    charstoval.emplace("bcdf", 4);
    charstoval.emplace("abdfg", 5);
    charstoval.emplace("abdefg", 6);
    charstoval.emplace("acf", 7);
    charstoval.emplace("abcdefg", 8);
    charstoval.emplace("abcdfg", 9);

    while (!input.eof()) {
        getline(input, line);

        if (line.size() == 0) {
            break;
        }

        int pos = line.find(" | ");
        vector<string> in;
        stov(in, line.substr(0, pos), " ");
        vector<string> out;
        stov(out, line.substr(pos + 3), " ");

        int thisnum = 0;

        unordered_map<int, string> strings;
        unordered_map<char, int> counts;

        for (int i = 0; i < in.size(); i++) {
            string s = in[i];
            sort(s.begin(), s.end());

            switch (s.size()) {
                case 2:
                    strings.emplace(1, s);
                    break;
                case 3:
                    strings.emplace(7, s);
                    break;
                case 4:
                    strings.emplace(4, s);
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    strings.emplace(8, s);
                    break;
            }

            for (char c : s) {
                if (counts.find(c) == counts.end()) {
                    counts[c] = 1;
                } else {
                    counts[c] += 1;
                }
            }
        }

        unordered_map<char, char> trans;

        for (char c : "abcdefg") {
            int count = counts[c];
            switch (count) {
                case 4:
                    trans.emplace(c, 'e');
                    break;
                case 6:
                    trans.emplace(c, 'b');
                    break;
                case 7:
                    // tie between d and g
                    trans.emplace(c, (strings[4].find(c) == string::npos) ? 'g' : 'd');
                    break;
                case 8:
                    // tie between a and c
                    trans.emplace(c, (strings[1].find(c) == string::npos) ? 'a' : 'c');
                    break;
                case 9:
                    trans.emplace(c, 'f');
                    break;
            }
            // cout << c << "->" << count << "=" << trans[c] << " ";
        }
        // cout << endl;

        for (int i = 0; i < out.size(); i++) {
            switch (out[i].size()) {
            case 2:
                p1count++;
                break;
            case 3:
                p1count++;
                break;
            case 4:
                p1count++;
                break;
            case 7:
                p1count++;
                break;
            case 5:
                // 2 3 or 5
                break;
            case 6:
                // 0 6 or 9
                break;
            }

            string segs = "";
            for (char c : out[i]) {
                if (c >= 'a' && c <= 'g')
                segs += trans[c];
            }
            sort(segs.begin(), segs.end());
            // cout << segs << endl;
            thisnum = thisnum * 10 + charstoval[segs];
        }
        // cout << thisnum << endl;;
        p2count += thisnum;
    }

    input.close();

    cout << "P1: " << p1count << endl;
    cout << "P2: " << p2count << endl;

    return 0;
}
