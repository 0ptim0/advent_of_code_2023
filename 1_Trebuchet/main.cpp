#include <errno.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Puzzle {
public:
    virtual int solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
public:
    int solve(istream &input) override {
        string line;
        int sum = 0;
        while (getline(input, line)) {
            string str_num = "00";
            for (auto c : line) {
                if (isdigit(c)) {
                    str_num[1] = c;
                    str_num[0] = str_num[0] > '0' ? str_num[0] : c;
                }
            }
            int num = stoi(str_num);
            sum += num;
        }
        return sum;
    }
};

class Puzzle2 : public Puzzle {
private:
    map<string, char> m = {{"one", '1'},   {"two", '2'},   {"three", '3'},
                           {"four", '4'},  {"five", '5'},  {"six", '6'},
                           {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};

public:
    int solve(istream &input) override {
        string line;
        int sum = 0;
        while (getline(input, line)) {
            string str_num = "00";
            for (int i = 0; i < line.length(); ++i) {
                char c = line[i];
                if (isdigit(c)) {
                    str_num[1] = c;
                    str_num[0] = str_num[0] > '0' ? str_num[0] : str_num[1];
                } else {
                    for (auto &p : m) {
                        string substr = line.substr(i, p.first.length());
                        if (m.find(substr) != m.end()) {
                            str_num[1] = m[substr];
                            str_num[0] =
                                str_num[0] > '0' ? str_num[0] : str_num[1];
                            break;
                        }
                    }
                }
            }
            int num = stoi(str_num);
            sum += num;
        }
        return sum;
    }
};

class Trebuchet {
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
    Trebuchet trebuchet;
    trebuchet.setStrategy(new Puzzle1);
    trebuchet.solve("input.txt", "output_1.txt");
    trebuchet.setStrategy(new Puzzle2);
    trebuchet.solve("input.txt", "output_2.txt");
    return 0;
}
