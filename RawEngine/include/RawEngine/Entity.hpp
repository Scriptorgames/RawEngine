#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <RawEngine/Component.hpp>
#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    struct Entity
    {
        Entity();
        ~Entity();

        template <ComponentType T>
        Component<T>& AddComponent(auto... args)
        {
            const auto component = std::make_shared<Component<T>>(*this, args...);
            Components.push_back(component);
            return *component;
        }

        template <ComponentType T>
        std::optional<Component<T>&> GetComponent()
        {
            for (auto& component : Components)
                if (component->Type() == T)
                    return *std::dynamic_pointer_cast<Component<T>>(component);
            return {};
        }

        template <ComponentType T>
        std::vector<Component<T>&> GetComponents()
        {
            std::vector<Component<T>&> components;
            for (auto& component : Components)
                if (component->Type() == T)
                    components.push_back(*std::dynamic_pointer_cast<Component<T>>(component));
            return components;
        }

        std::vector<std::shared_ptr<ComponentBase>> Components;
    };
}
