#include "lib.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace lib {

    // File operations

    fs::path get_root_directory() {
        fs::path build_directory = fs::current_path();
        fs::path root_directory = build_directory.parent_path();

        return root_directory;
    }

    std::string load_file(const fs::path& path) {
        std::ifstream file(get_root_directory() / path, std::ios::ate);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        size_t file_size = file.tellg();
        std::string content(file_size, '\0');

        file.seekg(0);
        file.read(&content[0], file_size);
        file.close();

        return content;
    }

    std::vector<std::string> split_lines(const std::string& input) {
        std::vector<std::string> result;

        std::istringstream input_stream(input);

        std::string line;
        while (std::getline(input_stream, line)) {
            result.push_back(line);
        }

        return result;
    }

    // Timer

    std::chrono::duration<double, std::milli> average_time(std::function<void()> function, int number_of_runs) {
        std::chrono::duration<double, std::milli> sum_of_times;

        for (int i = 0; i < number_of_runs; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            function();
            auto end = std::chrono::high_resolution_clock::now();

            sum_of_times += end - start;
        }

        return sum_of_times / number_of_runs;
    }
}
