#include <errno.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Game {
    int id;
    vector<int> rgb = {0, 0, 0};
    vector<int> limit = {12, 13, 14};

    int setWithLimit(const string &color, int num) {
        int i = 0;
        if (color == "red") {
            i = 0;
        } else if (color == "green") {
            i = 1;
        } else if (color == "blue") {
            i = 2;
        } else {
            return -1;
        }
        if (limit[i] < num) {
            return -1;
        } else {
            rgb[i] = num;
        }
        return 0;
    }

    int setWithMax(const string &color, int num) {
        int i = 0;
        if (color == "red") {
            i = 0;
        } else if (color == "green") {
            i = 1;
        } else if (color == "blue") {
            i = 2;
        } else {
            return -1;
        }
        rgb[i] = max(rgb[i], num);
        return 0;
    }

    int power() { return rgb[0] * rgb[1] * rgb[2]; }

    void clear() { rgb = {0, 0, 0}; }
};

class Puzzle {
public:
    virtual int solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
public:
    int solve(istream &input) override {
        string line;
        int sum = 0;
        bool incorrect_game = false;
        while (getline(input, line)) {
            incorrect_game = false;
            char *saveptr1 = nullptr;
            Game g = {0, {0, 0, 0}, {12, 13, 14}};
            char *token = strtok_r(line.data(), " ", &saveptr1);
            token = strtok_r(nullptr, ":", &saveptr1);
            g.id = atoi(token);
            while (token != nullptr) {
                char *saveptr2 = saveptr1;
                token = strtok_r(nullptr, ";", &saveptr1);
                if (token == nullptr) {
                    sum += g.id;
                    break;
                }

                while (token != nullptr) {
                    token = strtok_r(nullptr, " ", &saveptr2);
                    if (token == nullptr) break;
                    int num = atoi(token);
                    token = strtok_r(nullptr, ",", &saveptr2);
                    if (token == nullptr) break;
                    if (g.setWithLimit(string(token), num)) {
                        incorrect_game = true;
                        break;
                    }
                }
                token = saveptr1;
                if (incorrect_game) {
                    break;
                }
            }
            g.clear();
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
public:
    int solve(istream &input) override {
        string line;
        int sum = 0;
        bool incorrect_game = false;
        while (getline(input, line)) {
            char *saveptr1 = nullptr;
            Game g = {0, {0, 0, 0}, {12, 13, 14}};
            char *token = strtok_r(line.data(), " ", &saveptr1);
            token = strtok_r(nullptr, ":", &saveptr1);
            g.id = atoi(token);
            while (token != nullptr) {
                char *saveptr2 = saveptr1;
                token = strtok_r(nullptr, ";", &saveptr1);
                if (token == nullptr) {
                    break;
                }

                while (token != nullptr) {
                    token = strtok_r(nullptr, " ", &saveptr2);
                    if (token == nullptr) break;
                    int num = atoi(token);
                    token = strtok_r(nullptr, ",", &saveptr2);
                    if (token == nullptr) break;
                    g.setWithMax(string(token), num);
                }
                token = saveptr1;
            }
            sum += g.power();
            g.clear();
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
