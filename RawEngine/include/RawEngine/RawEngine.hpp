#pragma once

namespace RawEngine
{
    class Engine;
    class Window;
    class Input;
    class EventSystem;

    struct Scene;
    struct Entity;
    struct ComponentBase;

    enum ComponentType
    {
        ComponentType_Transform,
        ComponentType_Model,
        ComponentType_Camera,
    };

    template <ComponentType T>
    struct Component;

    using Transform = Component<ComponentType_Transform>;
    using Model = Component<ComponentType_Model>;
    using Camera = Component<ComponentType_Camera>;
}
