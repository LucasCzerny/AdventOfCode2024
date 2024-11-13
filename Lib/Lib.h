#pragma once

#include <filesystem>
namespace fs = std::filesystem;

namespace Lib
{
    std::string LoadFile(const fs::path& path);
}