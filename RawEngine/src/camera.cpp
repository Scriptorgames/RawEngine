#include <RawEngine/Scene/Component.hpp>

RawEngine::Camera::Component(Entity& parent)
    : ComponentBase(parent)
{
}

RawEngine::ComponentType RawEngine::Camera::Type() const { return ComponentType_Camera; }
