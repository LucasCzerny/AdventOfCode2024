#include <iostream>
#include <set>

#include "lib.hpp"

unsigned long long solve(const std::string& input) {
    const size_t last_id = input.size() / 2; // rounded down
    size_t front_id = 0;

    unsigned long long checksum = 0;
    size_t memory_size = 0;
    bool is_free_space = false;

    std::set<size_t> seen_ids;

    for (const char& c : input) {
        if (seen_ids.size() == last_id + 1) break;

        const size_t amount = c - '0';

        if (!is_free_space) {
            for (size_t i = 0; i < amount; i++) {
                if (seen_ids.find(front_id) == seen_ids.end()) {
                    checksum += front_id * memory_size;
                }

                memory_size++;
            }

            seen_ids.insert(front_id);
            front_id++;
        } else {
            size_t remaining_amount = amount;
            size_t back_id = last_id;

            while (back_id != front_id) {
                size_t back_id, back_id_amount;
                for (back_id = last_id; back_id >= front_id; back_id--) {
                    if (seen_ids.find(back_id) != seen_ids.end()) {
                        continue;
                    }

                    back_id_amount = input[back_id * 2] - '0'; 

                    if (back_id_amount <= remaining_amount) {
                        break;
                    }
                }

                if (back_id == front_id - 1) {
                    break;
                }

                seen_ids.insert(back_id);

                for (size_t i = 0; i < back_id_amount; i++) {
                    checksum += back_id * memory_size;
                    memory_size++;
                }

                remaining_amount -= back_id_amount;
            }

            for (size_t i = 0; i < remaining_amount; i++) {
                memory_size++;
            }
        }

        is_free_space = !is_free_space;
    }

    return checksum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}