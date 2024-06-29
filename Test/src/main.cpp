#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Input.hpp>

int main()
{
    RawEngine::Engine engine;

    const auto& input = engine.GetModule<RawEngine::ModuleType_Input>();
    input->DefineAxis("Vertical", {
                          {.Type = RawEngine::AxisType_Axis, .Index = GLFW_GAMEPAD_AXIS_LEFT_Y, .Negate = true},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_W, .Negate = false},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_S, .Negate = true},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_UP, .Negate = false},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_DOWN, .Negate = true},
                      });
    input->DefineAxis("Horizontal", {
                          {.Type = RawEngine::AxisType_Axis, .Index = GLFW_GAMEPAD_AXIS_LEFT_X, .Negate = false},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_D, .Negate = false},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_A, .Negate = true},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_RIGHT, .Negate = false},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_LEFT, .Negate = true},
                      });
    input->DefineAxis("Jump", {
                          {.Type = RawEngine::AxisType_Button, .Index = GLFW_GAMEPAD_BUTTON_A, .Negate = false},
                          {.Type = RawEngine::AxisType_Button, .Index = GLFW_GAMEPAD_BUTTON_B, .Negate = true},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_SPACE, .Negate = false},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_LEFT_SHIFT, .Negate = true},
                          {.Type = RawEngine::AxisType_Key, .Index = GLFW_KEY_RIGHT_SHIFT, .Negate = true},
                      });

    engine.Start();
}
