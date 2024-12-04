#include <iostream>
#include <regex>

#include "lib.hpp"

int solve(const std::string& input) {
    const std::vector<std::string> grid = lib::split_lines(input);

    const unsigned int rows = grid.size();
    const unsigned int columns = grid[0].size();

    int xmas_count = 0;

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {

            if (grid[row][column] != 'X') continue;

            static constexpr const char* word = "XMAS";

            for (int y_dir = -1; y_dir <= 1; y_dir++) {
                for (int x_dir = -1; x_dir <= 1; x_dir++) {

                    int i = 1;
                    for (i = 1; i < 4; i++) {
                        int c = column + i * x_dir;
                        int r = row + i * y_dir;

                        if (c < 0 || c >= columns) break;
                        if (r < 0 || r >= rows) break;

                        if (grid[r][c] != word[i]) {
                            break;
                        }
                    }

                    // we finished the loop without breaking -> we found the word, yay!!! :D
                    if (i == 4) {
                        xmas_count++;
                    }
                }
            }
        }
    } 

    return xmas_count;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}