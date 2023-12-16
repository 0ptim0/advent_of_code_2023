#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class Puzzle {
public:
    virtual int64_t solve(istream &input) = 0;
};

class Puzzle1 : public Puzzle {
private:
    enum Direction { right, down, left, up };

    struct Point {
        int64_t x;
        int64_t y;
        Direction dir;
        Point() {}
        Point(int64_t x, int64_t y, Direction dir) : x(x), y(y), dir(dir) {}
        bool operator==(const Point &p) const {
            return x == p.x && y == p.y && dir == p.dir;
        }
        struct HashPoint {
            size_t operator()(const Point &p) const {
                auto hash1 = hash<int64_t>{}(p.x);
                auto hash2 = hash<int64_t>{}(p.y) << 1;
                auto hash3 = hash<int64_t>{}(p.dir) << 2;
                return hash1 ^ hash2 ^ hash3;
            }
        };
    };

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<string> v;
        while (getline(input, line)) {
            v.push_back(line);
        }
        deque<Point> deq;
        unordered_set<Point, Point::HashPoint> s;
        deq.push_back({0, 0, right});
        while (!deq.empty()) {
            auto p = deq.front();
            deq.pop_front();
            if (p.x >= v[0].size() || p.x < 0 || p.y >= v.size() || p.y < 0 ||
                s.find(p) != s.end()) {
                continue;
            } else {
                if (v[p.y][p.x] == '|' && (p.dir == right || p.dir == left)) {
                    deq.push_back({p.x, p.y - 1, up});
                    deq.push_back({p.x, p.y + 1, down});
                } else if (v[p.y][p.x] == '-' &&
                           (p.dir == down || p.dir == up)) {
                    deq.push_back({p.x - 1, p.y, left});
                    deq.push_back({p.x + 1, p.y, right});
                } else if (v[p.y][p.x] == '/') {
                    if (p.dir == right) {
                        deq.push_back({p.x, p.y - 1, up});
                    } else if (p.dir == down) {
                        deq.push_back({p.x - 1, p.y, left});
                    } else if (p.dir == left) {
                        deq.push_back({p.x, p.y + 1, down});
                    } else {
                        deq.push_back({p.x + 1, p.y, right});
                    }
                } else if (v[p.y][p.x] == '\\') {
                    if (p.dir == right) {
                        deq.push_back({p.x, p.y + 1, down});
                    } else if (p.dir == down) {
                        deq.push_back({p.x + 1, p.y, right});
                    } else if (p.dir == left) {
                        deq.push_back({p.x, p.y - 1, up});
                    } else {
                        deq.push_back({p.x - 1, p.y, left});
                    }
                } else if (p.dir == right) {
                    deq.push_back({p.x + 1, p.y, right});
                } else if (p.dir == down) {
                    deq.push_back({p.x, p.y + 1, down});
                } else if (p.dir == left) {
                    deq.push_back({p.x - 1, p.y, left});
                } else {
                    deq.push_back({p.x, p.y - 1, up});
                }
            }
            s.insert(p);
        }
        unordered_set<Point, Point::HashPoint> ss;
        for (auto e : s) {
            ss.insert({e.x, e.y, right});
        }
        return ss.size();
    }
};

class Puzzle2 : public Puzzle {
private:
    enum Direction { right, down, left, up };

    struct Point {
        int64_t x;
        int64_t y;
        Direction dir;
        Point() {}
        Point(int64_t x, int64_t y, Direction dir) : x(x), y(y), dir(dir) {}
        bool operator==(const Point &p) const {
            return x == p.x && y == p.y && dir == p.dir;
        }
        struct HashPoint {
            size_t operator()(const Point &p) const {
                auto hash1 = hash<int64_t>{}(p.x);
                auto hash2 = hash<int64_t>{}(p.y) << 1;
                auto hash3 = hash<int64_t>{}(p.dir) << 2;
                return hash1 ^ hash2 ^ hash3;
            }
        };
    };

private:
    int64_t howManyEnergized(const vector<string> &v, Point initial) {
        deque<Point> deq;
        unordered_set<Point, Point::HashPoint> s;
        deq.push_back(initial);
        while (!deq.empty()) {
            auto p = deq.front();
            deq.pop_front();
            if (p.x >= v[0].size() || p.x < 0 || p.y >= v.size() || p.y < 0 ||
                s.find(p) != s.end()) {
                continue;
            } else {
                if (v[p.y][p.x] == '|' && (p.dir == right || p.dir == left)) {
                    deq.push_back({p.x, p.y - 1, up});
                    deq.push_back({p.x, p.y + 1, down});
                } else if (v[p.y][p.x] == '-' &&
                           (p.dir == down || p.dir == up)) {
                    deq.push_back({p.x - 1, p.y, left});
                    deq.push_back({p.x + 1, p.y, right});
                } else if (v[p.y][p.x] == '/') {
                    if (p.dir == right) {
                        deq.push_back({p.x, p.y - 1, up});
                    } else if (p.dir == down) {
                        deq.push_back({p.x - 1, p.y, left});
                    } else if (p.dir == left) {
                        deq.push_back({p.x, p.y + 1, down});
                    } else {
                        deq.push_back({p.x + 1, p.y, right});
                    }
                } else if (v[p.y][p.x] == '\\') {
                    if (p.dir == right) {
                        deq.push_back({p.x, p.y + 1, down});
                    } else if (p.dir == down) {
                        deq.push_back({p.x + 1, p.y, right});
                    } else if (p.dir == left) {
                        deq.push_back({p.x, p.y - 1, up});
                    } else {
                        deq.push_back({p.x - 1, p.y, left});
                    }
                } else if (p.dir == right) {
                    deq.push_back({p.x + 1, p.y, right});
                } else if (p.dir == down) {
                    deq.push_back({p.x, p.y + 1, down});
                } else if (p.dir == left) {
                    deq.push_back({p.x - 1, p.y, left});
                } else {
                    deq.push_back({p.x, p.y - 1, up});
                }
            }
            s.insert(p);
        }
        unordered_set<Point, Point::HashPoint> ss;
        for (auto e : s) {
            ss.insert({e.x, e.y, right});
        }
        return ss.size();
    }

public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        vector<string> v;
        while (getline(input, line)) {
            v.push_back(line);
        }
        int64_t rv = 0;
        for (int64_t i = 0; i < v.size(); ++i) {
            rv = max(rv, howManyEnergized(v, {0, i, right}));
            rv = max(rv, howManyEnergized(v, {v[0].size() - 1, i, left}));
        }
        for (int64_t i = 0; i < v[0].size(); ++i) {
            rv = max(rv, howManyEnergized(v, {i, 0, down}));
            rv = max(rv, howManyEnergized(v, {i, v.size() - 1, up}));
        }
        return rv;
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
