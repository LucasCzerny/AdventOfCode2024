#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include <chrono>

namespace Lib
{
    // File
    std::string LoadFile(const fs::path& path);

    // Timer
    struct ScopeTimer
    {
    public:
        ScopeTimer();
        ~ScopeTimer();

    private:
        std::chrono::_V2::system_clock::time_point m_StartTime;
    };
}