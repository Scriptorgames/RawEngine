#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace RawEngine
{
    struct Vertex
    {
        alignas(16) glm::vec3 Position;
        alignas(16) glm::vec3 Normal;
        alignas(8) glm::vec2 UV;
    };

    struct MeshLoader
    {
        void Load(const std::string& filename);

        std::vector<Vertex> Vertices;
        std::vector<uint32_t> Indices;
    };
}
