#include <cassert>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Input.hpp>
#include <RawEngine/Window.hpp>

void RawEngine::KeyState::Update(const bool now)
{
    Pre = Now;
    Now = now;
}

RawEngine::Input::Input(Engine& engine)
    : m_Engine(engine)
{
}

void RawEngine::Input::Update()
{
    const auto& window = m_Engine.GetWindow();

    for (int key = GLFW_KEY_SPACE; key < GLFW_KEY_LAST; ++key)
        m_KeyMap[key].Update(glfwGetKey(window.GetGLFW(), key));
}

bool RawEngine::Input::GetKey(const int key) { return m_KeyMap[key].Now; }

bool RawEngine::Input::GetKeyDown(const int key) { return !m_KeyMap[key].Pre && m_KeyMap[key].Now; }

bool RawEngine::Input::GetKeyUp(const int key) { return m_KeyMap[key].Pre && !m_KeyMap[key].Now; }

RawEngine::Input& RawEngine::Input::DefineAxis(const std::string& id, const std::vector<AxisConfig>& configs)
{
    m_AxisMap[id] = configs;
    return *this;
}

float RawEngine::Input::GetAxisRaw(const std::string& id, int jid)
{
    if (jid < 0)
    {
        for (int i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_16; ++i)
            if (glfwJoystickPresent(i) && glfwJoystickIsGamepad(i))
            {
                jid = i;
                break;
            }
    }

    GLFWgamepadstate state;
    if (GLFW_JOYSTICK_1 <= jid && jid <= GLFW_JOYSTICK_16)
        glfwGetGamepadState(jid, &state);

    float accum = 0.0f;
    for (const auto& [Type, Index, Negate] : m_AxisMap[id])
    {
        float value = 0.0f;
        switch (Type)
        {
        case AxisType_Key:
            value = GetKey(Index) ? 1.0f : 0.0f;
            break;
        case AxisType_Button:
            value = state.buttons[Index] ? 1.0f : 0.0f;
            break;
        case AxisType_Axis:
            value = state.axes[Index];
            break;
        }

        accum += Negate ? -value : value;
    }

    return accum;
}

float RawEngine::Input::GetAxis(const std::string& id, const int jid)
{
    const auto accum = GetAxisRaw(id, jid);
    return accum <= -1.0f ? -1.0f : accum >= 1.0f ? 1.0f : accum;
}
