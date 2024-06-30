#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <RawEngine/MeshLoader.hpp>

RawEngine::MeshLoader::MeshLoader()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
}

RawEngine::MeshLoader::~MeshLoader()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void RawEngine::MeshLoader::Load(const std::string& filename)
{
    Vertices.clear();
    Indices.clear();

    Assimp::Importer importer;

    const auto pScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices | aiProcess_GenUVCoords);
    if (!pScene)
    {
        std::cerr << importer.GetErrorString() << std::endl;
        return;
    }

    for (unsigned mi = 0; mi < pScene->mNumMeshes; ++mi)
    {
        const auto pMesh = pScene->mMeshes[mi];
        for (unsigned vi = 0; vi < pMesh->mNumVertices; ++vi)
        {
            const auto& position = pMesh->mVertices[vi];
            const auto& normal = pMesh->mNormals[vi];
            const auto& uv = pMesh->mTextureCoords[0][vi];

            Vertices.push_back({
                .Position = {position.x, position.y, position.z},
                .Normal = {normal.x, normal.y, normal.z},
                .UV = {uv.x, uv.y},
            });
        }

        for (unsigned fi = 0; fi < pMesh->mNumFaces; ++fi)
        {
            const auto& face = pMesh->mFaces[fi];
            for (unsigned ii = 0; ii < face.mNumIndices; ++ii)
                Indices.push_back(face.mIndices[ii]);
        }
    }

    importer.FreeScene();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(12));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(24));

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(Vertex) * Vertices.size()), Vertices.data(),GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(GLuint) * Indices.size()), Indices.data(),GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
