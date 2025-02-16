#include <assimp/Importer.hpp>
#include <RawEngine/Mesh.hpp>

#include "assimp/postprocess.h"

RawEngine::Mesh::Mesh(const std::filesystem::path& source)
    : m_Source(source)
{
}

void RawEngine::Mesh::Load()
{
    Assimp::Importer importer;
    auto pScene = importer.ReadFile(m_Source.string(), aiProcess_Triangulate);
}
