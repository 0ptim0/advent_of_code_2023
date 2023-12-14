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
public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<string> v;
        while (getline(input, line)) {
            v.push_back(line);
        }
        for (int y = v.size() - 1; y >= 1; --y) {
            int cnt = 0;
            for (int x = 0; x < v[y].size(); ++x) {
                if (v[y][x] == 'O') {
                    for (int yy = y - 1; yy >= 0; --yy) {
                        if (v[yy][x] == '.') {
                            swap(v[y][x], v[yy][x]);
                            break;
                        } else if (v[yy][x] == 'O') {
                            continue;
                        } else if (v[yy][x] == '#') {
                            break;
                        }
                    }
                    if (v[y][x] == 'O') {
                        cnt++;
                    }
                }
            }
            sum += (v.size() - y) * cnt;
        }
        for (int x = 0; x < v[0].size(); ++x) {
            if (v[0][x] == 'O') {
                sum += v.size();
            }
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
    void tiltNorth(vector<string> &v) {
        for (int y = v.size() - 1; y >= 1; --y) {
            for (int x = 0; x < v[y].size(); ++x) {
                if (v[y][x] == 'O') {
                    for (int yy = y - 1; yy >= 0; --yy) {
                        if (v[yy][x] == '.') {
                            swap(v[y][x], v[yy][x]);
                            break;
                        } else if (v[yy][x] == 'O') {
                            continue;
                        } else if (v[yy][x] == '#') {
                            break;
                        }
                    }
                }
            }
        }
    }
    void tiltSouth(vector<string> &v) {
        for (int y = 0; y < v.size() - 1; ++y) {
            for (int x = 0; x < v[y].size(); ++x) {
                if (v[y][x] == 'O') {
                    for (int yy = y + 1; yy < v.size(); ++yy) {
                        if (v[yy][x] == '.') {
                            swap(v[y][x], v[yy][x]);
                            break;
                        } else if (v[yy][x] == 'O') {
                            continue;
                        } else if (v[yy][x] == '#') {
                            break;
                        }
                    }
                }
            }
        }
    }
    void tiltEast(vector<string> &v) {
        for (int y = 0; y < v.size(); ++y) {
            for (int x = 0; x < v[y].size() - 1; ++x) {
                if (v[y][x] == 'O') {
                    for (int xx = x + 1; xx < v[y].size(); ++xx) {
                        if (v[y][xx] == '.') {
                            swap(v[y][x], v[y][xx]);
                            break;
                        } else if (v[y][xx] == 'O') {
                            continue;
                        } else if (v[y][xx] == '#') {
                            break;
                        }
                    }
                }
            }
        }
    }
    void tiltWest(vector<string> &v) {
        for (int y = 0; y < v.size(); ++y) {
            for (int x = v[y].size() - 1; x > 0; --x) {
                if (v[y][x] == 'O') {
                    for (int xx = x - 1; xx >= 0; --xx) {
                        if (v[y][xx] == '.') {
                            swap(v[y][x], v[y][xx]);
                            break;
                        } else if (v[y][xx] == 'O') {
                            continue;
                        } else if (v[y][xx] == '#') {
                            break;
                        }
                    }
                }
            }
        }
    }

    struct VectorHasher {
        int operator()(const vector<string> &v) const {
            int hash = 0;
            for (int y = v.size() - 1; y >= 0; --y) {
                int cnt = 0;
                for (int x = 0; x < v[y].size(); ++x) {
                    if (v[y][x] == 'O') {
                        hash += (v.size() - y);
                    }
                }
            }
            return hash;
        }
    };

    unordered_map<vector<string>, vector<string>, VectorHasher> m;

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<string> v;
        while (getline(input, line)) {
            v.push_back(line);
        }
        int64_t zero_index = 0;
        vector<vector<string>> mem;
        int64_t limit = 1000000000;
        for (int64_t i = 0; i < limit; ++i) {
            if (m.find(v) != m.end()) {
                v = m[v];
                if (zero_index == 0) {
                    zero_index = i;
                } else if (zero_index && v == mem[0]) {
                    zero_index = i;
                    break;
                }
                mem.push_back(v);
            } else {
                auto vv = v;
                tiltNorth(v);
                tiltWest(v);
                tiltSouth(v);
                tiltEast(v);
                m[vv] = v;
                mem.clear();
            }
        }
        auto index = (limit - zero_index - 1) % mem.size();
        v = mem[index];
        for (int y = v.size() - 1; y >= 0; --y) {
            int cnt = 0;
            for (int x = 0; x < v[y].size(); ++x) {
                if (v[y][x] == 'O') {
                    sum += (v.size() - y);
                }
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
