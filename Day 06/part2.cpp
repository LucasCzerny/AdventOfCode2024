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

std::set<Position> get_path(std::vector<std::string>& grid, int grid_width, int grid_height, Position initial_position) {
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

    return visited_squares;
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

    std::set<Position> visited_squares = get_path(grid, grid_width, grid_height, initial_position);
    int loop_counter = 0;

    // the new obstacle can only be at a square that was visited
    int index = 0;
    for (Position new_obstacle : visited_squares) {
        grid[new_obstacle.second][new_obstacle.first] = '#';

        Position current_position = initial_position;
        Direction current_direction = Direction::up;

        Position next_position;
        std::set<std::pair<Position, Direction>> previous_states;

        int prev = loop_counter;
        while ((next_position = move(current_position, current_direction)), is_inside(next_position, grid_width, grid_height)) {

            // epic collision detection
            if (grid[next_position.second][next_position.first] == '#') {
                current_direction = turn(current_direction);
                continue;
            }

            current_position = next_position;
            std::pair<Position, Direction> state = { current_position, current_direction };

            // Loop!!! :o
            if (previous_states.find(state) != previous_states.end()) {
                loop_counter++;
                break;
            }

            if (current_position.first != initial_position.first || current_position.second != initial_position.second) {
                previous_states.insert(state);
            }
        }

        grid[new_obstacle.second][new_obstacle.first] = '.';
    }

    return loop_counter;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10 runs: " << lib::average_time(std::bind(solve, input), 10) << '\n';
}