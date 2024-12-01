#include "Lib.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace Lib
{
    // File operations

    fs::path GetRootDirectory()
    {
        fs::path buildDirectory = fs::current_path();
        fs::path rootDirectory = buildDirectory.parent_path();

        return rootDirectory;
    }

    std::string LoadFile(const fs::path& path)
    {
        std::cout << GetRootDirectory() << '\n';
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

    // Timer

    std::chrono::duration<double, std::milli> AverageTime(std::function<void()> function, int numberOfRuns)
    {
        std::chrono::duration<double, std::milli> sumOfTimes;

        for (int i = 0; i < numberOfRuns; i++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            function();
            auto end = std::chrono::high_resolution_clock::now();

            sumOfTimes += end - start;
        }

        return sumOfTimes / numberOfRuns;
    }
}
