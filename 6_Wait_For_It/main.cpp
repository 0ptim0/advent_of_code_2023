#include <bits/stdc++.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Puzzle {
public:
    virtual int solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
private:
    long int getWays(long int t, long int d) {
        double D = t * t - 4 * d;
        if (D <= 0) return 0;
        double t1 = (-t + sqrt(D)) / -2;
        double t2 = (-t - sqrt(D)) / -2;
        if (ceil(t1) == t1) {
            t1 += 1.0;
        }
        if (ceil(t2) == t2) {
            t2 -= 1.0;
        }
        long int diff =
            static_cast<long int>(floor(t2)) - static_cast<long int>(ceil(t1));
        return diff + 1;
    }

public:
    int solve(istream &input) override {
        int ways = 1;
        string time, dist;
        getline(input, time);
        getline(input, dist);
        char *t = nullptr, *d = nullptr, *ptr1 = nullptr, *ptr2 = nullptr;
        t = strtok_r(time.data(), " ", &ptr1);
        d = strtok_r(dist.data(), " ", &ptr2);
        while ((t = strtok_r(nullptr, " ", &ptr1)) &&
               (d = strtok_r(nullptr, " ", &ptr2))) {
            if (isdigit(t[0]) && isdigit(d[0])) {
                int w = getWays(atoi(t), atoi(d));
                cout << w << endl;
                ways *= w;
            }
        }
        return ways;
    }
};

class Puzzle2 : public Puzzle {
private:
    long int getWays(long int t, long int d) {
        double D = t * t - 4 * d;
        if (D <= 0) return 0;
        double t1 = (-t + sqrt(D)) / -2;
        double t2 = (-t - sqrt(D)) / -2;
        if (ceil(t1) == t1) {
            t1 += 1.0;
        }
        if (ceil(t2) == t2) {
            t2 -= 1.0;
        }
        long int diff =
            static_cast<long int>(floor(t2)) - static_cast<long int>(ceil(t1));
        return diff + 1;
    }

public:
    int solve(istream &input) override {
        int ways = 1;
        string time, dist;
        string t_m, d_m;
        getline(input, time);
        getline(input, dist);
        char *t = nullptr, *d = nullptr, *ptr1 = nullptr, *ptr2 = nullptr;
        t = strtok_r(time.data(), " ", &ptr1);
        d = strtok_r(dist.data(), " ", &ptr2);
        while ((t = strtok_r(nullptr, " ", &ptr1)) &&
               (d = strtok_r(nullptr, " ", &ptr2))) {
            if (isdigit(t[0]) && isdigit(d[0])) {
                t_m.append(t);
                d_m.append(d);
            }
        }
        long int w = getWays(stol(t_m), stol(d_m));
        cout << w << endl;
        ways *= w;
        return ways;
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
