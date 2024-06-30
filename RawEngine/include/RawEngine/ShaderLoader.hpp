#pragma once

#include <filesystem>
#include <GL/glew.h>

namespace RawEngine
{
    struct ShaderLoader
    {
        ~ShaderLoader();

        void Load(const std::filesystem::path& vertex_filename, const std::filesystem::path& fragment_filename);

        GLuint Program{};
    };
}
