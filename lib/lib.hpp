#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include <chrono>
#include <functional>

namespace lib {

    // File operations
    std::string load_file(const fs::path& path);

    // Timer
    std::chrono::duration<double, std::milli> average_time(std::function<void()> function, int number_of_runs);
}
