#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Puzzle {
public:
    virtual int64_t solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
public:
    int64_t solve(istream &input) override {
        vector<int64_t> ex;
        string line;
        while (getline(input, line)) {
            vector<vector<int64_t>> v;
            string str;
            vector<int64_t> prev, current;
            auto line_stream = stringstream(line);
            while (getline(line_stream, str, ' ')) {
                current.push_back(stol(str));
            }
            v.push_back(current);
            while (!all_of(current.begin(), current.end(),
                           [](int i) { return i == 0; })) {
                prev = current;
                current.clear();
                for (auto it = prev.begin() + 1; it < prev.end(); ++it) {
                    current.push_back(*it - *(it - 1));
                }
                v.push_back(current);
            }
            for (int i = v.size() - 2; i >= 0; --i) {
                v[i].push_back(v[i + 1].back() + v[i].back());
            }
            ex.push_back(v[0].back());
        }
        return accumulate(ex.begin(), ex.end(), 0);
    }
};

class Puzzle2 : public Puzzle {
public:
    int64_t solve(istream &input) override {
        vector<int64_t> ex;
        string line;
        while (getline(input, line)) {
            vector<vector<int64_t>> v;
            string str;
            vector<int64_t> prev, current;
            auto line_stream = stringstream(line);
            while (getline(line_stream, str, ' ')) {
                current.push_back(stol(str));
            }
            v.push_back(current);
            while (!all_of(current.begin(), current.end(),
                           [](int i) { return i == 0; })) {
                prev = current;
                current.clear();
                for (auto it = prev.begin() + 1; it < prev.end(); ++it) {
                    current.push_back(*it - *(it - 1));
                }
                v.push_back(current);
            }
            for (int i = v.size() - 2; i >= 0; --i) {
                v[i].insert(v[i].begin(), v[i].front() - v[i + 1].front());
            }
            ex.push_back(v[0].front());
        }
        return accumulate(ex.begin(), ex.end(), 0);
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
