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

        // fix em by bubble sorting
        // if invalid == false at the end, nothing was changed
        // yes this is cursed

        bool invalid = false;
        bool sorted = false;
        
        size_t remaining_length = update.size();
        while (!sorted && remaining_length > 0) {
            sorted = true;

            for (size_t i = 1; i < remaining_length; i++) {
                const int current = update.at(i);

                for (size_t j = 0; j < i; j++) {
                    const int before = update.at(j);

                    auto loc = std::find(successors[before].begin(), successors[before].end(), current);
                    if (loc != successors[before].end()) continue;

                    sorted = false;
                    invalid = true;

                    std::swap(update[i], update[j]);
                }
            }
        }

        if (invalid) {
            size_t middle_index = update.size() / 2;
            sum += update.at(middle_index);
        }
    }

    return sum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}