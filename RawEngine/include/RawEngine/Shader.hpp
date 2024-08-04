#pragma once

#include <filesystem>
#include <map>
#include <vector>
#include <GL/glew.h>
#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    class Shader
    {
    public:
        Shader(const std::string& id, const std::map<ShaderStage, std::vector<std::filesystem::path>>& sources);

        void Load();

    private:
        std::string m_Id;
        std::map<ShaderStage, std::vector<std::filesystem::path>> m_Sources;
        GLuint m_Program = 0;
    };
}
