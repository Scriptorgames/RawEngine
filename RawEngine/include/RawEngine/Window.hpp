#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <RawEngine/Module.hpp>

namespace RawEngine
{
    struct State
    {
        int PosX, PosY, Width, Height;
    };

    template <>
    class Module<ModuleType_Window> : public ModuleBase
    {
    public:
        static void Initialize();
        static void Terminate();

        Module(Engine& engine, int width, int height, const char* title);
        ~Module() override;

        [[nodiscard]] ModuleType GetType() const override;

        void SetFullscreen(bool mode);
        void Close() const;

        [[nodiscard]] bool Update() const;
        [[nodiscard]] GLFWwindow* GetGLFW() const;

        void GetFramebufferSize(int& width, int& height) const;

    private:
        GLFWwindow* m_GLFW;

        State m_State{};
        bool m_Mode = false;
    };

    using Window = Module<ModuleType_Window>;
}
