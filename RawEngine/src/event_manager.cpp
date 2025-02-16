#include <RawEngine/Manager/EventManager.hpp>

RawEngine::EventManager::EventManager(Engine& engine)
    : m_Engine(engine)
{
}

RawEngine::EventManager::~EventManager() = default;

RawEngine::EventManager& RawEngine::EventManager::Register(const std::string& topic, const EventConsumer& consumer)
{
    m_Consumers[topic].push_back(consumer);
    return *this;
}

bool RawEngine::EventManager::Broadcast(const std::string& topic, const EventBase* pEvent)
{
    bool consumed = false;
    for (const auto& consumer : m_Consumers[topic])
        consumed |= consumer(pEvent);
    return consumed;
}
