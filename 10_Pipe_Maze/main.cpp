#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Puzzle {
public:
    virtual int64_t solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
private:
    vector<string> map;

    struct Coordinate {
        int64_t x = 0;
        int64_t y = 0;
        Coordinate() {}
        Coordinate(int64_t x, int64_t y) : x(x), y(y) {}
        Coordinate operator-(Coordinate const &obj1) {
            Coordinate obj2;
            obj2.x = x - obj1.x;
            obj2.y = y - obj1.y;
            return obj2;
        }
        bool operator==(const Coordinate &obj) {
            return x == obj.x && y == obj.y;
        }
        bool operator!=(const Coordinate &obj) { return !(*this == obj); }
    };

    Coordinate next(Coordinate c, Coordinate p) {
        auto diff = c - p;
        auto s = map[c.y][c.x];
        if (diff == Coordinate(0, 1)) {
            if (s == '|') {
                c.y++;
            } else if (s == 'L') {
                c.x++;
            } else if (s == 'J') {
                c.x--;
            }
        } else if (diff == Coordinate(1, 0)) {
            if (s == '-') {
                c.x++;
            } else if (s == '7') {
                c.y++;
            } else if (s == 'J') {
                c.y--;
            }
        } else if (diff == Coordinate(0, -1)) {
            if (s == '|') {
                c.y--;
            } else if (s == '7') {
                c.x--;
            } else if (s == 'F') {
                c.x++;
            }

        } else if (diff == Coordinate(-1, 0)) {
            if (s == '-') {
                c.x--;
            } else if (s == 'F') {
                c.y++;
            } else if (s == 'L') {
                c.y--;
            }
        }
        return c;
    }

public:
    int64_t solve(istream &input) override {
        string line;
        Coordinate s = {-1, -1};
        int64_t step = 0;
        while (getline(input, line)) {
            if (s.x == -1) {
                auto it = find(line.begin(), line.end(), 'S');
                if (it != line.end()) {
                    s = {distance(line.begin(), it), map.size()};
                }
            }
            map.push_back(line);
        }

        auto c1 = s;
        auto c2 = s;
        if (map[s.y - 1][s.x] == '|' || map[s.y - 1][s.x] == 'F' ||
            map[s.y - 1][s.x] == '7') {
            c1.y--;
        }
        if (map[s.y][s.x + 1] == '-' || map[s.y][s.x + 1] == 'J' ||
            map[s.y][s.x + 1] == '7') {
            c2.x += c1 == s ? 0 : 1;
            c1.x += c1 == s ? 1 : 0;
        }
        if (map[s.y + 1][s.x] == '|' || map[s.y + 1][s.x] == 'J' ||
            map[s.y + 1][s.x] == 'L') {
            c2.y += c1 == s ? 0 : 1;
            c1.y += c1 == s ? 1 : 0;
        }
        if (map[s.y][s.x - 1] == '-' || map[s.y][s.x - 1] == 'L' ||
            map[s.y][s.x - 1] == 'F') {
            c2.x--;
        }
        auto p1 = s;
        auto p2 = s;
        step++;
        while (c1 != c2) {
            auto tmp1 = c1;
            auto tmp2 = c2;
            c1 = next(c1, p1);
            c2 = next(c2, p2);
            p1 = tmp1;
            p2 = tmp2;
            step++;
        }
        for (auto a : map) {
            cout << a << endl;
        }
        return step;
    }
};

class Puzzle2 : public Puzzle {
private:
    struct Coordinate {
        int64_t x = 0;
        int64_t y = 0;
        Coordinate() {}
        Coordinate(int64_t x, int64_t y) : x(x), y(y) {}
        Coordinate operator-(Coordinate const &obj1) {
            Coordinate obj2;
            obj2.x = x - obj1.x;
            obj2.y = y - obj1.y;
            return obj2;
        }
        bool operator==(const Coordinate &obj) {
            return x == obj.x && y == obj.y;
        }
        bool operator!=(const Coordinate &obj) { return !(*this == obj); }
    };

    vector<string> map;

    bool isInside(Coordinate c, const vector<Coordinate> &v) {
        int n = v.size();
        int count = 0;
        for (auto a : v) {
            if (c == a) {
                return false;
            }
        }
        for (int i = 0, j = n - 1; i < n; j = i++) {
            if (((v[i].y > c.y) != (v[j].y > c.y)) &&
                (c.x < (v[j].x - v[i].x) * (c.y - v[i].y) / (v[j].y - v[i].y) +
                           v[i].x)) {
                count++;
            }
        }

        return count % 2 == 1;
    }

    Coordinate next(Coordinate c, Coordinate p) {
        auto diff = c - p;
        auto s = map[c.y][c.x];
        if (diff == Coordinate(0, 1)) {
            if (s == '|') {
                c.y++;
            } else if (s == 'L') {
                c.x++;
            } else if (s == 'J') {
                c.x--;
            }
        } else if (diff == Coordinate(1, 0)) {
            if (s == '-') {
                c.x++;
            } else if (s == '7') {
                c.y++;
            } else if (s == 'J') {
                c.y--;
            }
        } else if (diff == Coordinate(0, -1)) {
            if (s == '|') {
                c.y--;
            } else if (s == '7') {
                c.x--;
            } else if (s == 'F') {
                c.x++;
            }

        } else if (diff == Coordinate(-1, 0)) {
            if (s == '-') {
                c.x--;
            } else if (s == 'F') {
                c.y++;
            } else if (s == 'L') {
                c.y--;
            }
        }
        return c;
    }

public:
    int64_t solve(istream &input) override {
        string line;
        Coordinate s = {-1, -1};
        int64_t step = 0;
        while (getline(input, line)) {
            if (s.x == -1) {
                auto it = find(line.begin(), line.end(), 'S');
                if (it != line.end()) {
                    s = {distance(line.begin(), it), map.size()};
                }
            }
            map.push_back(line);
        }

        auto c = s;
        if (map[s.y - 1][s.x] == '|' || map[s.y - 1][s.x] == 'F' ||
            map[s.y - 1][s.x] == '7') {
            c.y--;
        } else if (map[s.y][s.x + 1] == '-' || map[s.y][s.x + 1] == 'J' ||
                   map[s.y][s.x + 1] == '7') {
            c.x++;
        } else if (map[s.y + 1][s.x] == '|' || map[s.y + 1][s.x] == 'J' ||
                   map[s.y + 1][s.x] == 'L') {
            c.y++;
        } else if (map[s.y][s.x - 1] == '-' || map[s.y][s.x - 1] == 'L' ||
                   map[s.y][s.x - 1] == 'F') {
            c.x--;
        }
        auto p = s;
        step++;
        vector<Coordinate> v;
        while (c != s) {
            auto sym = map[c.y][c.x];
            v.push_back(Coordinate(c.x, c.y));
            auto tmp = c;
            c = next(c, p);
            p = tmp;
            step++;
        }
        int64_t count = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (isInside(Coordinate(j, i), v)) {
                    count++;
                }
            }
        }
        return count;
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
