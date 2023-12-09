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
    class Graph {
    public:
        unordered_map<string, pair<string, string>> g;

    public:
        auto add(string value, string l, string r) {
            g[value] = {l, r};
            return g[value];
        }

        auto find(string value) { return g[value]; }
    };

public:
    int64_t solve(istream &input) override {
        string line, traversal;
        Graph graph;
        getline(input, traversal);
        getline(input, line);
        while (getline(input, line)) {
            smatch m;
            regex_search(
                line, m,
                regex("([A-Za-z]+)\\s*=\\s*\\(([^,]+),\\s*([^)]+)\\)"));
            graph.add(m[1], m[2], m[3]);
        }
        int64_t count = 0;
        auto p = graph.find("AAA");
        bool loop = true;
        while (loop) {
            for (auto c : traversal) {
                string n;
                if (c == 'L') {
                    n = p.first;
                } else if (c == 'R') {
                    n = p.second;
                }
                count++;
                if (n == "ZZZ") {
                    loop = false;
                    break;
                } else {
                    p = graph.find(n);
                }
            }
        }
        return count;
    }
};

class Puzzle2 : public Puzzle {
    class Graph {
    public:
        unordered_map<string, pair<string, string>> g;

    public:
        auto add(string value, string l, string r) {
            g[value] = {l, r};
            return g[value];
        }

        auto find(string value) { return g[value]; }
    };

public:
    int64_t gcd(int64_t a, int64_t b) {
        while (b != 0) {
            int64_t temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    int64_t lcm(int64_t a, int64_t b) { return (a * b) / gcd(a, b); }

    int64_t findLCM(vector<int64_t> v) {
        int64_t result = v[0];
        for (auto n : v) {
            result = lcm(result, n);
        }
        return result;
    }

public:
    int64_t solve(istream &input) override {
        string line, traversal;
        vector<string> first;
        Graph graph;
        getline(input, traversal);
        getline(input, line);
        while (getline(input, line)) {
            smatch m;
            regex_search(
                line, m,
                regex("([0-9A-Za-z]+)\\s*=\\s*\\(([^,]+),\\s*([^)]+)\\)"));
            graph.add(m[1], m[2], m[3]);
            if (string(m[1]).back() == 'A') {
                first.push_back(m[1]);
            }
        }
        vector<int64_t> count;
        vector<pair<string, string>> cur;
        for (auto f : first) {
            cur.push_back(graph.find(f));
            count.push_back(0);
        }
        bool loop = true;
        int64_t i = 0;
        for (auto &p : cur) {
            while (loop) {
                for (auto c : traversal) {
                    string n;
                    if (c == 'L') {
                        n = p.first;
                    } else if (c == 'R') {
                        n = p.second;
                    }
                    count[i]++;
                    if (n.back() == 'Z') {
                        loop = false;
                        break;
                    }
                    p = graph.find(n);
                }
            }
            i++;
            loop = true;
        }
        return findLCM(count);
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
