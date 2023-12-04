#include <errno.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

class Puzzle {
public:
    virtual int solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
public:
    int solve(istream &input) override {
        int sum = 0;
        string line;
        while (getline(input, line)) {
            set<int> s;
            int points = 0;
            char *p1 = nullptr, *p2 = nullptr;
            char *token = nullptr;
            token = strtok_r(line.data(), ":", &p1);
            p2 = p1;
            token = strtok_r(nullptr, "|", &p1);
            while ((token = strtok_r(nullptr, " ", &p2)) != nullptr) {
                s.insert(atoi(token));
            }
            p2 = p1;
            while ((token = strtok_r(nullptr, " ", &p2)) != nullptr) {
                if (s.find(atoi(token)) != s.end()) {
                    if (points == 0) {
                        points = 1;
                    } else {
                        points *= 2;
                    }
                }
            }
            sum += points;
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
public:
    int solve(istream &input) override {
        vector<int> dp;
        string line;
        while (getline(input, line)) {
            dp.push_back(1);
        }
        input.clear();
        input.seekg(ios_base::beg);
        int i = 0;
        while (getline(input, line)) {
            set<int> s;
            char *p1 = nullptr, *p2 = nullptr;
            char *token = nullptr;
            token = strtok_r(line.data(), ":", &p1);
            p2 = p1;
            token = strtok_r(nullptr, "|", &p1);
            while ((token = strtok_r(nullptr, " ", &p2)) != nullptr) {
                s.insert(atoi(token));
            }
            p2 = p1;
            int j = 1;
            while ((token = strtok_r(nullptr, " ", &p2)) != nullptr) {
                if (s.find(atoi(token)) != s.end()) {
                    dp[i + j] += dp[i];
                    j++;
                }
            }
            ++i;
        }
        return accumulate(dp.begin(), dp.end(), 0);
    }
};

class Solution {
private:
    Puzzle *m_strategy;

public:
    void setStrategy(Puzzle *strategy) { m_strategy = strategy; }

    int solve(const string &in, const string &out) {
        ifstream input;
        ofstream output;
        input.open(in, ios::in);
        output.open(out, ios::out);
        int rv = m_strategy->solve(input);
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
