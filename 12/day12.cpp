#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool is_upper(const string &s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < 'A' || s[i] > 'Z') {
            return false;
        }
    }
    return true;
}

void traverse(vector<string> &nodes, vector<vector<int>> &graph, int v, bool * visited, int &count) {
    if (v == 1) {
        count++;
        return;
    }
    visited[v] = true;
    for (int i = 0; i < graph[v].size(); i++) {
        if (!visited[graph[v][i]] || is_upper(nodes[graph[v][i]])) {
            traverse(nodes, graph, graph[v][i], visited, count);
        }
    }
    visited[v] = false;
}

int get_max(int * arr, int len) {
    int x = arr[0];
    for (int i = 1; i < len; i++) {
        x = max(x, arr[i]);
    }
    return x;
}

int num_larger(int * arr, int len, int val) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] > val) {
            count++;
        }
    }
    return count;
}

void traverse2(vector<string> &nodes, vector<vector<int>> &graph, int v, int * visited, int &count) {
    if (v == 1) {
        count++;
        return;
    }

    if (visited[v] > 1) {
        return;
    }

    if (!is_upper(nodes[v])) {
        visited[v]++;
    }

    for (int i = 0; i < graph[v].size(); i++) {
        if (graph[v][i] != 0 && (is_upper(nodes[graph[v][i]]) || num_larger(visited, nodes.size(), 1) < 2)) {
            traverse2(nodes, graph, graph[v][i], visited, count);
        }
    }
    if (!is_upper(nodes[v])) {
        visited[v]--;
    }
}

int main() {
    vector<string> nodes = {"start", "end"};
    vector<vector<int>> graph(2, vector<int>());

    ifstream input("input.txt");

    int p1count = 0;

    string line;
    while (getline(input, line)) {
        string a = line.substr(0, line.find('-'));
        string b = line.substr(line.find('-') + 1);

        int ai = -1;
        int bi = -1;

        for (int i = 0; i < nodes.size(); i++) {
            if (a == nodes[i]) {
                ai = i;
            }
            if (b == nodes[i]) {
                bi = i;
            }
        }

        if (ai == -1) {
            ai = nodes.size();
            nodes.push_back(a);
            graph.push_back(vector<int>());
        }

        if (bi == -1) {
            bi = nodes.size();
            nodes.push_back(b);
            graph.push_back(vector<int>());
        }

        graph[ai].push_back(bi);
        graph[bi].push_back(ai);
    }

    /*
    for (int i = 0; i < nodes.size(); i++) {
        cout << nodes[i] << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            cout << nodes[graph[i][j]] << " ";
        }
        cout << endl;
    }
    */

    bool * visited = new bool[nodes.size()];

    traverse(nodes, graph, 0, visited, p1count);

    delete[] visited;

    int p2count = 0;

    int * timesvisit = new int[nodes.size()];

    for (int i = 0; i < nodes.size(); i++) {
        timesvisit[i] = 0;
    }

    traverse2(nodes, graph, 0, timesvisit, p2count);

    delete[] timesvisit;

    cout << "P1: " << p1count << endl;
    cout << "P2: " << p2count << endl;

    return 0;
}
