#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

using namespace std;

class Puzzle {
public:
    virtual int64_t solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<pair<int64_t, int64_t>> v;
        int64_t y = 0;
        while (getline(input, line)) {
            bool no_galaxies = true;
            for (int64_t i = 0; i < line.length(); ++i) {
                if (line[i] == '#') {
                    v.push_back({i, y});
                    no_galaxies = false;
                }
            }
            y++;
            if (no_galaxies) {
                y++;
            }
        }
        bool empty = false;
        int64_t x_max = line.size();
        for (auto a : v) {
            cout << a.first << " " << a.second << endl;
        }
        for (int64_t i = 0; i < x_max; ++i) {
            // int64_t x_bias = 0;
            if (empty) {
                empty = false;
                continue;
            }
            bool at_least_one = false;
            for (int64_t j = 0; j < v.size(); ++j) {
                if (v[j].first == i) {
                    at_least_one = true;
                }
            }
            if (!at_least_one) {
                for (int64_t j = 0; j < v.size(); ++j) {
                    if (v[j].first > i) {
                        v[j].first++;
                    }
                }
                x_max++;
                empty = true;
            }
        }
        for (int64_t i = 0; i < v.size(); ++i) {
            // cout << v[i].first << " " << v[i].second << ": " << endl;
            for (int64_t j = i + 1; j < v.size(); ++j) {
                sum += abs(v[j].first - v[i].first) + abs(v[j].second - v[i].second);
                // cout << v[j].first << " " << v[j].second << " " << abs(v[j].first - v[i].first) + abs(v[j].second - v[i].second) << endl;
            }
            cout << endl;
        }
        cout << sum << endl;
        return sum;
    }
};

class Puzzle2 : public Puzzle {
public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<pair<int64_t, int64_t>> v;
        int64_t y = 0;
        while (getline(input, line)) {
            bool no_galaxies = true;
            for (int64_t i = 0; i < line.length(); ++i) {
                if (line[i] == '#') {
                    v.push_back({i, y});
                    no_galaxies = false;
                }
            }
            y++;
            if (no_galaxies) {
                y += 1000000 - 1;
            }
        }
        int64_t x_max = line.size();
        for (auto a : v) {
            cout << a.first << " " << a.second << endl;
        }
        int64_t x_cur = 0;
        while (x_cur < x_max) {
            bool at_least_one = false;
            for (int64_t j = 0; j < v.size(); ++j) {
                if (v[j].first == x_cur) {
                    at_least_one = true;
                }
            }
            if (!at_least_one) {
                for (int64_t j = 0; j < v.size(); ++j) {
                    if (v[j].first > x_cur) {
                        v[j].first += 1000000 - 1;
                    }
                }
                x_max += 1000000 - 1;
                x_cur += 1000000 - 1;
            }
            x_cur++;
        }
        for (int64_t i = 0; i < v.size(); ++i) {
            // cout << v[i].first << " " << v[i].second << ": " << endl;
            for (int64_t j = i + 1; j < v.size(); ++j) {
                sum += abs(v[j].first - v[i].first) + abs(v[j].second - v[i].second);
                // cout << v[j].first << " " << v[j].second << " " << abs(v[j].first - v[i].first) + abs(v[j].second - v[i].second) << endl;
            }
            cout << endl;
        }
        cout << sum << endl;
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