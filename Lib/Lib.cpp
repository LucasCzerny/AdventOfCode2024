#include "Lib.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace Lib
{
    // File

    fs::path GetRootDirectory()
    {
        fs::path buildDirectory = fs::current_path();
        fs::path rootDirectory = buildDirectory.parent_path();

        return rootDirectory;
    }

    std::string LoadFile(const fs::path& path)
    {
        std::ifstream file(GetRootDirectory() / path, std::ios::ate);

        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file");
        }

        size_t fileSize = file.tellg();
        std::string content(fileSize, '\0');

        file.seekg(0);
        file.read(&content[0], fileSize);
        file.close();

        return content;
    }

    // Time

    ScopeTimer::ScopeTimer()
    {
        m_StartTime = std::chrono::high_resolution_clock::now();
    }

    ScopeTimer::~ScopeTimer()
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = endTime - m_StartTime;

        std::cout << "Timer: " << duration.count() << "ms\n";
    }
}