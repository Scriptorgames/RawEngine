#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>
#include <RawEngine/RawEngine.hpp>

#define RE_TOPIC_SIZE "SIZE"
#define RE_TOPIC_KEY "KEY"

namespace RawEngine
{
    struct SizePayload
    {
        int Width, Height;
    };

    struct KeyPayload
    {
        int Key, Scancode, Action, Mods;
    };

    template <typename T>
    struct MutableEvent;

    template <typename T>
    struct ImmutableEvent;

    struct EventBase
    {
        virtual ~EventBase();

        template <typename T>
        [[nodiscard]] const MutableEvent<T>& Mutable() const { return *dynamic_cast<const MutableEvent<T>*>(this); }

        template <typename T>
        [[nodiscard]] const ImmutableEvent<T>& Immutable() const { return *dynamic_cast<const ImmutableEvent<T>*>(this); }
    };

    template <typename T>
    struct MutableEvent : EventBase
    {
        MutableEvent() = default;

        MutableEvent(T& payload)
            : Payload_(payload)
        {
        }

        T* operator->() const { return &Payload_; }

        T& Payload_;
    };

    template <typename T>
    struct ImmutableEvent : EventBase
    {
        ImmutableEvent() = default;

        ImmutableEvent(const T& payload)
            : Payload_(payload)
        {
        }

        const T* operator->() const { return &Payload_; }

        const T& Payload_;
    };

    template <>
    struct ImmutableEvent<void> : EventBase
    {
        ImmutableEvent() = default;
    };

    typedef std::function<bool(const EventBase*)> EventConsumer;

    class EventSystem
    {
    public:
        explicit EventSystem(Engine& engine);
        ~EventSystem();

        EventSystem& Register(const std::string& topic, const EventConsumer& consumer);
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
