#include <iostream>
#include <sstream>

#include "Lib.hpp"

int Solve(const std::string& input)
{
    int safeReports = 0;

    std::istringstream inputStream(input);

    std::string line;
    while (std::getline(inputStream, line))
    {
        std::istringstream lineStream(line);

        int previous, current;
        lineStream >> previous >> current;
        bool decreasing = previous > current;

        bool endOfLine = false;
        while (!endOfLine) 
        {
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
            endOfLine = !(lineStream >> current);
        }

        if (endOfLine)
        {
            safeReports++;
        }
    }

    return safeReports;
}

int main()
{
    std::string input = Lib::LoadFile("input.txt");
    std::cout << "Solution for Part 1: " << Solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << Lib::AverageTime(std::bind(Solve, input), 10000) << '\n';
}