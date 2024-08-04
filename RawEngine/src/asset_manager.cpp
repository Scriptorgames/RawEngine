#include <filesystem>
#include <iostream>
#include <RawEngine/AssetManager.hpp>
#include <RawEngine/InputManager.hpp>
#include <RawEngine/Mesh.hpp>
#include <RawEngine/Shader.hpp>
#include <yaml-cpp/yaml.h>

RawEngine::AssetManager::AssetManager(Engine& engine)
    : m_Engine(engine)
{
}

void RawEngine::AssetManager::Index()
{
    const auto assets = std::filesystem::current_path() / "assets";

    IndexConfig(assets);
}

void RawEngine::AssetManager::ConfigureInput(const std::unique_ptr<InputManager>& input) const
{
    input->Reset();

    for (auto yaml = YAML::LoadFile(m_Input.string()); const auto& axis : yaml["axes"])
    {
        const auto name = axis["name"].as<std::string>();
        std::cout << "Axis: " << name << std::endl;

        std::vector<AxisMode> modes;
        for (const auto& mode : axis["modes"])
        {
            const auto type_string = mode["type"].as<std::string>();
            const auto index_string = mode["index"].as<std::string>();
            const auto invert = mode["invert"].as<bool>();
            std::cout << "  Mode: " << type_string << " " << index_string << " " << invert << std::endl;

            const auto type = MapAxisType(type_string);
            const auto index = MapIndex(type, index_string);

            modes.emplace_back(type, index, invert);
        }
        input->DefineAxis(name, modes);
    }
}

const std::filesystem::path& RawEngine::AssetManager::GetScene(const size_t index) { return m_Scenes[index]; }

RawEngine::ShaderPtr RawEngine::AssetManager::GetShader(const std::string& id) { return m_Shaders[id]; }

RawEngine::MeshPtr RawEngine::AssetManager::GetMesh(const std::string& id) { return m_Meshes[id]; }

void RawEngine::AssetManager::IndexConfig(const std::filesystem::path& assets)
{
    auto yaml = YAML::LoadFile((assets / "config.yaml").string());

    const auto input = yaml["input"];
    auto shaders = yaml["shaders"];
    auto meshes = yaml["meshes"];
    auto scenes = yaml["scenes"];

    m_Input = assets / input.as<std::string>();

    m_Scenes.clear();
    for (const auto& scene : scenes)
        m_Scenes.push_back(assets / scene.as<std::string>());


    m_Shaders.clear();
    for (const auto& shader : shaders)
        IndexShader(assets / shader.as<std::string>());

    m_Meshes.clear();
    for (const auto& mesh : meshes)
        IndexMesh(assets / mesh.as<std::string>());
}

void RawEngine::AssetManager::IndexShader(const std::filesystem::path& path)
{
    auto yaml = YAML::LoadFile(path.string());
    const auto id = yaml["id"].as<std::string>();
    std::map<ShaderStage, std::vector<std::filesystem::path>> sources;
    for (const auto& source : yaml["sources"])
    {
        auto stage = source["stage"].as<std::string>();
        auto filename = source["filename"].as<std::string>();
        sources[MapShaderStage(stage)].push_back(path.parent_path() / filename);
    }
    m_Shaders[id] = std::make_shared<Shader>(id, sources);
}

void RawEngine::AssetManager::IndexMesh(const std::filesystem::path& path)
{
    auto yaml = YAML::LoadFile(path.string());
    const auto id = yaml["id"].as<std::string>();
    const auto source = yaml["source"].as<std::string>();
    m_Meshes[id] = std::make_shared<Mesh>(path.parent_path() / source);
}
