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
    class Timer
    {
    public:
        Timer(std::function<void()> function)
            : m_Function(function) {}

        std::chrono::duration<double, std::milli> AverageTime(int numberOfRuns);

    private:
        std::function<void()> m_Function;
    };
}