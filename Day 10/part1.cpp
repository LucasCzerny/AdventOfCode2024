#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "lib.hpp"

struct Position {
    int x, y;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    int& operator[](int index) {
        return index == 0 ? x : y;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& p) const {
            return std::hash<int>()(p.x << 1 ^ p.y);
        }
    };
}

// good ol' dfs
std::unordered_set<Position> find_reachable_9s(const Position& p, const std::vector<std::string>& grid, std::unordered_map<Position, std::unordered_set<Position>>& reachable_9s) {
    static const size_t grid_width = grid[0].size();
    static const size_t grid_height = grid.size();

    if (!reachable_9s[p].empty()) {
        return reachable_9s[p];
    }

    const char current_level = grid[p.y][p.x];

    if (current_level == '9') {
        return { p };
    }

    std::unordered_set<Position> reachable;

    for (int delta_coord = 0; delta_coord < 2; delta_coord++) {
        for (int delta = -1; delta <= 1; delta += 2) {
            Position neighbor = p;
            neighbor[delta_coord] += delta;

            if (neighbor[delta_coord] < 0 || neighbor[delta_coord] >= (delta_coord == 0 ? grid_width : grid_height)) continue;
            if (grid[neighbor.y][neighbor.x] != current_level + 1) continue;

            std::unordered_set<Position> new_9s = find_reachable_9s(neighbor, grid, reachable_9s);
            reachable.insert(new_9s.begin(), new_9s.end());
        }
    }

    reachable_9s[p] = reachable;
    return reachable;
}

int solve(const std::string& input) {
    const std::vector<std::string> grid = lib::split_lines(input);
    const size_t grid_width = grid[0].size();
    const size_t grid_height = grid.size();

    std::unordered_map<Position, std::unordered_set<Position>> reachable_9s;
    int nr_of_paths = 0;
    
    for (int y = 0; y < grid_height; y++) {
        for (int x = 0; x < grid_width; x++) {
            if (grid[y][x] != '0') continue;

            nr_of_paths += find_reachable_9s(Position{ x, y }, grid, reachable_9s).size();
        }
    }

    return nr_of_paths;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}