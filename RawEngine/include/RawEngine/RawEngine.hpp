#pragma once

#include <memory>
#include <string>

namespace RawEngine
{
    class Engine;
    class AssetManager;
    class SceneManager;
    class EventManager;
    class WindowManager;
    class InputManager;

    class Mesh;
    class Shader;

    enum ShaderStage
    {
        ShaderStage_Vertex,
        ShaderStage_Fragment,
    };

    ShaderStage MapShaderStage(const std::string& str);

    typedef std::shared_ptr<Mesh> MeshPtr;
    typedef std::shared_ptr<Shader> ShaderPtr;

    struct Scene;
    struct Entity;
    struct ComponentBase;

    enum ComponentType
    {
        ComponentType_Transform,
        ComponentType_Model,
        ComponentType_Camera,
    };

    ComponentType MapComponentType(const std::string& str);

    template <ComponentType T>
    struct Component;

    using Transform = Component<ComponentType_Transform>;
    using Model = Component<ComponentType_Model>;
    using Camera = Component<ComponentType_Camera>;
}
