#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "lib.hpp"

int solve(const std::string& input) {
    std::vector<int> left_numbers, right_numbers;
    left_numbers.reserve(1000);
    right_numbers.reserve(1000);

    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line)) {
        std::istringstream line_stream(line);
        int left, right;
        line_stream >> left >> right;

        left_numbers.push_back(left);
        right_numbers.push_back(right);
    }

    std::unordered_map<int, int> right_counts;
    for (int right : right_numbers) {
        right_counts[right]++;
    }

    int sum = 0;
    for (int left : left_numbers) {
        sum += left * right_counts[left];
    }

    return sum;
}

int main() {
    std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}