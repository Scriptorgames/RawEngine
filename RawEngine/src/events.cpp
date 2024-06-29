#include <RawEngine/Events.hpp>

RawEngine::EventBase::~EventBase() = default;

RawEngine::EventSystem::EventSystem(Engine& engine)
    : m_Engine(engine)
{
}

RawEngine::EventSystem::~EventSystem() = default;

RawEngine::EventSystem& RawEngine::EventSystem::Register(const std::string& topic, const EventConsumer& consumer)
{
    m_Consumers[topic].push_back(consumer);
    return *this;
}

bool RawEngine::EventSystem::Broadcast(const std::string& topic, const EventBase* pEvent)
{
    bool consumed = false;
    for (const auto& consumer : m_Consumers[topic])
        consumed |= consumer(pEvent);
    return consumed;
}
