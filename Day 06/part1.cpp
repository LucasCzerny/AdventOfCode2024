#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <vector>

#include "lib.hpp"

using Position = std::pair<int, int>;

enum Direction {
    up, right, down, left
};

Position move(Position& position, Direction direction) {
    constexpr std::array<Position, 4> direction_changes = {
        Position{ 0, -1 }, Position{ 1, 0 }, Position{ 0, 1 }, Position{ -1, 0 }
    };
    
    const Position change = direction_changes[direction];
    return Position {
        position.first + change.first,
        position.second + change.second
    };
}

Direction turn(Direction direction) {
    return static_cast<Direction>((direction + 1) % 4);
}

bool is_inside(Position position, int grid_width, int grid_height) {
    return position.first >= 0 && position.first < grid_width && position.second >= 0 && position.second < grid_height;
}

int solve(const std::string& input) {
    std::vector<std::string> grid = lib::split_lines(input);

    const int grid_width = grid[0].size();
    const int grid_height = grid.size();

    Position initial_position;

    // where is that stupid guard
    for (size_t i = 0; i < grid_height; i++) {
        for (size_t j = 0; j < grid_width; j++) {
            if (grid[i][j] == '^') {
                initial_position = Position{ j, i };
                break;
            }
        }
    }

    Position current_position = initial_position;
    Direction current_direction = Direction::up;
    
    Position next_position;
    std::set<Position> visited_squares;

    while ((next_position = move(current_position, current_direction)), is_inside(next_position, grid_width, grid_height)) {

        // epic collision detection
        if (grid[next_position.second][next_position.first] == '#') {
            current_direction = turn(current_direction);
            continue;
        }

        current_position = next_position;
        visited_squares.insert(current_position);
    }

    // of by one for some reason lol
    return visited_squares.size() + 1;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}