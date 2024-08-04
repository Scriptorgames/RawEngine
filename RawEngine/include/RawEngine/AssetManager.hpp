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

        void ConfigureInput(const std::unique_ptr<InputManager>& input) const;

        const std::filesystem::path& GetScene(size_t index);
        ShaderPtr GetShader(const std::string& id);
        MeshPtr GetMesh(const std::string& id);

    private:
        void IndexConfig(const std::filesystem::path& assets);
        void IndexShader(const std::filesystem::path& path);
        void IndexMesh(const std::filesystem::path& path);

        Engine& m_Engine;

        std::filesystem::path m_Input;
        std::vector<std::filesystem::path> m_Scenes;
        std::map<std::string, ShaderPtr> m_Shaders;
        std::map<std::string, MeshPtr> m_Meshes;
    };
}
