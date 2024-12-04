#include <iostream>
#include <regex>

#include "lib.hpp"

int solve(const std::vector<std::string>& input) {
    const unsigned int rows = input.size();
    const unsigned int columns = input[0].size();

    

    return 0;
}

int main() {
    const std::vector<std::string> input = lib::load_lines("sample_input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000).count() << '\n';
}