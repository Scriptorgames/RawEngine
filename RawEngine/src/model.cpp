#include <RawEngine/Scene/Component.hpp>

RawEngine::Model::Component(Entity& parent)
    : ComponentBase(parent)
{
}

RawEngine::ComponentType RawEngine::Model::Type() const { return ComponentType_Model; }
