#include <iostream>

#include "lib.hpp"

int solve(const std::string& input) {
    return 0;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000).count() << '\n';
}