#include <cmath>
#include <iostream>
#include <numeric>
#include <map>

#include "lib.hpp"

unsigned int nr_of_digits(unsigned long long number) {
    if (number == 0) return 1;
    return std::log10(number) + 1;
}

unsigned long long solve(const std::string& input) {
    constexpr int number_of_blinks = 25;

    std::vector<unsigned long long> stones = lib::split_numbers_by_space<unsigned long long>(input);

    std::map<unsigned long long, unsigned long long> stone_map;
    for (auto stone : stones) {
        stone_map[stone]++;
    }

    for (int i = 0; i < number_of_blinks; i++) {
        std::map<unsigned long long, unsigned long long> new_stone_map;

        for (auto [stone, count] : stone_map) {
            if (stone == 0) {
                new_stone_map[1] += count;
            } else if (nr_of_digits(stone) % 2 == 0) {
                const unsigned int digits = nr_of_digits(stone);
                const unsigned int pow = std::pow(10, digits / 2);

                // split em
                const unsigned long long first_stone = stone / pow;
                const unsigned long long second_stone = stone % pow;

                new_stone_map[first_stone] += count;
                new_stone_map[second_stone] += count;
            } else {
                new_stone_map[stone * 2024] += count;
            }
        }

        stone_map = new_stone_map;
    }

    unsigned long long sum = std::accumulate(stone_map.begin(), stone_map.end(), 0ull, 
        [](unsigned long long acc, const std::pair<const unsigned long long, unsigned long long>& entry) {
            // entry.first is the stone, entry.second is the count
            return acc + entry.second;
        }
    );

    return sum;
}

int main() {
    std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}