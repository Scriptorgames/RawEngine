#include <cassert>
#include <iostream>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Event.hpp>
#include <RawEngine/EventManager.hpp>
#include <RawEngine/WindowManager.hpp>

void glfw_error_callback(const int errorCode, const char* pDescription)
{
    std::cerr << "[GLFW 0x" << std::hex << errorCode << std::dec << "] " << pDescription << std::endl;
}

void glfw_joystick_callback(const int jid, const int event)
{
    std::cout
        << "[GLFW] "
        << (event == GLFW_CONNECTED ? "Connected" : event == GLFW_DISCONNECTED ? "Disconnected" : "?")
        << " joystick "
        << jid << std::endl;
}

void glfw_monitor_callback(GLFWmonitor* pMonitor, const int event)
{
    std::cout
        << "[GLFW] "
        << (event == GLFW_CONNECTED ? "Connected" : event == GLFW_DISCONNECTED ? "Disconnected" : "?")
        << " monitor "
        << glfwGetMonitorName(pMonitor) << std::endl;
}

void glfw_key_callback(GLFWwindow* pWindow, const int key, const int scancode, const int action, const int mods)
{
    const auto& window = *static_cast<RawEngine::WindowManager*>(glfwGetWindowUserPointer(pWindow));
    window.GetEngine().GetEvents().BroadcastImmutable(RE_TOPIC_KEY, RawEngine::KeyPayload{key, scancode, action, mods});
}

void glfw_window_size_callback(GLFWwindow* pWindow, const int width, const int height)
{
    const auto& window = *static_cast<RawEngine::WindowManager*>(glfwGetWindowUserPointer(pWindow));
    window.GetEngine().GetEvents().BroadcastImmutable(RE_TOPIC_SIZE, RawEngine::SizePayload{width, height});
}

void RawEngine::WindowManager::Initialize()
{
    assert(glfwInit() == GLFW_TRUE);
    glfwSetErrorCallback(glfw_error_callback);
    glfwSetJoystickCallback(glfw_joystick_callback);
    glfwSetMonitorCallback(glfw_monitor_callback);
}

void RawEngine::WindowManager::Terminate() { glfwTerminate(); }

RawEngine::WindowManager::WindowManager(Engine& engine, const int width, const int height, const char* title)
    : m_Engine(engine)
{
    glfwDefaultWindowHints();
    m_GLFW = glfwCreateWindow(width, height, title, nullptr, nullptr);
    assert(m_GLFW);

    glfwSetWindowUserPointer(m_GLFW, this);
    glfwMakeContextCurrent(m_GLFW);

    glfwSetKeyCallback(m_GLFW, glfw_key_callback);
    glfwSetWindowSizeCallback(m_GLFW, glfw_window_size_callback);
}

RawEngine::WindowManager::~WindowManager()
{
    glfwDestroyWindow(m_GLFW);
}

RawEngine::Engine& RawEngine::WindowManager::GetEngine() const { return m_Engine; }

void RawEngine::WindowManager::SetFullscreen(const bool active)
{
    if (active == m_FullscreenActive)
        return;

    if (m_FullscreenActive)
    {
        glfwSetWindowMonitor(m_GLFW,
                             nullptr,
                             m_State.PosX,
                             m_State.PosY,
                             m_State.Width,
                             m_State.Height,
                             GLFW_DONT_CARE);
        glfwSetWindowAttrib(m_GLFW, GLFW_RESIZABLE, GLFW_TRUE);
    }
    else
    {
        glfwGetWindowPos(m_GLFW, &m_State.PosX, &m_State.PosY);
        glfwGetWindowSize(m_GLFW, &m_State.Width, &m_State.Height);

        const auto pMonitor = glfwGetPrimaryMonitor();
        const auto pMode = glfwGetVideoMode(pMonitor);
        int xpos, ypos;
        glfwGetMonitorPos(pMonitor, &xpos, &ypos);
        glfwSetWindowMonitor(m_GLFW, nullptr, xpos, ypos, pMode->width, pMode->height, pMode->refreshRate);
        glfwSetWindowAttrib(m_GLFW, GLFW_RESIZABLE, GLFW_FALSE);
    }

    m_FullscreenActive = active;
}

void RawEngine::WindowManager::ToggleFullscreen() { SetFullscreen(!m_FullscreenActive); }

void RawEngine::WindowManager::Close() const { glfwSetWindowShouldClose(m_GLFW, GLFW_TRUE); }

bool RawEngine::WindowManager::Update() const
{
    glfwSwapBuffers(m_GLFW);
    glfwPollEvents();

    return !glfwWindowShouldClose(m_GLFW);
}

GLFWwindow* RawEngine::WindowManager::GetGLFW() const { return m_GLFW; }

void RawEngine::WindowManager::GetFramebufferSize(int& width, int& height) const
{
    glfwGetFramebufferSize(m_GLFW, &width, &height);
}
