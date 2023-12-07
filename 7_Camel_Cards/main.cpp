#include <errno.h>
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class Puzzle {
public:
    virtual int solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
private:
    enum CardType {
        high_card = 1,
        one_pair = 2,
        two_pair = 3,
        three_of_a_kind = 4,
        full_house = 5,
        four_of_a_kind = 6,
        five_of_a_kind = 7,
    };

    int getType(string str) {
        unordered_map<char, int> m;
        for (auto c : str) {
            if (m.find(c) != m.end()) {
                m[c]++;
            } else {
                m.insert({c, 1});
            }
        }
        if (m.size() == 1) {
            return five_of_a_kind;
        } else if (m.size() == 2) {
            if (m.begin()->second == 4 || m.begin()->second == 1) {
                return four_of_a_kind;
            } else {
                return full_house;
            }
        } else if (m.size() == 3) {
            for (auto it = m.begin(); it != m.end(); ++it) {
                if (it->second == 3) {
                    return three_of_a_kind;
                }
            }
            return two_pair;
        } else if (m.size() == 4) {
            return one_pair;
        }
        return high_card;
    }

public:
    int solve(istream &input) override {
        map<string, int> m;
        int sum = 0;
        string line;
        while (getline(input, line)) {
            string card = string(strtok(line.data(), " "));
            int type = getType(card);
            int value = atoi(strtok(nullptr, " "));
            replace(card.begin(), card.end(), 'A', 'Z');
            replace(card.begin(), card.end(), 'K', 'Y');
            replace(card.begin(), card.end(), 'Q', 'X');
            replace(card.begin(), card.end(), 'J', 'W');
            replace(card.begin(), card.end(), 'T', 'V');
            replace(card.begin(), card.end(), '1', 'A');
            replace(card.begin(), card.end(), '2', 'B');
            replace(card.begin(), card.end(), '3', 'C');
            replace(card.begin(), card.end(), '4', 'D');
            replace(card.begin(), card.end(), '5', 'E');
            replace(card.begin(), card.end(), '6', 'F');
            replace(card.begin(), card.end(), '7', 'G');
            replace(card.begin(), card.end(), '8', 'H');
            replace(card.begin(), card.end(), '9', 'I');
            m.insert({to_string(type) + "_" + card, value});
        }
        int i = 1;
        for (auto it = m.begin(); it != m.end(); ++it) {
            sum += it->second * i;
            i++;
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
private:
    enum CardType {
        high_card = 1,
        one_pair = 2,
        two_pair = 3,
        three_of_a_kind = 4,
        full_house = 5,
        four_of_a_kind = 6,
        five_of_a_kind = 7,
    };

    int getType(string str) {
        unordered_map<char, int> m;
        for (auto c : str) {
            if (m.find(c) != m.end()) {
                m[c]++;
            } else {
                m.insert({c, 1});
            }
        }
        if (m.size() == 1) {
            return five_of_a_kind;
        } else if (m.size() == 2) {
            if (m.find('J') != m.end()) {
                return five_of_a_kind;
            } else if (m.begin()->second == 4 || m.begin()->second == 1) {
                return four_of_a_kind;
            } else {
                return full_house;
            }
        } else if (m.size() == 3) {
            for (auto it = m.begin(); it != m.end(); ++it) {
                if (it->second == 3) {
                    if (m.find('J') != m.end()) {
                        return four_of_a_kind;
                    } else {
                        return three_of_a_kind;
                    }
                }
            }
            if (m.find('J') != m.end()) {
                if (m['J'] == 1) {
                    return full_house;
                } else {
                    return four_of_a_kind;
                }
            } else {
                return two_pair;
            }
        } else if (m.size() == 4) {
            if (m.find('J') != m.end()) {
                return three_of_a_kind;
            } else {
                return one_pair;
            }
        }
        if (m.find('J') != m.end()) {
            return one_pair;
        }
        return high_card;
    }

public:
    int solve(istream &input) override {
        map<string, int> m;
        int sum = 0;
        string line;
        while (getline(input, line)) {
            string card = string(strtok(line.data(), " "));
            int type = getType(card);
            int value = atoi(strtok(nullptr, " "));
            replace(card.begin(), card.end(), 'A', 'Z');
            replace(card.begin(), card.end(), 'K', 'Y');
            replace(card.begin(), card.end(), 'Q', 'X');
            replace(card.begin(), card.end(), 'T', 'V');
            replace(card.begin(), card.end(), 'J', 'A');
            replace(card.begin(), card.end(), '1', 'B');
            replace(card.begin(), card.end(), '2', 'C');
            replace(card.begin(), card.end(), '3', 'D');
            replace(card.begin(), card.end(), '4', 'E');
            replace(card.begin(), card.end(), '5', 'F');
            replace(card.begin(), card.end(), '6', 'G');
            replace(card.begin(), card.end(), '7', 'H');
            replace(card.begin(), card.end(), '8', 'I');
            replace(card.begin(), card.end(), '9', 'J');
            m.insert({to_string(type) + "_" + card, value});
        }
        int i = 1;
        for (auto it = m.begin(); it != m.end(); ++it) {
            sum += it->second * i;
            i++;
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
