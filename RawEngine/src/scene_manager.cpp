#include <iostream>
#include <RawEngine/AssetManager.hpp>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Mesh.hpp>
#include <RawEngine/SceneManager.hpp>
#include <RawEngine/Shader.hpp>
#include <yaml-cpp/yaml.h>

RawEngine::SceneManager::SceneManager(Engine& engine)
    : m_Engine(engine)
{
}

RawEngine::Scene& RawEngine::SceneManager::LoadEntryScene()
{
    return LoadScene(0);
}

static std::string upper(const std::string& str)
{
    std::string res;
    for (const auto& c : str)
        res += static_cast<char>(std::toupper(c));
    return res;
}

RawEngine::Scene& RawEngine::SceneManager::LoadScene(const size_t index)
{
    const auto& path = m_Engine.GetAssets().GetScene(index);

    auto scene_yaml = YAML::LoadFile(path.string());
    const auto id = scene_yaml["id"].as<std::string>();

    if (m_Scenes.contains(id))
        return m_LoadedScene = m_Scenes[id];

    Scene scene;
    scene.MainCamera = scene_yaml["main-camera"].as<std::string>();
    for (const auto& entity_yaml : scene_yaml["entities"])
    {
        auto& entity = scene[entity_yaml["name"].as<std::string>()];
        for (const auto& component_yaml : entity_yaml["components"])
        {
            switch (MapComponentType(component_yaml["type"].as<std::string>()))
            {
            case ComponentType_Transform:
                {
                    auto& transform = entity.AddComponent<ComponentType_Transform>();

                    if (auto translation_yaml = component_yaml["translation"]; translation_yaml.IsDefined())
                        transform.Translation = {
                            translation_yaml[0].as<float>(),
                            translation_yaml[1].as<float>(),
                            translation_yaml[2].as<float>()
                        };

                    if (auto rotation_yaml = component_yaml["rotation"]; rotation_yaml.IsDefined())
                    {
                        if (auto type = upper(rotation_yaml["type"].as<std::string>()); type == "ANGLE-AXIS")
                        {
                            auto angle = rotation_yaml["angle"].as<float>();
                            auto axis = rotation_yaml["axis"];
                            transform.Rotation = rotate(
                                transform.Rotation,
                                angle,
                                {
                                    axis[0].as<float>(),
                                    axis[1].as<float>(),
                                    axis[2].as<float>()
                                });
                        }
                        else if (type == "LOOK-AT")
                        {
                            auto target = rotation_yaml["target"];
                            auto up = rotation_yaml["up"];
                            transform.Rotation = quatLookAt(
                                normalize(
                                    glm::vec3(
                                        target[0].as<float>(),
                                        target[1].as<float>(),
                                        target[2].as<float>())
                                    - transform.Translation),
                                {up[0].as<float>(), up[1].as<float>(), up[2].as<float>()});
                        }
                    }

                    if (auto scale_yaml = component_yaml["scale"]; scale_yaml.IsDefined())
                        transform.Scale = {
                            scale_yaml[0].as<float>(),
                            scale_yaml[1].as<float>(),
                            scale_yaml[2].as<float>()
                        };

                    break;
                }
            case ComponentType_Model:
                {
                    auto& model = entity.AddComponent<ComponentType_Model>();

                    auto shader_id = component_yaml["shader"].as<std::string>();
                    auto mesh_id = component_yaml["mesh"].as<std::string>();

                    model.Shader = m_Engine.GetAssets().GetShader(shader_id);
                    model.Mesh = m_Engine.GetAssets().GetMesh(mesh_id);

                    break;
                }
            case ComponentType_Camera:
                {
                    auto& camera = entity.AddComponent<ComponentType_Camera>();

                    if (auto fov_yaml = component_yaml["fov"]; fov_yaml.IsDefined())
                        camera.FOV = fov_yaml.as<float>();

                    if (auto near_yaml = component_yaml["near"]; near_yaml.IsDefined())
                        camera.Near = near_yaml.as<float>();

                    if (auto far_yaml = component_yaml["far"]; far_yaml.IsDefined())
                        camera.Far = far_yaml.as<float>();

                    break;
                }
            }
        }
    }

    return m_LoadedScene = m_Scenes[id] = scene;
}

RawEngine::Scene& RawEngine::SceneManager::GetLoadedScene() { return m_LoadedScene; }

void RawEngine::SceneManager::Init()
{
    for (const auto& [id, entity] : m_LoadedScene.Entities)
    {
        for (const auto& model : entity.GetComponents<ComponentType_Model>())
        {
            model->Shader->Load();
            model->Mesh->Load();
        }
    }
}

void RawEngine::SceneManager::Start()
{
    for (const auto& [id, entity] : m_LoadedScene.Entities);
}

void RawEngine::SceneManager::Update()
{
    for (const auto& [id, entity] : m_LoadedScene.Entities);
}

void RawEngine::SceneManager::Stop()
{
    for (const auto& [id, entity] : m_LoadedScene.Entities);
}

void RawEngine::SceneManager::Destroy()
{
    for (const auto& [id, entity] : m_LoadedScene.Entities);
}
