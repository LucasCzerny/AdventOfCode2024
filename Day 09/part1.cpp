#include <iostream>

#include "lib.hpp"

unsigned long long solve(const std::string& input) {
    const size_t last_id = input.size() / 2; // rounded down
    size_t front_id = 0, back_id = last_id + 1;
    size_t back_remaining = 0;

    unsigned long long checksum = 0;
    size_t memory_size = 0;
    bool is_free_space = false;

    for (const char& c : input) {
        const size_t amount = c - '0';

        if (!is_free_space) {
            for (size_t i = 0; i < amount; i++) {
                checksum += front_id * memory_size;
                memory_size++;
            }

            front_id++;
        } else {
            for (size_t i = 0; i < amount; i++) {
                if (back_remaining == 0) {
                    back_id--;
                    back_remaining = input[back_id * 2] - '0';
                }

                checksum += back_id * memory_size;
                memory_size++;
                back_remaining--;
            }
        }

        if (front_id == back_id) {
            break;
        }

        is_free_space = !is_free_space;
    }

    for (size_t i = 0; i < back_remaining; i++) {
        checksum += back_id * memory_size;
        memory_size++;
    }

    return checksum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 1: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}