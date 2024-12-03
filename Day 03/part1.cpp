#include <iostream>
#include <regex>

#include "lib.hpp"

int solve(const std::string& input) {
    static const std::regex mul_regex(R"(mul\((\d+),\s*(\d+)\))");

    const auto mul_start = std::sregex_iterator(input.begin(), input.end(), mul_regex);
    const auto mul_end = std::sregex_iterator();

    int sum = 0;
    for (auto it = mul_start; it != mul_end; it++) {
        const std::smatch match = *it;
        const std::string mul_string = match.str();

        const int first = std::stoi(match[1].str());
        const int second = std::stoi(match[2].str());

        sum += first * second;
    }

    return sum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000).count() << '\n';
}