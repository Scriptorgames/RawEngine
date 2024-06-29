#include <cassert>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Input.hpp>
#include <RawEngine/Window.hpp>

void RawEngine::KeyState::Update(const bool now)
{
    Pre = Now;
    Now = now;
}

RawEngine::Input::Module(Engine& engine)
    : ModuleBase(engine)
{
}

RawEngine::ModuleType RawEngine::Input::GetType() const { return ModuleType_Input; }

void RawEngine::Input::Update()
{
    const auto window = GetEngine().GetModule<ModuleType_Window>();

    for (int key = GLFW_KEY_SPACE; key < GLFW_KEY_LAST; ++key)
        m_KeyMap[key].Update(glfwGetKey(window->GetGLFW(), key));
}

bool RawEngine::Input::GetKey(const int key) { return m_KeyMap[key].Now; }

bool RawEngine::Input::GetKeyDown(const int key) { return !m_KeyMap[key].Pre && m_KeyMap[key].Now; }

bool RawEngine::Input::GetKeyUp(const int key) { return m_KeyMap[key].Pre && !m_KeyMap[key].Now; }

void RawEngine::Input::DefineAxis(const std::string& id, const std::vector<AxisConfig>& configs) { m_AxisMap[id] = configs; }

float RawEngine::Input::GetAxis(const std::string& id, int jid)
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
    glfwGetGamepadState(jid, &state);

    float accum = 0.0f;
    for (const auto& [Type, Index, Negate] : m_AxisMap[id])
    {
        float value;
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
        default:
            value = 0.0f;
            break;
        }
        accum += Negate ? -value : value;
    }
    return accum;
}
