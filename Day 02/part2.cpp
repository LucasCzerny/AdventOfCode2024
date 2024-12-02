#include <iostream>
#include <sstream>
#include <vector>

#include "lib.hpp"

bool is_report_safe(const std::string& line)
{
    std::istringstream line_stream(line);

    std::vector<int> numbers;
    numbers.reserve(8); // seems to be the maximum

    int number;
    while (line_stream >> number)
    {
        numbers.push_back(number);
    }

    for (int remove_index = -1; remove_index < static_cast<int>(numbers.size()); remove_index++)
    {
        int previous_index = 0 + (remove_index == 0);
        int previous = numbers[previous_index];

        int next_index = (previous_index + 1) == remove_index ? previous_index + 2 : previous_index + 1;
        bool decreasing = previous > numbers[next_index];

        int i;
        for (i = next_index; i < numbers.size(); i++) 
        {
            if (i == remove_index) continue;

            int current = numbers[i];

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

            if (decreasing != (difference > 0) || abs_difference < 1 || abs_difference > 3)
            {
                break;
            }

            previous = current;
        }

        // If we reached the end, then the report is safe
        if (i == numbers.size())
        {
            return true;
        }
    }

    return false;
}

int solve(const std::string& input)
{
    int safe_reports = 0;

    std::istringstream input_stream(input);

    std::string line;
    while (std::getline(input_stream, line))
    {
        safe_reports += is_report_safe(line);
    }

    return safe_reports;
}

int main()
{
    std::string input = lib::load_file("input.txt");
    std::cout << "Solution for Part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}
