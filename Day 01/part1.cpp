#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Lib.h"

int main()
{
    std::string input = Lib::LoadFile("input.txt");

    // This will print the time once the timer goes out of scope
    Lib::ScopeTimer timer;

    std::vector<int> leftNumbers, rightNumbers;

    std::istringstream stream(input);
    std::string line;
    while (std::getline(stream, line))
    {
        int left, right;
        std::sscanf(line.c_str(), "%d  %d", &left, &right);

        leftNumbers.push_back(left);
        rightNumbers.push_back(right);
    }

    std::sort(leftNumbers.begin(), leftNumbers.end());
    std::sort(rightNumbers.begin(), rightNumbers.end());

    int sum = 0;
    for (int i = 0; i < leftNumbers.size(); i++)
    {
        sum += std::abs(leftNumbers[i] - rightNumbers[i]);
    }
    
    std::cout << "Solution for Part 1: " << sum << "\n";
}