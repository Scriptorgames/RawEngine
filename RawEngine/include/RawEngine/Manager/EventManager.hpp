#pragma once

#include <functional>
#include <map>
#include <string>
#include <RawEngine/Event.hpp>
#include <RawEngine/RawEngine.hpp>

#define RE_TOPIC_SIZE "SIZE"
#define RE_TOPIC_KEY "KEY"

namespace RawEngine
{
    typedef std::function<bool(const EventBase*)> EventConsumer;

    class EventManager
    {
    public:
        explicit EventManager(Engine& engine);
        ~EventManager();

        EventManager& Register(const std::string& topic, const EventConsumer& consumer);
        bool Broadcast(const std::string& topic, const EventBase* pEvent);

        template <typename T>
        bool BroadcastMutable(const std::string& topic, T& payload)
        {
            MutableEvent<T> event = payload;
            return Broadcast(topic, &event);
        }

        template <typename T>
        bool BroadcastImmutable(const std::string& topic, const T& payload)
        {
            ImmutableEvent<T> event = payload;
            return Broadcast(topic, &event);
        }

    private:
        Engine& m_Engine;

        std::map<std::string, std::vector<EventConsumer>> m_Consumers;
    };
}
