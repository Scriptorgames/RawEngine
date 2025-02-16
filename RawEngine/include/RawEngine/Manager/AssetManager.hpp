#pragma once

#include <filesystem>
#include <map>
#include <vector>
#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    class AssetManager
    {
    public:
        explicit AssetManager(Engine& engine);

        void Index();

        void ConfigureInput(const std::unique_ptr<InputManager>& pInput) const;

        const std::filesystem::path& GetScenePath(size_t index);
        ShaderPtr GetShader(const std::string& id);
        MeshPtr GetMesh(const std::string& id);

    private:
        void IndexConfig(const std::filesystem::path& assets_path);
        void IndexShader(const std::filesystem::path& path);
        void IndexMesh(const std::filesystem::path& path);

        Engine& m_Engine;

        std::filesystem::path m_InputPath;
        std::vector<std::filesystem::path> m_ScenePaths;
        std::map<std::string, ShaderPtr> m_Shaders;
        std::map<std::string, MeshPtr> m_Meshes;
    };
}
