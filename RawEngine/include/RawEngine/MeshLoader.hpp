#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace RawEngine
{
    struct Vertex
    {
        alignas(16) glm::vec3 Position{};
        alignas(16) glm::vec3 Normal{};
        alignas(8) glm::vec2 UV{};
    };

    struct MeshLoader
    {
        MeshLoader();
        ~MeshLoader();

        void Load(const std::string& filename);

        std::vector<Vertex> Vertices;
        std::vector<GLuint> Indices;

        GLuint VAO{};
        GLuint VBO{};
        GLuint IBO{};
    };
}
