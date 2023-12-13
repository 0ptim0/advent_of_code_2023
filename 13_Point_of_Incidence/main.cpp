#include <bits/stdc++.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

class Puzzle {
public:
    virtual int64_t solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
private:
    bool check(const vector<string> &v, int64_t i) {
        for (int j1 = i, j2 = i - 1; j1 < v.size() && j2 >= 0; ++j1, --j2) {
            if (v[j1] != v[j2]) {
                return false;
            }
        }
        return true;
    }

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<string> v;
        while (getline(input, line)) {
            if (line.length() != 0) {
                v.push_back(line);
                continue;
            }

            vector<string> vt;
            for (int i = 0; i < v[0].size(); ++i) {
                string col;
                for (int j = 0; j < v.size(); ++j) {
                    col.push_back(v[j][i]);
                }
                vt.push_back(col);
            }

            int64_t cols = 0, rows = 0;

            string col_prev;
            for (int i = 0; i < vt.size(); ++i) {
                string col = vt[i];
                if (col == col_prev && check(vt, i)) {
                    cols = i;
                    break;
                }
                col_prev = col;
            }

            string row_prev;
            for (int i = 0; i < v.size(); ++i) {
                string row = v[i];
                if (row == row_prev && check(v, i)) {
                    rows = i;
                    break;
                }
                row_prev = row;
            }

            sum += cols + 100 * rows;
            v.clear();
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
private:
    bool check(const vector<string> &v, int64_t i) {
        for (int j1 = i, j2 = i - 1; j1 < v.size() && j2 >= 0; ++j1, --j2) {
            if (v[j1] != v[j2]) {
                return false;
            }
        }
        return true;
    }

    bool checkWithDiff(const vector<string> &v, int64_t i) {
        int diff = 0;
        for (int j1 = i, j2 = i - 1; j1 < v.size() && j2 >= 0; ++j1, --j2) {
            for (int j = 0; j < v[j1].size(); ++j) {
                if (v[j1][j] != v[j2][j]) {
                    diff++;
                }
                if (diff > 1) return false;
            }
        }
        return true;
    }

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<string> v;
        while (getline(input, line)) {
            if (line.length() != 0) {
                v.push_back(line);
                continue;
            }

            vector<string> vt;
            for (int i = 0; i < v[0].size(); ++i) {
                string col;
                for (int j = 0; j < v.size(); ++j) {
                    col.push_back(v[j][i]);
                }
                vt.push_back(col);
            }

            int64_t cols = 0, rows = 0;
            int64_t cols_alt = 0, rows_alt = 0;

            string col_prev;
            for (int i = 0; i < vt.size(); ++i) {
                string col = vt[i];
                if (check(vt, i)) {
                    cols = i;
                } else if (checkWithDiff(vt, i)) {
                    cols_alt = i;
                }
                col_prev = col;
            }

            string row_prev;
            for (int i = 0; i < v.size(); ++i) {
                string row = v[i];
                if (check(v, i)) {
                    rows = i;
                } else if (checkWithDiff(v, i)) {
                    rows_alt = i;
                }
                row_prev = row;
            }

            sum += cols_alt + 100 * rows_alt;
            v.clear();
        }
        return sum;
    }
};

class Solution {
private:
    Puzzle *m_strategy;

public:
    void setStrategy(Puzzle *strategy) { m_strategy = strategy; }

    int64_t solve(const string &in, const string &out) {
        ifstream input;
        ofstream output;
        input.open(in, ios::in);
        output.open(out, ios::out);
        int64_t rv = m_strategy->solve(input);
        output.write(to_string(rv).data(), to_string(rv).length());
        cout << rv << endl;
        return rv;
    }
};

int main(int argc, char *argv[]) {
    Solution sol;
    sol.setStrategy(new Puzzle1);
    sol.solve("input.txt", "output_1.txt");
    sol.setStrategy(new Puzzle2);
    sol.solve("input.txt", "output_2.txt");
    return 0;
}
