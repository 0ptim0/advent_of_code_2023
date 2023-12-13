#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

class Puzzle {
public:
    virtual int64_t solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
private:
    bool check(const string &initial, const string &option) {
        for (int64_t i = 0; i < initial.size(); ++i) {
            if (initial[i] != option[i] && initial[i] != '?') {
                return false;
            }
        }
        return true;
    }

    int64_t traversal(const vector<int> &pattern, const string &map,
                      int64_t pos, int64_t pattern_num, string tmp) {
        int64_t rv = 0;
        for (int64_t i = pos; i + pattern[pattern_num] <= map.size(); ++i) {
            auto t = tmp;
            for (int64_t j = 0; j < pattern[pattern_num]; j++) {
                t[i + j] = '#';
            }
            if (pattern_num == pattern.size() - 1) {
                if (check(map, t)) {
                    rv++;
                }
            } else {
                rv += traversal(pattern, map, i + pattern[pattern_num] + 1,
                                pattern_num + 1, t);
            }
        }
        return rv;
    }

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        while (getline(input, line)) {
            auto s = stringstream(line);
            string map, pattern;
            getline(s, map, ' ');
            getline(s, pattern, ' ');
            vector<int> patternv;
            s = stringstream(pattern);
            string tmp;
            while (getline(s, tmp, ',')) {
                patternv.push_back(stoi(tmp));
            }
            string option;
            for (auto c : map) {
                option.push_back('.');
            }
            sum += traversal(patternv, map, 0, 0, option);
        }
        return sum;
    }
};

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};

class Puzzle2 : public Puzzle {
private:
    bool check(const string &initial, const string &option) {
        for (int64_t i = 0; i < initial.size(); ++i) {
            if (initial[i] != option[i] && initial[i] != '?') {
                return false;
            }
        }
        return true;
    }

    struct Info {
        int64_t f;
        int64_t b;
        int64_t fb;
        Info() : f(0), b(0), fb(0) {}
    };

    int64_t traversal(const vector<int> &pattern, const string &map,
                      int64_t pos, int64_t pattern_num, string tmp,
                      unordered_map<string, int64_t> &m) {
        int64_t rv = 0;
        int64_t min_size = 0;
        for (int i = pattern_num; i < pattern.size(); ++i) {
            min_size += pattern[i] + 1;
        }
        min_size--;
        for (int64_t i = pos; i + min_size <= map.size(); ++i) {
            auto t = tmp;
            bool im = false;
            for (int64_t j = 0; j < pattern[pattern_num]; j++) {
                if (map[i + j] == '.') {
                    im = true;
                    // i += j;
                    break;
                }
            }
            if (im) {
                continue;
            }
            if (map[i + pattern[pattern_num]] == '#') {
                continue;
            }
            for (int64_t j = 0; j < pattern[pattern_num]; j++) {
                t[i + j] = '#';
            }
            if (!check(map.substr(0, i + pattern[pattern_num]),
                       t.substr(0, i + pattern[pattern_num]))) {
                continue;
            }
            string key = to_string(i) + '_' + to_string(pattern_num);
            if (m.find(key) != m.end()) {
                rv += m[key];
            } else if (pattern_num == pattern.size() - 1) {
                // cout << t << endl;
                if (check(map, t)) {
                    // if (t.front() == '#' && t.back() == '#') {
                    //     info.fb++;
                    //     // info.f++;
                    //     // info.b++;
                    // } else if (t.front() == '#') {
                    //     info.f++;
                    // } else if (t.back() == '#') {
                    //     info.b++;
                    // }
                    rv++;
                    m[key] = 1;
                } else {
                    m[key] = 0;
                }

            } else {
                auto rvv = traversal(pattern, map, i + pattern[pattern_num] + 1,
                                pattern_num + 1, t, m);
                m[key] = rvv;
                rv += rvv;
            }
        }
        return rv;
    }

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        while (getline(input, line)) {
            auto s = stringstream(line);
            string map, pattern;
            getline(s, map, ' ');
            getline(s, pattern, ' ');
            vector<int> patternv;
            string tmp;
            auto map_tmp = map;
            auto pattern_tmp = pattern;
            for (int64_t i = 0; i < 4; ++i) {
                map += "?";
                map += map_tmp;
                pattern += ",";
                pattern += pattern_tmp;
            }
            s = stringstream(pattern);
            while (getline(s, tmp, ',')) {
                patternv.push_back(stoi(tmp));
            }
            string option;
            for (auto c : map) {
                option.push_back('.');
            }
            Info info;
            unordered_map<string, int64_t> m;
            int64_t o = traversal(patternv, map, 0, 0, option, m);
            // Info i1;
            // Info i21;
            // Info i22;
            // Info i2;
            // int64_t n = traversal(patternv, map, 0, 0, option, i1);
            // auto map1 = map;
            // auto map2 = map;
            // option.push_back('.');
            // map1.insert(0, 1, '?');
            // map2.push_back('?');
            // int64_t q1 = traversal(patternv, map1, 0, 0, option, i21);
            // int64_t q2 = traversal(patternv, map2, 0, 0, option, i22);
            // int64_t q = 0;
            // int64_t o = 0;
            // if (q1 >= q2) {
            //     q = q1;
            //     i2 = i21;
            //     o += i1.fb * i1.fb * i1.fb * i1.fb * i1.fb;
            //     o += (q - i2.b - i2.fb) * (q - i2.b - i2.fb) * (q - i2.b -
            //     i2.fb) * (q - i2.b - i2.fb) * (i1.f); o += (q - i2.fb) * (q -
            //     i2.fb) * (q - i2.fb) * (q - i2.fb) * (n - i1.f - i1.fb);
            // } else {
            //     q = q2;
            //     i2 = i22;
            //     o += i1.fb * i1.fb * i1.fb * i1.fb * i1.fb;
            //     o += (i1.b) * (q - i2.f - i2.fb) * (q - i2.f - i2.fb) * (q -
            //     i2.f - i2.fb) * (q - i2.f - i2.fb); o += (n - i1.b - i1.fb) *
            //     (q - i2.fb) * (q - i2.fb) * (q - i2.fb) * (q - i2.fb);
            // }
            cout << o << endl;
            sum += o;
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
