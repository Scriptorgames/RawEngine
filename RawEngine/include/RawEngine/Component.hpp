#pragma once

#include <RawEngine/RawEngine.hpp>

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
    };

    template <>
    struct Component<ComponentType_Model> : ComponentBase
    {
        explicit Component(Entity& parent);

        [[nodiscard]] ComponentType Type() const override;
    };

    template <>
    struct Component<ComponentType_Camera> : ComponentBase
    {
        explicit Component(Entity& parent);

        [[nodiscard]] ComponentType Type() const override;
    };
}
