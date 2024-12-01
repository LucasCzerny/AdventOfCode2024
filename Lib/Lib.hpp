#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include <chrono>
#include <functional>

namespace Lib
{
    // File operations
    std::string LoadFile(const fs::path& path);

    // Timer
    std::chrono::duration<double, std::milli> AverageTime(std::function<void()> function, int numberOfRuns);
}