#include <cassert>
#include <iostream>
#include <GL/glew.h>
#include <RawEngine/AssetManager.hpp>
#include <RawEngine/Engine.hpp>
#include <RawEngine/EventManager.hpp>
#include <RawEngine/InputManager.hpp>
#include <RawEngine/SceneManager.hpp>
#include <RawEngine/WindowManager.hpp>

void gl_debug_message_callback(GLenum /*source*/,
                               GLenum /*type*/,
                               GLuint /*id*/,
                               GLenum /*severity*/,
                               GLsizei /*length*/,
                               const GLchar* pMessage,
                               const void* /*pUserParam*/)
{
    std::cout << pMessage << std::endl;
}

RawEngine::Engine::Engine()
{
    WindowManager::Initialize();

    m_Assets = std::make_unique<AssetManager>(*this);
    m_Scenes = std::make_unique<SceneManager>(*this);
    m_Events = std::make_unique<EventManager>(*this);
    m_Window = std::make_unique<WindowManager>(*this, 800, 600, "RawEngine");
    m_Input = std::make_unique<InputManager>(*this);

    m_Assets->Index();
    m_Assets->ConfigureInput(m_Input);

    m_Scenes->LoadEntryScene();

    assert(!glewInit());

    glDebugMessageCallback(gl_debug_message_callback, this);
}

RawEngine::Engine::~Engine()
{
    m_Input = nullptr;
    m_Window = nullptr;
    m_Events = nullptr;
    m_Scenes = nullptr;
    m_Assets = nullptr;

    WindowManager::Terminate();
}

RawEngine::AssetManager& RawEngine::Engine::GetAssets() const { return *m_Assets; }

RawEngine::SceneManager& RawEngine::Engine::GetScenes() const { return *m_Scenes; }

RawEngine::EventManager& RawEngine::Engine::GetEvents() const { return *m_Events; }

RawEngine::WindowManager& RawEngine::Engine::GetWindow() const { return *m_Window; }

RawEngine::InputManager& RawEngine::Engine::GetInput() const { return *m_Input; }

void RawEngine::Engine::Start() const
{
    m_Scenes->Init();
    m_Scenes->Start();

    while (m_Window->Update())
    {
        m_Input->Update();
        m_Scenes->Update();

        const auto x = m_Input->GetAxis("Horizontal") * 0.5f + 0.5f;
        const auto y = m_Input->GetAxis("Vertical") * 0.5f + 0.5f;
        const auto z = m_Input->GetAxis("Jump") * 0.5f + 0.5f;
        glClearColor(x, y, z, 1.0f);

        int width, height;
        m_Window->GetFramebufferSize(width, height);
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render scene
    }

    m_Scenes->Stop();
    m_Scenes->Destroy();
}

void RawEngine::Engine::Stop() const
{
    m_Window->Close();
}
