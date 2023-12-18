#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
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
        int64_t cons;
        Point() {}
        Point(int64_t x, int64_t y, Direction dir, int64_t cons)
            : x(x), y(y), dir(dir), cons(cons) {}
        bool operator==(const Point &p) const {
            return x == p.x && y == p.y && dir == p.dir && cons == p.cons;
        }
        struct HashPoint {
            size_t operator()(const Point &p) const {
                auto hash1 = hash<int64_t>{}(p.x);
                auto hash2 = hash<int64_t>{}(-p.y);
                auto hash3 = hash<int64_t>{}(p.dir) << 2;
                auto hash4 = hash<int64_t>{}(-p.cons + 1) * 2 << 3;
                return hash1 ^ hash2 ^ hash3 ^ hash4;
            }
        };
    };

    int64_t min_heat_loss = INT32_MAX;

    int64_t traversal(const vector<vector<int64_t>> &v,
                      unordered_map<Point, int64_t, Point::HashPoint> &m,
                      Point p, int64_t current) {
        // int64_t rv = INT64_MAX;
        // for (int i = 0; i < 4; ++i) {
        //     if (abs(p.dir - i) == 2) {
        //         continue;
        //     }
        //     if (i == p.dir) {
        //         for (int j = p.cons; j < 3; ++j) {
        //             auto pp = p;
        //             pp.cons = j;
        //             if (m.find(pp) != m.end()) {
        //                 rv = min(rv, m[pp]);
        //             }
        //         }
        //     } else {
        //         for (int j = 0; j < 3; ++j) {
        //             auto pp = p;
        //             pp.dir = static_cast<Direction>(i);
        //             pp.cons = j;
        //             if (m.find(pp) != m.end()) {
        //                 rv = min(rv, m[pp]);
        //             }
        //         }
        //     }
        // }
        // if (rv != INT64_MAX) {
        //     return rv;
        // }
        if (m.find(p) != m.end()) {
            return m[p];
        }
        if (p.x >= v.front().size() || p.y >= v.size() || p.x < 0 || p.y < 0) {
            return INT64_MAX;
        } else if (p.x == v.back().size() - 1 && p.y == v.size() - 1) {
            min_heat_loss = min(current + v[p.y][p.x], min_heat_loss);
            return v[p.y][p.x];
        }
        current += v[p.y][p.x];
        if (current >= min_heat_loss) {
            // m[p] = INT64_MAX;
            return INT64_MAX;
        }
        vector<int64_t> r(3, INT64_MAX);
        vector<Point> rp(3);
        if (p.dir == right) {
            rp[0] = {p.x + 1, p.y, right, p.cons + 1};
            rp[1] = {p.x, p.y + 1, down, 0};
            rp[2] = {p.x, p.y - 1, up, 0};
        } else if (p.dir == down) {
            rp[0] = {p.x, p.y + 1, down, p.cons + 1};
            rp[1] = {p.x + 1, p.y, right, 0};
            rp[2] = {p.x - 1, p.y, left, 0};
        } else if (p.dir == left) {
            rp[0] = {p.x - 1, p.y, left, p.cons + 1};
            rp[1] = {p.x, p.y + 1, down, 0};
            rp[2] = {p.x, p.y - 1, up, 0};
        } else if (p.dir == up) {
            rp[0] = {p.x, p.y - 1, up, p.cons + 1};
            rp[1] = {p.x + 1, p.y, right, 0};
            rp[2] = {p.x - 1, p.y, left, 0};
        }

        if (p.cons < 2) {
            r[0] = traversal(v, m, rp[0], current);
        }
        r[1] = traversal(v, m, rp[1], current);
        r[2] = traversal(v, m, rp[2], current);

        auto min_path = min_element(r.begin(), r.end());
        if (*min_path == INT64_MAX) return INT64_MAX;

        auto heat = *min_path + v[p.y][p.x];
        m[p] = heat;
        min_heat_loss = min(heat + current - v[p.y][p.x], min_heat_loss);
        return heat;
    }

    struct Cell {
        int64_t row, col, dist, consecutiveMoves, lastMoveDirection;

        Cell(int64_t r, int64_t c, int64_t d, int64_t cm, int64_t lmd)
            : row(r),
              col(c),
              dist(d),
              consecutiveMoves(cm),
              lastMoveDirection(lmd) {}
    };

    bool isValid(int64_t row, int64_t col, int64_t numRows, int64_t numCols,
                 int64_t lastMoveDirection) {
        return (row >= 0 && row < numRows && col >= 0 && col < numCols);
    }

    int64_t dijkstraShortestPath(vector<vector<int64_t>> &grid) {
        int64_t numRows = grid.size();
        int64_t numCols = grid[0].size();

        vector<vector<int64_t>> dist(numRows,
                                     vector<int64_t>(numCols, INT64_MAX));

        auto compare = [](Cell a, Cell b) { return a.dist > b.dist; };

        priority_queue<Cell, vector<Cell>, decltype(compare)> pq(compare);

        pq.push(Cell(0, 0, grid[0][0], 0, 0));
        dist[0][0] = grid[0][0];

        int64_t rowMoves[] = {0, 1, -1, 0};
        int64_t colMoves[] = {1, 0, 0, -1};

        while (!pq.empty()) {
            Cell current = pq.top();
            pq.pop();

            for (int64_t i = 0; i < 4; ++i) {
                int64_t newRow = current.row + rowMoves[i];
                int64_t newCol = current.col + colMoves[i];

                if (isValid(newRow, newCol, numRows, numCols,
                            current.lastMoveDirection)) {
                    int64_t newDist = current.dist + grid[newRow][newCol];
                    int64_t newConsecutiveMoves =
                        (i == current.lastMoveDirection)
                            ? current.consecutiveMoves + 1
                            : 1;

                    if (newConsecutiveMoves <= 3 &&
                        newDist < dist[newRow][newCol]) {
                        dist[newRow][newCol] = newDist;
                        pq.push(Cell(newRow, newCol, newDist,
                                     newConsecutiveMoves, i));
                    }
                }
            }
        }

        return dist[numRows - 1][numCols - 1];
    }

public:
    int64_t solve(istream &input) override {
        string line;
        vector<vector<int64_t>> v;
        while (getline(input, line)) {
            vector<int64_t> vv;
            for (auto c : line) {
                vv.push_back(c - '0');
            }
            v.push_back(vv);
        }
        unordered_map<Point, int64_t, Point::HashPoint> m;
        // auto rv = traversal(v, m, {0, 0, right, -1}, 0);
        auto rv = dijkstraShortestPath(v);
        rv -= v[0][0];
        return rv;
    }
};

class Puzzle2 : public Puzzle {
public:
    int64_t solve(istream &input) override {
        int64_t sum = 0;
        string line;
        while (getline(input, line)) {
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
