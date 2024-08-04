#include <map>
#include <RawEngine/InputManager.hpp>
#include <RawEngine/RawEngine.hpp>
#include <RawEngine/WindowManager.hpp>

static std::string upper(const std::string& str)
{
    std::string res;
    for (const auto& c : str)
        res += static_cast<char>(std::toupper(c));
    return res;
}

RawEngine::ShaderStage RawEngine::MapShaderStage(const std::string& str)
{
    static std::map<std::string, ShaderStage> map{
        {"VERTEX", ShaderStage_Vertex},
        {"FRAGMENT", ShaderStage_Fragment},
    };
    return map[upper(str)];
}

RawEngine::ComponentType RawEngine::MapComponentType(const std::string& str)
{
    static std::map<std::string, ComponentType> map{
        {"TRANSFORM", ComponentType_Transform},
        {"MODEL", ComponentType_Model},
        {"CAMERA", ComponentType_Camera},
    };
    return map[upper(str)];
}

RawEngine::AxisType RawEngine::MapAxisType(const std::string& str)
{
    static std::map<std::string, AxisType> map{
        {"KEY", AxisType_Key},
        {"BUTTON", AxisType_Button},
        {"AXIS", AxisType_Axis},
    };
    return map[upper(str)];
}

int RawEngine::MapIndex(const AxisType type, const std::string& str)
{
    static std::map<std::string, int> key_map{
        {"SPACE", GLFW_KEY_SPACE},
        {"LEFT-SHIFT", GLFW_KEY_LEFT_SHIFT},
        {"RIGHT-SHIFT", GLFW_KEY_RIGHT_SHIFT},
    };
    static std::map<std::string, int> button_map{
        {"A", GLFW_GAMEPAD_BUTTON_A},
        {"B", GLFW_GAMEPAD_BUTTON_B},
        {"X", GLFW_GAMEPAD_BUTTON_X},
        {"Y", GLFW_GAMEPAD_BUTTON_Y},
        {"BACK", GLFW_GAMEPAD_BUTTON_BACK},
        {"CROSS", GLFW_GAMEPAD_BUTTON_CROSS},
        {"GUIDE", GLFW_GAMEPAD_BUTTON_GUIDE},
        {"START", GLFW_GAMEPAD_BUTTON_START},
        {"CIRCLE", GLFW_GAMEPAD_BUTTON_CIRCLE},
        {"DPAD-UP", GLFW_GAMEPAD_BUTTON_DPAD_UP},
        {"SQUARE", GLFW_GAMEPAD_BUTTON_SQUARE},
        {"DPAD-DOWN", GLFW_GAMEPAD_BUTTON_DPAD_DOWN},
        {"DPAD-LEFT", GLFW_GAMEPAD_BUTTON_DPAD_LEFT},
        {"TRIANGLE", GLFW_GAMEPAD_BUTTON_TRIANGLE},
        {"DPAD-RIGHT", GLFW_GAMEPAD_BUTTON_DPAD_RIGHT},
        {"LEFT-THUMB", GLFW_GAMEPAD_BUTTON_LEFT_THUMB},
        {"LEFT-BUMPER", GLFW_GAMEPAD_BUTTON_LEFT_BUMPER},
        {"RIGHT-THUMB", GLFW_GAMEPAD_BUTTON_RIGHT_THUMB},
        {"RIGHT-BUMPER", GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER},
    };
    static std::map<std::string, int> axis_map{
        {"LEFT-X", GLFW_GAMEPAD_AXIS_LEFT_X},
        {"LEFT-Y", GLFW_GAMEPAD_AXIS_LEFT_Y},
        {"RIGHT-X", GLFW_GAMEPAD_AXIS_RIGHT_X},
        {"RIGHT-Y", GLFW_GAMEPAD_AXIS_RIGHT_Y},
        {"LEFT-TRIGGER", GLFW_GAMEPAD_AXIS_LEFT_TRIGGER},
        {"RIGHT-TRIGGER", GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER},
    };

    const auto id = upper(str);

    switch (type)
    {
    case AxisType_Key:
        {
            if (id.size() == 1)
                return id[0];
            return key_map[id];
        }
    case AxisType_Button: return button_map[id];
    case AxisType_Axis: return axis_map[id];
    }

    return -1;
}
