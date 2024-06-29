#pragma once

#include <memory>
#include <optional>
#include <RawEngine/RawEngine.hpp>
#include <RawEngine/Scene.hpp>

namespace RawEngine
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        [[nodiscard]] Window& GetWindow() const;
        [[nodiscard]] Input& GetInput() const;
        [[nodiscard]] EventSystem& GetEvents() const;

        void Start() const;
        void Stop() const;

        Scene& LoadEntryScene();
        std::optional<Scene> LoadScene(int index);

    private:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Input> m_Input;
        std::unique_ptr<EventSystem> m_Events;

        Scene m_Scene;
    };
}
