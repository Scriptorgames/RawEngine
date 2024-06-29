#include <RawEngine/Component.hpp>

RawEngine::ComponentBase::ComponentBase(Entity& parent)
    : Parent(parent)
{
}

RawEngine::ComponentBase::~ComponentBase() = default;