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
    int64_t hash(const string &str) {
        int64_t rv = 0;
        for (auto c : str) {
            rv += static_cast<int>(c);
            rv *= 17;
            rv = rv % 256;
        }
        return rv;
    }

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<string> v;
        while (getline(input, line, ',')) {
            sum += hash(line);
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
private:
    int64_t hash(const string &str) {
        int64_t rv = 0;
        for (auto c : str) {
            rv += static_cast<int>(c);
            rv *= 17;
            rv = rv % 256;
        }
        return rv;
    }

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<vector<pair<string, int>>> boxes(256);
        while (getline(input, line, ',')) {
            string label;
            char operation;
            int64_t focal_length = 0;
            for (auto c : line) {
                if (c == '-' || c == '=') {
                    operation = c;
                } else if (isdigit(c)) {
                    focal_length = c - '0';
                } else {
                    label.push_back(c);
                }
            }
            auto box = hash(label);
            auto it = find_if(boxes[box].begin(), boxes[box].end(),
                              [&label](const pair<string, int> &p) {
                                  return p.first == label;
                              });
            if (operation == '-') {
                if (it != boxes[box].end()) {
                    boxes[box].erase(it);
                }
            } else if (operation == '=') {
                if (it != boxes[box].end()) {
                    it->second = focal_length;
                } else {
                    boxes[box].push_back({label, focal_length});
                }
            }
        }
        for (int i = 0; i < boxes.size(); ++i) {
            for (int j = 0; j < boxes[i].size(); ++j) {
                sum += (i + 1) * (j + 1) * (boxes[i][j].second);
            }
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
