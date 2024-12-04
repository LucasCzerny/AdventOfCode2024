#include <iostream>
#include <regex>

#include "lib.hpp"

int solve(const std::vector<std::string>& input) {
    const unsigned int rows = input.size();
    const unsigned int columns = input[0].size();

    int xmas_count = 0;

    for (int row = 1; row < rows -1; row++) {
        for (int column = 1; column < columns - 1; column++) {

            if (input[row][column] != 'A') continue;

            const char top_left = input[row - 1][column - 1];
            const char bottom_right = input[row + 1][column + 1];

            if (top_left + bottom_right != 'M' + 'S') {
                continue;
            }

            const char top_right = input[row - 1][column + 1];
            const char bottom_left = input[row + 1][column - 1];

            if (top_right + bottom_left == 'M' + 'S') {
                xmas_count++;
            }
        }
    } 

    return xmas_count;
}

int main() {
    const std::vector<std::string> input = lib::load_lines("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}