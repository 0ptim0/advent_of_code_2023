#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

using namespace std;

class Puzzle {
public:
    virtual int solve(istream &input) = 0;
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
    int solve(istream &input) override {
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
        int count = 0;
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
                cout << c;
                count++;
                if (n == "ZZZ") {
                    loop = false;
                    break;
                } else {
                    p = graph.find(n);
                    // cout << n << endl;
                }
            }
            cout << endl;
        }
        return count;
    }
};

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find LCM of two numbers
int64_t lcm(int64_t a, int64_t b) {
    return (a * b) / gcd(a, b);
}

// Function to find LCM of an array of numbers
int64_t findLCM(vector<int64_t> v) {
    int64_t result = v[0];

    for (auto n : v) {
        result = lcm(result, n);
    }

    return result;
}

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
    int solve(istream &input) override {
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
                cout << m[1] << endl;
            }
            // if (string(m[1]) == "GFA") {
            //     first.push_back(m[1]);
            //     cout << m[1] << endl;
            // }
        }
        cout << endl;
        vector<int64_t> count;
        vector<pair<string, string>> cur;
        for (auto f : first) {
            cur.push_back(graph.find(f));
            count.push_back(0);
            // cout << graph.find(f).first << " " << graph.find(f).second << endl;
        }
        // cout << cur.size() << endl;
        bool loop = true;
        int z_counter = 0;
        int i = 0;
        for (auto &p : cur) {
            while (loop) {
                for (auto c : traversal) {
                // for (auto p : cur) {
                //     cout << p.first << " " << p.second << endl;
                // }
                    string n;
                    if (c == 'L') {
                        n = p.first;
                    } else if (c == 'R') {
                        n = p.second;
                    }
                    // cout << n << endl;
                    count[i]++;
                    if (n.back() == 'Z') {
                        z_counter++;
                        loop = false;
                        break;
                    }
                    p = graph.find(n);
                }

                // cout << endl;
                // count++;
                // if (z_counter != 0)
                    // cout << z_counter << endl;
                // if (z_counter == cur.size()) {
                //     loop = false;
                //     break;
                // }
                // z_counter = 0;
            }
            cout << count[i] << endl;
            i++;
            loop = true;
        }
        cout << findLCM(count) << endl;
        return findLCM(count);
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
    // sol.setStrategy(new Puzzle1);
    // sol.solve("input.txt", "output_1.txt");
    sol.setStrategy(new Puzzle2);
    sol.solve("input.txt", "output_2.txt");
    return 0;
}