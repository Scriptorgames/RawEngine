#pragma once

#include <memory>
#include <vector>
#include <algorithm>
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
        [[nodiscard]] bool HasComponent() const
        {
            return std::ranges::any_of(Components, [](const std::shared_ptr<ComponentBase>& component)
            {
                return component->Type() == T;
            });
        }

        template <ComponentType T>
        [[nodiscard]] Component<T>& GetComponent() const
        {
            for (auto& component : Components)
                if (component->Type() == T)
                    return *std::dynamic_pointer_cast<Component<T>>(component);
            throw std::runtime_error("GetComponent");
        }

        template <ComponentType T>
        [[nodiscard]] std::vector<std::shared_ptr<Component<T>>> GetComponents() const
        {
            std::vector<std::shared_ptr<Component<T>>> components;
            for (auto& component : Components)
                if (component->Type() == T)
                    components.push_back(std::dynamic_pointer_cast<Component<T>>(component));
            return components;
        }

        [[nodiscard]] Transform& GetTransform() const { return GetComponent<ComponentType_Transform>(); }

        std::vector<std::shared_ptr<ComponentBase>> Components;
    };
}
