#include <cassert>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Manager/InputManager.hpp>
#include <RawEngine/Manager/WindowManager.hpp>

void RawEngine::KeyState::Update(const bool now)
{
    Pre = Now;
    Now = now;
}

RawEngine::InputManager::InputManager(Engine& engine)
    : m_Engine(engine)
{
}

void RawEngine::InputManager::Update()
{
    const auto& window = m_Engine.GetWindow();

    for (int key = GLFW_KEY_SPACE; key < GLFW_KEY_LAST; ++key)
        m_KeyMap[key].Update(glfwGetKey(window.GetGLFW(), key));
}

bool RawEngine::InputManager::GetKey(const int key) { return m_KeyMap[key].Now; }

bool RawEngine::InputManager::GetKeyDown(const int key) { return !m_KeyMap[key].Pre && m_KeyMap[key].Now; }

bool RawEngine::InputManager::GetKeyUp(const int key) { return m_KeyMap[key].Pre && !m_KeyMap[key].Now; }

RawEngine::InputManager& RawEngine::InputManager::Reset()
{
    m_AxisMap.clear();
    m_KeyMap.clear();
    return *this;
}

RawEngine::InputManager& RawEngine::InputManager::DefineAxis(const std::string& name,
                                                             const std::vector<AxisMode>& modes)
{
    m_AxisMap[name] = modes;
    return *this;
}

float RawEngine::InputManager::GetAxisRaw(const std::string& name, int jid)
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
    for (const auto& [Type, Index, Invert] : m_AxisMap[name])
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

        accum += Invert ? -value : value;
    }

    return accum;
}

float RawEngine::InputManager::GetAxis(const std::string& name, const int jid)
{
    const auto accum = GetAxisRaw(name, jid);
    return accum <= -1.0f ? -1.0f : accum >= 1.0f ? 1.0f : accum;
}
