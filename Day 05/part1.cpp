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

        size_t middle_index = update.size() / 2 + 1;

        // check backwards for the first half...
        int i;
        for (i = 0; i < middle_index; i++) {
            const int first = update.at(i);

            int j;
            for (j = 0; j < i; j++) {
                const int second = update.at(j);
                if (std::find(successors[second].begin(), successors[second].end(), first) == successors[second].end()) {
                    break;
                }
            }

            if (j != i) break;
        }

        if (i != middle_index) continue;

        // ... then check forwards for the second half
        for (i = update.size() - 1; i >= middle_index; i++) {
            const int first = update.at(i);

            int j;
            for (j = i + 1; j < update.size(); j++) {
                const int second = update.at(j);
                if (std::find(successors[first].begin(), successors[first].end(), second) == successors[first].end()) {
                    break;
                }
            }

            if (j != update.size()) break;
        }

        if (i == middle_index) {
            sum += update[middle_index];
        }
    }

    return sum;
}

int main() {
    std::string input = lib::load_file("sample_input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    // std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}