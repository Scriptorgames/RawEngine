#include <filesystem>
#include <iostream>
#include <RawEngine/Mesh.hpp>
#include <RawEngine/Shader.hpp>
#include <RawEngine/Manager/AssetManager.hpp>
#include <RawEngine/Manager/InputManager.hpp>
#include <yaml-cpp/yaml.h>

RawEngine::AssetManager::AssetManager(Engine& engine)
    : m_Engine(engine)
{
}

void RawEngine::AssetManager::Index()
{
    const auto assets_path = std::filesystem::current_path() / "assets";

    IndexConfig(assets_path);
}

void RawEngine::AssetManager::ConfigureInput(const std::unique_ptr<InputManager>& pInput) const
{
    pInput->Reset();

    for (auto root_node = YAML::LoadFile(m_InputPath.string()); const auto& axis_node : root_node["axes"])
    {
        const auto name = axis_node["name"].as<std::string>();
        std::cout << "Axis: " << name << std::endl;

        std::vector<AxisMode> modes;
        for (const auto& mode_node : axis_node["modes"])
        {
            const auto type_string = mode_node["type"].as<std::string>();
            const auto index_string = mode_node["index"].as<std::string>();
            const auto invert = mode_node["invert"].as<bool>();
            std::cout << "  Mode: " << type_string << " " << index_string << " " << invert << std::endl;

            const auto type = MapAxisType(type_string);
            const auto index = MapIndex(type, index_string);

            modes.emplace_back(type, index, invert);
        }
        pInput->DefineAxis(name, modes);
    }
}

const std::filesystem::path& RawEngine::AssetManager::GetScenePath(const size_t index) { return m_ScenePaths[index]; }

RawEngine::ShaderPtr RawEngine::AssetManager::GetShader(const std::string& id) { return m_Shaders[id]; }

RawEngine::MeshPtr RawEngine::AssetManager::GetMesh(const std::string& id) { return m_Meshes[id]; }

void RawEngine::AssetManager::IndexConfig(const std::filesystem::path& assets_path)
{
    auto root_node = YAML::LoadFile((assets_path / "config.yaml").string());

    const auto input_node = root_node["input"];
    auto shaders_node = root_node["shaders"];
    auto meshes_node = root_node["meshes"];
    auto scenes_node = root_node["scenes"];

    m_InputPath = assets_path / input_node.as<std::string>();

    m_ScenePaths.clear();
    for (const auto& scene : scenes_node)
        m_ScenePaths.push_back(assets_path / scene.as<std::string>());


    m_Shaders.clear();
    for (const auto& shader : shaders_node)
        IndexShader(assets_path / shader.as<std::string>());

    m_Meshes.clear();
    for (const auto& mesh : meshes_node)
        IndexMesh(assets_path / mesh.as<std::string>());
}

void RawEngine::AssetManager::IndexShader(const std::filesystem::path& path)
{
    auto root_node = YAML::LoadFile(path.string());
    const auto id = root_node["id"].as<std::string>();
    std::map<ShaderStage, std::vector<std::filesystem::path>> sources;
    for (const auto& source_node : root_node["sources"])
    {
        auto stage = source_node["stage"].as<std::string>();
        auto filename = source_node["filename"].as<std::string>();
        sources[MapShaderStage(stage)].push_back(path.parent_path() / filename);
    }
    m_Shaders[id] = std::make_shared<Shader>(id, sources);
}

void RawEngine::AssetManager::IndexMesh(const std::filesystem::path& path)
{
    auto root_node = YAML::LoadFile(path.string());
    const auto id = root_node["id"].as<std::string>();
    const auto source = root_node["source"].as<std::string>();
    m_Meshes[id] = std::make_shared<Mesh>(path.parent_path() / source);
}
