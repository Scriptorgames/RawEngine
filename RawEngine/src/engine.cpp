#include <cassert>
#include <GL/glew.h>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Input.hpp>
#include <RawEngine/Window.hpp>

RawEngine::Engine::Engine()
{
    Window::Initialize();
    AddModule<ModuleType_Window>(800, 600, "RawEngine");
    AddModule<ModuleType_Input>();

    assert(!glewInit());
}

RawEngine::Engine::~Engine()
{
    for (auto& module : m_Modules)
        module.reset();
    Window::Terminate();
}

void RawEngine::Engine::Start()
{
    const auto window = GetModule<ModuleType_Window>();
    const auto input = GetModule<ModuleType_Input>();

    while (window->Update())
    {
        input->Update();

        if (input->GetKeyUp(GLFW_KEY_ESCAPE))
            window->Close();

        const auto x = input->GetAxis("Horizontal");
        const auto y = input->GetAxis("Vertical");
        const auto z = input->GetAxis("Jump");
        glClearColor(x, y, z, 1.0f);

        int width, height;
        window->GetFramebufferSize(width, height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
