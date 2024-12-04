#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "lib.hpp"

int solve(const std::string& input) {
    std::vector<int> left_numbers, right_numbers;
    left_numbers.reserve(1000);
    right_numbers.reserve(1000);

    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line))
    {
        std::istringstream line_stream(line);
        int left, right;
        line_stream >> left >> right;

        left_numbers.push_back(left);
        right_numbers.push_back(right);
    }

    std::sort(left_numbers.begin(), left_numbers.end());
    std::sort(right_numbers.begin(), right_numbers.end());

    const int sum = std::inner_product(
        left_numbers.begin(), left_numbers.end(),
        right_numbers.begin(),
        0, std::plus<int>(),
        [](int a, int b) {
            return std::abs(a - b);
        }
    );

    return sum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}