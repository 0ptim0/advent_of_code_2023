#include <errno.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

class Puzzle {
public:
    virtual int solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
private:
    bool check(const string &h, const string &m, const string &l, int i) {
        bool rv = false;
        if (i >= m.length()) {
            return false;
        }
        if (h.length() != 0) {
            rv |= h[i] != '.';
        }
        if (l.length() != 0) {
            rv |= l[i] != '.';
        }
        if (!isdigit(m[i])) {
            rv |= m[i] != '.';
        }
        return rv;
    }

public:
    int solve(istream &input) override {
        int sum = 0;
        bool part_number = false;
        string line_prev, line_current, line_next;
        getline(input, line_current);
        getline(input, line_next);
        while (line_current.length()) {
            string num;
            int i = 0;
            while (i < line_current.length()) {
                if (isdigit(line_current[i])) {
                    if (!part_number && num.length() == 0 && i > 0) {
                        part_number =
                            check(line_prev, line_current, line_next, i - 1);
                    }
                    if (!part_number) {
                        part_number =
                            check(line_prev, line_current, line_next, i);
                    }
                    num.push_back(line_current[i]);
                } else {
                    if (part_number ||
                        (num.length() != 0 &&
                         check(line_prev, line_current, line_next, i))) {
                        sum += stoi(num);
                        part_number = false;
                    }
                    num.clear();
                }
                ++i;
            }
            if (part_number) {
                sum += stoi(num);
                part_number = false;
                num.clear();
            }
            line_prev = line_current;
            line_current = line_next;
            if (!getline(input, line_next)) {
                line_next.clear();
            }
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
private:
    const char *getNumStart(const char *str) {
        while (isdigit(*str)) {
            str--;
        }
        return str + 1;
    }

    string getNum(const char *str) {
        string rv;
        while (isdigit(*str)) {
            rv.push_back(*str);
            str++;
        }
        return rv;
    }

    int getProduct(const char *h, const char *m, const char *l, int i) {
        set<const char *> s;
        for (int j = i + 1; j >= i - 1; --j) {
            if (isdigit(h[j])) {
                s.insert(getNumStart(h + j));
            }
            if (isdigit(m[j])) {
                s.insert(getNumStart(m + j));
            }
            if (isdigit(l[j])) {
                s.insert(getNumStart(l + j));
            }
        }
        if (s.size() < 2) {
            return 0;
        }
        auto it = s.begin();
        string first = getNum(*it);
        ++it;
        string second = getNum(*it);
        int product = stoi(first) * stoi(second);
        cout << first << " " << second << endl;
        return product;
    }

public:
    int solve(istream &input) override {
        int sum = 0;
        bool part_number = false;
        string line_prev, line_current, line_next;
        getline(input, line_current);
        getline(input, line_next);
        while (line_current.length()) {
            for (int i = 0; i < line_current.length(); ++i) {
                if (line_current[i] == '*') {
                    sum += getProduct(line_prev.data(), line_current.data(),
                                      line_next.data(), i);
                }
            }
            line_prev = line_current;
            line_current = line_next;
            if (!getline(input, line_next)) {
                line_next.clear();
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
