#include <errno.h>
#include <limits.h>
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Puzzle {
public:
    virtual int64_t solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
public:
    int64_t solve(istream &input) override {
        vector<int64_t> v;
        string line;
        char *token = nullptr;
        getline(input, line);
        token = strtok(line.data(), " ");
        while ((token = strtok(nullptr, " ")) != nullptr) {
            v.push_back(atol(token));
        }
        vector<int64_t> tmp = v;
        while (getline(input, line)) {
            if (line.length() == 0) {
                v = tmp;
            } else if (isdigit(line[0])) {
                token = strtok(line.data(), " ");
                int64_t dest = atol(token);
                token = strtok(nullptr, " ");
                int64_t src_start = atol(token);
                token = strtok(nullptr, " ");
                int64_t range = atol(token);
                int64_t src_end = src_start + range;
                for (size_t i = 0; i < v.size(); ++i) {
                    int64_t src_current = v[i];
                    if (src_current >= src_start && src_current < src_end) {
                        int64_t offset = src_current - src_start;
                        tmp[i] = dest + offset;
                    }
                }
            }
        }
        v = tmp;
        return *(min_element(v.begin(), v.end()));
    }
};

class Puzzle2 : public Puzzle {
public:
    int64_t solve(istream &input) override {
        vector<pair<int64_t, int64_t>> v;
        string line;
        char *token = nullptr;
        getline(input, line);
        token = strtok(line.data(), " ");
        while ((token = strtok(nullptr, " ")) != nullptr) {
            int64_t start = atol(token);
            token = strtok(nullptr, " ");
            int64_t length = atol(token);
            v.push_back({start, start + length - 1});
        }
        vector<pair<int64_t, int64_t>> tmp = v;
        while (getline(input, line)) {
            if (line.length() == 0) {
                v = tmp;
            } else if (isdigit(line[0])) {
                token = strtok(line.data(), " ");
                int64_t dest = atol(token);
                token = strtok(nullptr, " ");
                int64_t src_start = atol(token);
                token = strtok(nullptr, " ");
                int64_t length = atol(token);
                int64_t src_end = src_start + length - 1;
                for (size_t i = 0; i < v.size(); ++i) {
                    int64_t off_1 = v[i].first - src_start;
                    int64_t off_2 = v[i].second - src_end;
                    int64_t l = v[i].second - v[i].first;
                    if (src_start > v[i].second || src_end < v[i].first) {
                        continue;
                    }
                    if (off_1 >= 0 && off_2 <= 0) {
                        tmp[i].first = dest + off_1;
                        tmp[i].second = tmp[i].first + l;
                        printf("#1. %d. [%ld, %ld] -> [%ld, %ld]\n", line_num, v[i].first, v[i].second, tmp[i].first, tmp[i].second);
                    } else if (off_1 < 0 && off_2 <= 0) {
                        tmp[i].first = dest;
                        tmp[i].second = dest + l - abs(off_1); 
                        v.push_back({v[i].first, v[i].first + abs(off_1) - 1});
                        tmp.push_back({v[i].first, v[i].first + abs(off_1) - 1});
                        printf("#2. %d. [%ld, %ld] -> [%ld, %ld], [%ld, %ld]\n", line_num, v[i].first, v[i].second, tmp[i].first, tmp[i].second, v.back().first, v.back().second);
                    } else if (off_1 >= 0 && off_2 > 0) {
                        tmp[i].first = dest + off_1;
                        tmp[i].second = dest + length - 1;
                                                v.push_back({v[i].second - abs(off_2) + 1, v[i].second});
                        tmp.push_back({v[i].second - abs(off_2) + 1, v[i].second});
                        printf("#3. %d. [%ld, %ld] -> [%ld, %ld], [%ld, %ld]\n", line_num, v[i].first, v[i].second, tmp[i].first, tmp[i].second, v.back().first, v.back().second);
                    } else if (off_1 < 0 && off_2 > 0) {
                        tmp[i].first = dest;
                        tmp[i].second = dest + length - 1;
                        v.push_back({v[i].first, v[i].first + abs(off_1) - 1});
                        tmp.push_back({v[i].first, v[i].first + abs(off_1) - 1});
                        v.push_back({v[i].second - abs(off_2) + 1, v[i].second});
                        tmp.push_back({v[i].second - abs(off_2) + 1, v[i].second});
                        printf("#4. %d. [%ld, %ld] -> [%ld, %ld], [%ld, %ld], [%ld, %ld]\n", line_num, v[i].first, v[i].second, tmp[i].first, tmp[i].second, v.end()->first, v.end()->second, (v.end() - 1)->first, (v.end() - 1)->second);
                    }
                    v[i].first = -1;
                    v[i].second = -1;
                }
            } else {
                cout << endl << line << endl;
                for (size_t i = 0; i < v.size(); ++i) {
                    printf("[%ld, %ld]\n", v[i].first, v[i].second);
                }
            }
        }
        v = tmp;
        int64_t location = INT64_MAX;
        for (auto it = v.begin(); it != v.end(); ++it) {
            location = min(it->first, location);
        }
        return location;
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