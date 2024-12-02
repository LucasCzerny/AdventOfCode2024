#include <iostream>
#include <sstream>
#include <vector>

#include "Lib.hpp"

bool IsReportSafe(const std::string& line)
{
    std::istringstream lineStream(line);

    std::vector<int> numbers;
    numbers.reserve(8); // seems to be the maximum

    int number;
    while (lineStream >> number)
    {
        numbers.push_back(number);
    }

    for (int removeIndex = -1; removeIndex < static_cast<int>(numbers.size()); removeIndex++)
    {
        int previousIndex = 0 + (removeIndex == 0);
        int previous = numbers[previousIndex];

        int nextIndex = (previousIndex + 1) == removeIndex ? previousIndex + 2 : previousIndex + 1;
        bool decreasing = previous > numbers[nextIndex];

        int i;
        for (i = nextIndex; i < numbers.size(); i++) 
        {
            if (i == removeIndex) continue;

            int current = numbers[i];

            int difference = previous - current;
            int absDifference = std::abs(difference);

            // if it's decreasing, then the difference should be > 0
            // if !decreasing, then the difference is < 0

            // decreasing ... column
            // difference > 0 ... row
            // the result is true if there's an error

            //       | true  false
            // ------|------------
            // true  | false true
            // false | true  false

            if (decreasing != (difference > 0) || absDifference < 1 || absDifference > 3)
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

int Solve(const std::string& input)
{
    int safeReports = 0;

    std::istringstream inputStream(input);

    std::string line;
    while (std::getline(inputStream, line))
    {
        safeReports += IsReportSafe(line);
    }

    return safeReports;
}

int main()
{
    std::string input = Lib::LoadFile("input.txt");
    std::cout << "Solution for Part 2: " << Solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << Lib::AverageTime(std::bind(Solve, input), 10000) << '\n';
}