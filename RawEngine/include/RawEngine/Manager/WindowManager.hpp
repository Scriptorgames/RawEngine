#pragma once
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    struct State
    {
        int PosX, PosY, Width, Height;
    };

    class WindowManager
    {
    public:
        static void Initialize();
        static void Terminate();

        WindowManager(Engine& engine, int width, int height, const char* title);
        ~WindowManager();

        [[nodiscard]] Engine& GetEngine() const;

        void SetFullscreen(bool active);
        void ToggleFullscreen();
        void Close() const;

        [[nodiscard]] bool Update() const;
        [[nodiscard]] GLFWwindow* GetGLFW() const;

        void GetFramebufferSize(int& width, int& height) const;

    private:
        Engine& m_Engine;
        GLFWwindow* m_GLFW;

        State m_State{};
        bool m_FullscreenActive = false;
    };
}
