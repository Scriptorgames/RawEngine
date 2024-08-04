#pragma once

#include <memory>
#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        [[nodiscard]] AssetManager& GetAssets() const;
        [[nodiscard]] SceneManager& GetScenes() const;
        [[nodiscard]] EventManager& GetEvents() const;
        [[nodiscard]] WindowManager& GetWindow() const;
        [[nodiscard]] InputManager& GetInput() const;

        void Start() const;
        void Stop() const;

    private:
        std::unique_ptr<AssetManager> m_Assets;
        std::unique_ptr<SceneManager> m_Scenes;
        std::unique_ptr<EventManager> m_Events;
        std::unique_ptr<WindowManager> m_Window;
        std::unique_ptr<InputManager> m_Input;
    };
}
