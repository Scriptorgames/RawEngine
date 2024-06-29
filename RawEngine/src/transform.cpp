#include <RawEngine/Component.hpp>

RawEngine::Transform::Component(Entity& parent)
    : ComponentBase(parent)
{
}

RawEngine::ComponentType RawEngine::Transform::Type() const { return ComponentType_Transform; }
