#include <RawEngine/Module.hpp>

RawEngine::ModuleBase::ModuleBase(Engine& engine)
    : m_Engine(engine)
{
}

RawEngine::ModuleBase::~ModuleBase() = default;

RawEngine::Engine& RawEngine::ModuleBase::GetEngine() const { return m_Engine; }
