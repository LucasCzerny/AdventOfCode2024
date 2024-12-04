#include <iostream>
#include <regex>

#include "lib.hpp"

struct regex_it {
    std::__cxx11::sregex_iterator current, end;

    regex_it() = default;

    regex_it(const std::string& input, const std::regex& regex) {
        current = std::sregex_iterator(input.begin(), input.end(), regex);
        end = std::sregex_iterator();
    }

    bool operator<(const regex_it& other) const {
        if (current == end) {
            return false;
        } else if (other.current == other.end) {
            return true;
        }

        return current->position() < other.current->position();
    }
};

int solve(const std::string& input) {
    static const std::regex mul_regex(R"(mul\((\d+),\s*(\d+)\))");
    static const std::regex do_regex(R"(do\(\))");
    static const std::regex dont_regex(R"(don't\(\))");

    regex_it mul_iterator = regex_it(input, mul_regex);
    regex_it do_iterator = regex_it(input, do_regex);
    regex_it dont_iterator = regex_it(input, dont_regex);

    int sum = 0;
    bool enabled = true;

    while (mul_iterator.current != mul_iterator.end) {
        regex_it* next_it = mul_iterator < do_iterator ? &mul_iterator : &do_iterator;
        next_it = dont_iterator < *next_it ? &dont_iterator : next_it;

        const std::smatch match = *next_it->current;
        const std::string match_str = match.str();

        if (match_str.find("mul") == 0 && enabled) {
            const int first = std::stoi(match[1].str());
            const int second = std::stoi(match[2].str());
            sum += first * second;
        } else if (match_str == "do()") {
            enabled = true;
        } else if (match_str == "don't()") {
            enabled = false;
        }

        next_it->current++;
    }

    return sum;
}

int main() {
    const std::string input = lib::load_file("input.txt");
    std::cout << "Solution for part 2: " << solve(input) << '\n';

    std::cout << "Average time for 10.000 runs: " << lib::average_time(std::bind(solve, input), 10000) << '\n';
}