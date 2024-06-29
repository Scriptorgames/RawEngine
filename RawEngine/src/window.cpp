#include <cassert>
#include <iostream>
#include <RawEngine/Window.hpp>

void glfw_error_callback(const int errorCode, const char* pDescription)
{
    std::cerr << "[GLFW 0x" << std::hex << errorCode << std::dec << "] " << pDescription << std::endl;
}

void glfw_joystick_callback(const int jid, const int event)
{
    std::cout << "[GLFW] " << (event == GLFW_CONNECTED ? "Connected" : event == GLFW_DISCONNECTED ? "Disconnected" : "?") << " joystick " << jid << std::endl;
}

void glfw_monitor_callback(GLFWmonitor* pMonitor, const int event)
{
    std::cout << "[GLFW] " << (event == GLFW_CONNECTED ? "Connected" : event == GLFW_DISCONNECTED ? "Disconnected" : "?") << " monitor " << glfwGetMonitorName(pMonitor) << std::endl;
}

void RawEngine::Window::Initialize()
{
    assert(glfwInit() == GLFW_TRUE);
    glfwSetErrorCallback(glfw_error_callback);
    glfwSetJoystickCallback(glfw_joystick_callback);
    glfwSetMonitorCallback(glfw_monitor_callback);
}

void RawEngine::Window::Terminate()
{
    glfwTerminate();
}

RawEngine::Window::Module(Engine& engine, const int width, const int height, const char* title)
    : ModuleBase(engine)
{
    glfwDefaultWindowHints();
    m_GLFW = glfwCreateWindow(width, height, title, nullptr, nullptr);
    assert(m_GLFW);

    glfwSetWindowUserPointer(m_GLFW, this);
}

RawEngine::Window::~Module()
{
    glfwDestroyWindow(m_GLFW);
}

RawEngine::ModuleType RawEngine::Window::GetType() const { return ModuleType_Window; }

void RawEngine::Window::SetFullscreen(const bool mode)
{
    if (mode == m_Mode)
        return;

    if (m_Mode)
    {
        glfwSetWindowMonitor(m_GLFW, nullptr, m_State.PosX, m_State.PosY, m_State.Width, m_State.Height, GLFW_DONT_CARE);
        glfwSetWindowAttrib(m_GLFW, GLFW_DECORATED, GLFW_TRUE);
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
        glfwSetWindowAttrib(m_GLFW, GLFW_DECORATED, GLFW_FALSE);
        glfwSetWindowAttrib(m_GLFW, GLFW_RESIZABLE, GLFW_FALSE);
    }

    m_Mode = mode;
}

void RawEngine::Window::Close() const { glfwSetWindowShouldClose(m_GLFW, GLFW_TRUE); }

bool RawEngine::Window::Update() const
{
    glfwSwapBuffers(m_GLFW);

    glfwPollEvents();
    return !glfwWindowShouldClose(m_GLFW);
}

GLFWwindow* RawEngine::Window::GetGLFW() const { return m_GLFW; }
