#pragma once

#include <string>

namespace RawEngine
{
    struct ShaderLoader
    {
        void Load(const std::string& vertex_filename, const std::string& fragment_filename);
    };
}
