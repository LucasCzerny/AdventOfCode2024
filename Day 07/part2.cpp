#include <iostream>

#include "lib.hpp"

unsigned long long concatenate(unsigned long long first, unsigned long long second) {
    unsigned int pow = 10;
    while(second >= pow) {
        pow *= 10;
    }

    return first * pow + second;   
}

bool is_equation_solvable(unsigned long long result, const std::vector<unsigned int>& numbers, unsigned long long current_result = 0, unsigned int depth = 0) {
    if (current_result > result) {
        return false;
    }

    if (depth == numbers.size()) {
        return result == current_result;
    }

    const unsigned int next_number = numbers[depth];
    return is_equation_solvable(result, numbers, current_result + next_number, depth + 1)
        || is_equation_solvable(result, numbers, (depth == 0 ? 1 : current_result) * next_number, depth + 1)
        || is_equation_solvable(result, numbers, concatenate(current_result, next_number), depth + 1);
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
    std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}