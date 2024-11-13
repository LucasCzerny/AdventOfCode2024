#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "Lib.h"

int main()
{
    std::string input = Lib::LoadFile("input.txt");
    std::istringstream inputStream(input);

    std::unordered_map<std::string, uint8_t> digits = {
        { "zero", 0 }, { "0", 0 },
        { "one", 1 }, { "1", 1 },
        { "two", 2 }, { "2", 2 },
        { "three", 3 }, { "3", 3 },
        { "four", 4 }, { "4", 4 },
        { "five", 5 }, { "5", 5 },
        { "six", 6 }, { "6", 6 },
        { "seven", 7 }, { "7", 7 },
        { "eight", 8 }, { "8", 8 },
        { "nine", 9 }, { "9", 9 }
    };

    uint32_t sum = 0;

    for (std::string line; std::getline(inputStream, line);)
    {
        int firstPosition = line.size(), lastPosition = -1;
        uint32_t firstDigit, lastDigit;

        for (const auto& [digit, digitValue] : digits)
        {
            int position = (int)line.find(digit, 0);
            while (position != std::string::npos)
            {
                if (position < firstPosition)
                {
                    firstPosition = position;
                    firstDigit = digitValue;
                }
                if (position > lastPosition)
                {
                    lastPosition = position;
                    lastDigit = digitValue;
                }

                position = line.find(digit, position + 1);
            }
        }

        sum += firstDigit * 10 + lastDigit;
    }

    std::cout << "Solution for Part 2: " << sum << "\n";
}