#include <iostream>
#include <unordered_map>

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

int find_nr_of_paths(const Position& p, const std::vector<std::string>& grid, std::unordered_map<Position, int>& nr_paths_to_9) {
    static const size_t grid_width = grid[0].size();
    static const size_t grid_height = grid.size();

    if (nr_paths_to_9[p] != 0) {
        return nr_paths_to_9[p];
    }

    const char current_level = grid[p.y][p.x];

    if (current_level == '9') {
        return 1;
    }

    int nr_of_paths = 0;

    for (int delta_coord = 0; delta_coord < 2; delta_coord++) {
        for (int delta = -1; delta <= 1; delta += 2) {
            Position neighbor = p;
            neighbor[delta_coord] += delta;

            if (neighbor[delta_coord] < 0 || neighbor[delta_coord] >= (delta_coord == 0 ? grid_width : grid_height)) continue;
            if (grid[neighbor.y][neighbor.x] != current_level + 1) continue;

            nr_of_paths += find_nr_of_paths(neighbor, grid, nr_paths_to_9);
        }
    }

    nr_paths_to_9[p] = nr_of_paths;
    return nr_of_paths;
}

int solve(const std::string& input) {
    const std::vector<std::string> grid = lib::split_lines(input);
    const size_t grid_width = grid[0].size();
    const size_t grid_height = grid.size();

    std::unordered_map<Position, int> nr_paths_to_9;
    int nr_of_paths = 0;
    
    for (int y = 0; y < grid_height; y++) {
        for (int x = 0; x < grid_width; x++) {
            if (grid[y][x] != '0') continue;

            nr_of_paths += find_nr_of_paths(Position{ x, y }, grid, nr_paths_to_9);
        }
    }

    return nr_of_paths;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}