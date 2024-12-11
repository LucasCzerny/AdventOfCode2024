#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "lib.hpp"

struct Position {
    int x, y;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& p) const noexcept {
            return std::hash<int>()(p.x + p.y << 1);
        }
    };
}

std::unordered_map<char, std::vector<Position>> process_map(const std::string& input) {
    std::unordered_map<char, std::vector<Position>> char_positions;

    std::istringstream input_stream(input);
    std::string line;

    int y = 0;
    while (std::getline(input_stream, line)) {
        std::istringstream line_stream(line);
        char c;

        int x = 0;
        while (line_stream >> c) {
            if (c != '.') {
                char_positions[c].push_back(Position{ x, y });
            }

            x++;
        }

        y++;
    }

    return char_positions;
}

int solve(const std::string& input) {
    const size_t board_width = input.find_first_of('\n');
    const size_t board_height = std::count(input.begin(), input.end(), '\n') + 1;

    const std::unordered_map<char, std::vector<Position>> char_positions = process_map(input);
    std::unordered_set<Position> antinodes;

    for (const auto& [_, positions] : char_positions) {
        for (size_t i = 0; i < positions.size(); i++) {
            for (size_t j = i + 1; j < positions.size(); j++) {

                const Position& first = positions[i];
                const Position& second = positions[j];

                const Position first_to_second = {
                    second.x - first.x,
                    second.y - first.y
                };
                
                // start at first and go backwards
                Position antinode = first;
                while (antinode.x >= 0 && antinode.x < board_width && antinode.y >= 0 && antinode.y < board_height) {
                    antinodes.insert(antinode);

                    antinode = {
                        antinode.x - first_to_second.x,
                        antinode.y - first_to_second.y
                    };
                }

                // start at second and go forwards
                antinode = second;
                while (antinode.x >= 0 && antinode.x < board_width && antinode.y >= 0 && antinode.y < board_height) {
                    antinodes.insert(antinode);

                    antinode = {
                        antinode.x + first_to_second.x,
                        antinode.y + first_to_second.y
                    };
                }
            }
        }
    }

    return antinodes.size();
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}