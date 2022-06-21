#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool hit_area(int x1, int y1, int x2, int y2, int xvelo, int yvelo, int& peak) {
    int x = 0, y = 0;

    while (x <= x2 && y >= y1) {
   //     cout << x << " " << y << endl;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
            // in box
            return true;
        }
        x += xvelo;
        y += yvelo;
        if (xvelo > 0) {
            xvelo--;
        }
        yvelo--;
        peak = max(peak, y);
    }

    return false;
}

int main() {
    string input;
    getline(cin, input);

    int pos = input.find("=");
    input = input.substr(pos + 1);
    pos = input.find(".");
    int x1 = stoi(input.substr(0, pos));
    input = input.substr(pos + 2);
    pos = input.find(",");
    int x2 = stoi(input.substr(0, pos));
    pos = input.find("=");
    input = input.substr(pos + 1);
    pos = input.find(".");
    int y1 = stoi(input.substr(0, pos));
    input = input.substr(pos + 2);
    int y2 = stoi(input);

    // cout << x1 << " " << x2 << " " << y1 << " " << y2 << endl;


    // use the quadratic formula to find the optimal x velocity
    int xvelo = (1-(int)ceil(sqrt(1+8*x1)))/(-2);
    // use the quadratic formula to find the min y velocity
    int yvelo = (1-(int)ceil(sqrt(1-8*y2)))/(-2);

    int peak = 0;
    int best = 0;

    /*
    while (hit_area(x1, y1, x2, y2, xvelo, yvelo, peak)) {
        cout << "Hit at " << yvelo << endl;
        yvelo++;
        if (peak > best) {
            best = peak;
        }
        peak = 0;
    }
    */

    int p2count = 0;

    for (int xvelo = 0; xvelo < 5000; xvelo++) {
        for (int yvelo = -1000; yvelo < 5000; yvelo++) {
            peak = 0;
            if (hit_area(x1, y1, x2, y2, xvelo, yvelo, peak)) {
                if (peak > best) {
                    best = peak;
                }
                p2count++;
            }
        }
    }

    cout << "P1: " << best << endl;
    cout << "P2: " << p2count << endl;
    // cout << xvelo << " " << yvelo << endl;

    return 0;
}
