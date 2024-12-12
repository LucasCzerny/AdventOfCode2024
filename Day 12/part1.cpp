#include <iostream>
#include <numeric>
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

std::vector<size_t> find_region(const std::vector<std::string>& grid, Position position, std::unordered_map<Position, bool>& is_part_of_region) {
    static const size_t plot_size = grid.size();

    std::vector<size_t> result;

    if (is_part_of_region[position]) {
        return result;
    }

    is_part_of_region[position] = true;

    // start with 0 neighbors, 4 fences
    result.push_back(4);

    const char current_char = grid[position.y][position.x];

    for (int i = 0; i < 2; i++) {
        for (int delta = -1; delta <= 1; delta += 2) {
            // horizontal
            Position next_position = position;
            next_position[i] += delta;

            if (next_position[i] < 0 || next_position[i] >= plot_size
                || grid[next_position.y][next_position.x] != current_char
            ) {
                continue;
            }

            // new neighbor found; 1 fence less
            result[0]--;

            // the result vector of that position has already been added to another region
            // or to the current recursion call tree thingy
            if (is_part_of_region[next_position]) {
                continue;
            }

            std::vector<size_t> neighbor_result = find_region(grid, next_position, is_part_of_region);
            result.insert(result.end(), neighbor_result.begin(), neighbor_result.end());
        }
    }

    return result;
}

int solve(const std::string& input) {
    const std::vector<std::string> grid = lib::split_lines(input);
    const size_t plot_size = grid.size();

    std::unordered_map<Position, bool> is_part_of_region;

    unsigned int total_price = 0;

    for (int y = 0; y < plot_size; y++) {
        for (int x = 1; x < plot_size; x++) {
            const std::vector<size_t> region = find_region(grid, { x, y }, is_part_of_region);

            const unsigned int perimeter = region.size();
            const unsigned int nr_fences = std::accumulate(region.begin(), region.end(), 0u);

            total_price += perimeter * nr_fences;
        }
    }

    return total_price;
}

int main() {
    const std::string input = lib::load_file("sample_input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    // std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000).count() << '\n';
}