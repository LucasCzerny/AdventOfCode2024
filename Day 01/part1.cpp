#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

#include "Lib.h"

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

    std::sort(leftNumbers.begin(), leftNumbers.end());
    std::sort(rightNumbers.begin(), rightNumbers.end());

    int sum = std::inner_product(
        leftNumbers.begin(), leftNumbers.end(),
        rightNumbers.begin(),
        0, std::plus<int>(),
        [](int a, int b)
        {
            return std::abs(a - b);
        }
    );

    return sum;
}

int main()
{
    std::string input = Lib::LoadFile("input.txt");
    std::cout << "Solution for Part 1: " << Solve(input) << '\n';

    Lib::Timer timer(std::bind(Solve, input));
    std::cout << "Average time for 10.000 runs: " << timer.AverageTime(10000) << '\n';
}