#pragma once

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
        [[nodiscard]] const ImmutableEvent<T>& Immutable() const
        {
            return *dynamic_cast<const ImmutableEvent<T>*>(this);
        }
    };

    template <typename T>
    struct MutableEvent final : EventBase
    {
        MutableEvent() = default;

        // ReSharper disable once CppNonExplicitConvertingConstructor
        MutableEvent(T& p) // NOLINT(*-explicit-constructor)
            : P(p)
        {
        }

        T* operator->() const { return &P; }

        T& P;
    };

    template <typename T>
    struct ImmutableEvent final : EventBase
    {
        ImmutableEvent() = default;

        // ReSharper disable once CppNonExplicitConvertingConstructor
        ImmutableEvent(const T& p) // NOLINT(*-explicit-constructor)
            : P(p)
        {
        }

        const T* operator->() const { return &P; }

        const T& P;
    };

    template <>
    struct ImmutableEvent<void> final : EventBase
    {
        ImmutableEvent() = default;
    };
}
