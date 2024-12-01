#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Lib.hpp"

int Solve(const std::string& input)
{
    std::vector<int> leftNumbers, rightNumbers;
    leftNumbers.reserve(1000);
    rightNumbers.reserve(1000);

    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line))
    {
        std::istringstream lineStream(line);
        int left, right;
        lineStream >> left >> right;

        leftNumbers.push_back(left);
        rightNumbers.push_back(right);
    }

    std::unordered_map<int, int> rightCounts;
    for (int right : rightNumbers)
    {
        rightCounts[right]++;
    }

    int sum = 0;
    for (int left : leftNumbers)
    {
        sum += left * rightCounts[left];
    }

    return sum;
}

int main()
{
    std::string input = Lib::LoadFile("input.txt");
    std::cout << "Solution for Part 2: " << Solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << Lib::AverageTime(std::bind(Solve, input), 10000) << '\n';
}