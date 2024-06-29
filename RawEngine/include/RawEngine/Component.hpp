#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <RawEngine/MeshLoader.hpp>
#include <RawEngine/RawEngine.hpp>
#include <RawEngine/ShaderLoader.hpp>

namespace RawEngine
{
    struct ComponentBase
    {
        explicit ComponentBase(Entity& parent);
        virtual ~ComponentBase();

        [[nodiscard]] virtual ComponentType Type() const = 0;

        Entity& Parent;
    };

    template <>
    struct Component<ComponentType_Transform> : ComponentBase
    {
        explicit Component(Entity& parent);

        [[nodiscard]] ComponentType Type() const override;

        glm::vec3 Translation{};
        glm::quat Rotation{};
        glm::vec3 Scale{1.0f};
    };

    template <>
    struct Component<ComponentType_Model> : ComponentBase
    {
        explicit Component(Entity& parent);

        [[nodiscard]] ComponentType Type() const override;

        MeshLoader Mesh;
        ShaderLoader Shader;
    };

    template <>
    struct Component<ComponentType_Camera> : ComponentBase
    {
        explicit Component(Entity& parent);

        [[nodiscard]] ComponentType Type() const override;

        float FOV = 90.0f;
        float Near = 0.3f;
        float Far = 100.0f;
    };
}
