#include <cassert>
#include <GL/glew.h>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Events.hpp>
#include <RawEngine/Input.hpp>
#include <RawEngine/Window.hpp>

RawEngine::Engine::Engine()
{
    Window::Initialize();
    m_Window = std::make_unique<Window>(*this, 800, 600, "RawEngine");
    m_Input = std::make_unique<Input>(*this);
    m_Events = std::make_unique<EventSystem>(*this);

    assert(!glewInit());
}

RawEngine::Engine::~Engine()
{
    m_Input = nullptr;
    m_Window = nullptr;
    Window::Terminate();
}

RawEngine::Window& RawEngine::Engine::GetWindow() const { return *m_Window; }

RawEngine::Input& RawEngine::Engine::GetInput() const { return *m_Input; }

RawEngine::EventSystem& RawEngine::Engine::GetEvents() const { return *m_Events; }

void RawEngine::Engine::Start() const
{
    while (m_Window->Update())
    {
        m_Input->Update();

        const auto x = m_Input->GetAxis("Horizontal") * 0.5f + 0.5f;
        const auto y = m_Input->GetAxis("Vertical") * 0.5f + 0.5f;
        const auto z = m_Input->GetAxis("Jump") * 0.5f + 0.5f;
        glClearColor(x, y, z, 1.0f);

        int width, height;
        m_Window->GetFramebufferSize(width, height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void RawEngine::Engine::Stop() const
{
    m_Window->Close();
}

RawEngine::Scene& RawEngine::Engine::LoadEntryScene()
{
    if (const auto has_scene = LoadScene(0))
    {
        return m_Scene = has_scene.value();
    }

    return m_Scene = {};
}

std::optional<RawEngine::Scene> RawEngine::Engine::LoadScene(int index)
{
    return {};
}
