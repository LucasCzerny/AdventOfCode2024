#include <iostream>
#include <sstream>

#include "lib.hpp"

int solve(const std::string& input) {
    int safe_reports = 0;

    std::istringstream input_stream(input);

    std::string line;
    while (std::getline(input_stream, line)) {
        std::istringstream line_stream(line);

        int previous, current;
        line_stream >> previous >> current;
        bool decreasing = previous > current;

        bool end_of_line = false;
        while (!end_of_line) {
            int difference = previous - current;
            int abs_difference = std::abs(difference);

            // if it's decreasing, then the difference should be > 0
            // if !decreasing, then the difference is < 0

            // decreasing ... column
            // difference > 0 ... row
            // the result is true if there's an error

            //       | true  false
            // ------|------------
            // true  | false true
            // false | true  false

            if (decreasing != (difference > 0) || abs_difference < 1 || abs_difference > 3) {
                break;
            }

            previous = current;
            end_of_line = !(line_stream >> current);
        }

        if (end_of_line) {
            safe_reports++;
        }
    }

    return safe_reports;
}

int main() {
    std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}