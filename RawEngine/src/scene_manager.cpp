#include <iostream>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Mesh.hpp>
#include <RawEngine/Shader.hpp>
#include <RawEngine/Manager/AssetManager.hpp>
#include <RawEngine/Manager/SceneManager.hpp>
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
    const auto& path = m_Engine.GetAssets().GetScenePath(index);

    auto root_node = YAML::LoadFile(path.string());
    const auto id = root_node["id"].as<std::string>();

    if (m_Scenes.contains(id))
        return m_LoadedScene = m_Scenes[id];

    Scene scene;
    scene.MainCamera = root_node["main-camera"].as<std::string>();
    for (const auto& entity_node : root_node["entities"])
    {
        auto& entity = scene[entity_node["name"].as<std::string>()];
        for (const auto& component_node : entity_node["components"])
        {
            switch (MapComponentType(component_node["type"].as<std::string>()))
            {
            case ComponentType_Transform:
                {
                    auto& transform = entity.AddComponent<ComponentType_Transform>();

                    if (auto translation_node = component_node["translation"]; translation_node.IsDefined())
                        transform.Translation = {
                            translation_node[0].as<float>(),
                            translation_node[1].as<float>(),
                            translation_node[2].as<float>()
                        };

                    if (auto rotation_node = component_node["rotation"]; rotation_node.IsDefined())
                    {
                        if (auto type = upper(rotation_node["type"].as<std::string>()); type == "ANGLE-AXIS")
                        {
                            auto angle_node = rotation_node["angle"];
                            auto axis_node = rotation_node["axis"];
                            transform.Rotation = rotate(
                                transform.Rotation,
                                angle_node.as<float>(),
                                {
                                    axis_node[0].as<float>(),
                                    axis_node[1].as<float>(),
                                    axis_node[2].as<float>()
                                });
                        }
                        else if (type == "LOOK-AT")
                        {
                            auto target_node = rotation_node["target"];
                            auto up_node = rotation_node["up"];
                            transform.Rotation = quatLookAt(
                                normalize(
                                    glm::vec3(
                                        target_node[0].as<float>(),
                                        target_node[1].as<float>(),
                                        target_node[2].as<float>())
                                    - transform.Translation),
                                {up_node[0].as<float>(), up_node[1].as<float>(), up_node[2].as<float>()});
                        }
                    }

                    if (auto scale_node = component_node["scale"]; scale_node.IsDefined())
                        transform.Scale = {
                            scale_node[0].as<float>(),
                            scale_node[1].as<float>(),
                            scale_node[2].as<float>()
                        };

                    break;
                }
            case ComponentType_Model:
                {
                    auto& model = entity.AddComponent<ComponentType_Model>();

                    auto shader = component_node["shader"].as<std::string>();
                    auto mesh = component_node["mesh"].as<std::string>();

                    model.Shader = m_Engine.GetAssets().GetShader(shader);
                    model.Mesh = m_Engine.GetAssets().GetMesh(mesh);

                    break;
                }
            case ComponentType_Camera:
                {
                    auto& camera = entity.AddComponent<ComponentType_Camera>();

                    if (auto fov_node = component_node["fov"]; fov_node.IsDefined())
                        camera.FOV = fov_node.as<float>();

                    if (auto near_node = component_node["near"]; near_node.IsDefined())
                        camera.Near = near_node.as<float>();

                    if (auto far_node = component_node["far"]; far_node.IsDefined())
                        camera.Far = far_node.as<float>();

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
