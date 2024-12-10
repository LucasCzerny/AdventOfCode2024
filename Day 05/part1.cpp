#include <iostream>
#include <map>

#include "lib.hpp"

std::vector<int> split_line(std::string& line) {
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream line_stream(line);

    std::vector<int> result;
    int number;

    while (line_stream >> number) {
        result.push_back(number);
    }

    return result;
}

int solve(const std::string& input) {
    std::istringstream input_stream(input);

    // Rules

    std::map<int, std::vector<int>> successors;

    std::string line;
    while (std::getline(input_stream, line)) {
        if (line.empty()) break;
        
        std::replace(line.begin(), line.end(), '|', ' ');
        std::istringstream line_stream(line);

        int first, second;
        line_stream >> first >> second;

        successors[first].push_back(second);
    }

    // Updates

    int sum = 0;

    while (std::getline(input_stream, line)) {
        std::vector<int> update = split_line(line);

        bool invalid = false;
        for (size_t i = 0; i < update.size(); i++) {
            const int current = update.at(i);

            for (size_t j = i + 1; j < update.size(); j++) {
                const int after = update.at(j);

                auto loc = std::find(successors[current].begin(), successors[current].end(), after);
                if (loc != successors[current].end()) continue;

                invalid = true;
                break;
            }

            if (invalid) break;
        }

        if (!invalid) {
            size_t middle_index = update.size() / 2;
            sum += update.at(middle_index);
        }
    }

    return sum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}