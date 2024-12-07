#include <iostream>

#include "lib.hpp"

bool is_equation_solvable(unsigned long long result, const std::vector<unsigned int>& numbers, unsigned int depth = 0) {
    if (depth == numbers.size() - 1) {
        return result == numbers[0];
    }

    int number_to_apply = numbers[numbers.size() - 1 - depth];

    bool solvable = is_equation_solvable(result - number_to_apply, numbers, depth + 1);

    double division = static_cast<double>(result) / number_to_apply;
    unsigned long long division_int = static_cast<unsigned long long>(division);

    // result is divisible by number_to_apply
    if (division == division_int) {
        solvable |= is_equation_solvable(division_int, numbers, depth + 1);
    }

    return solvable;
}

unsigned long long solve(const std::string& input) {
    std::istringstream input_stream(input);
    std::string line;

    // pulling out the big guns
    unsigned long long sum = 0;

    while (std::getline(input_stream, line)) {
        std::istringstream line_stream(line);

        unsigned long long result;
        line_stream >> result;

        line_stream.ignore(); // ignore the colon

        std::vector<unsigned int> numbers;
        unsigned int number;

        while (line_stream >> number) {
            numbers.push_back(number);
        }

        if (is_equation_solvable(result, numbers)) {
            sum += result;
        }
    }

    return sum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}