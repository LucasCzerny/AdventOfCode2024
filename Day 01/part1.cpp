#include <iostream>
#include <string>
#include <sstream>

#include "Lib.h"

int main()
{
    std::string input = Lib::LoadFile("input.txt");
    std::istringstream inputStream(input);

    constexpr std::string_view digits = "0123456789";

    uint32_t sum = 0;

    for (std::string line; std::getline(inputStream, line);)
    {
        size_t first_position = line.find_first_of(digits);
        size_t last_position = line.find_last_of(digits);

        uint32_t number = (line[first_position] - '0') * 10 + line[last_position] - '0';
        sum += number;
    }

    std::cout << "Solution for Part 1: " << sum << "\n";
}