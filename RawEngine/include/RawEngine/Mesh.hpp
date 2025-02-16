#pragma once

#include <filesystem>
#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    class Mesh
    {
    public:
        explicit Mesh(const std::filesystem::path& source);

        void Load();

    private:
        std::filesystem::path m_Source;
    };
}
