#include <iostream>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Entity.hpp>
#include <RawEngine/Events.hpp>
#include <RawEngine/Input.hpp>
#include <RawEngine/Window.hpp>

int main()
{
    RawEngine::Engine engine;

    engine.GetInput()
          .DefineAxis("Vertical", {
                          {RawEngine::AxisType_Axis, GLFW_GAMEPAD_AXIS_LEFT_Y, true},
                          {RawEngine::AxisType_Key, GLFW_KEY_W, false},
                          {RawEngine::AxisType_Key, GLFW_KEY_S, true},
                          {RawEngine::AxisType_Key, GLFW_KEY_UP, false},
                          {RawEngine::AxisType_Key, GLFW_KEY_DOWN, true},
                      })
          .DefineAxis("Horizontal", {
                          {RawEngine::AxisType_Axis, GLFW_GAMEPAD_AXIS_LEFT_X, false},
                          {RawEngine::AxisType_Key, GLFW_KEY_D, false},
                          {RawEngine::AxisType_Key, GLFW_KEY_A, true},
                          {RawEngine::AxisType_Key, GLFW_KEY_RIGHT, false},
                          {RawEngine::AxisType_Key, GLFW_KEY_LEFT, true},
                      })
          .DefineAxis("Jump", {
                          {RawEngine::AxisType_Button, GLFW_GAMEPAD_BUTTON_A, false},
                          {RawEngine::AxisType_Button, GLFW_GAMEPAD_BUTTON_B, true},
                          {RawEngine::AxisType_Key, GLFW_KEY_SPACE, false},
                          {RawEngine::AxisType_Key, GLFW_KEY_LEFT_SHIFT, true},
                          {RawEngine::AxisType_Key, GLFW_KEY_RIGHT_SHIFT, true},
                      });

    engine.GetEvents()
          .Register(RE_TOPIC_SIZE, [](const RawEngine::EventBase* pEvent)
          {
              const auto& event = pEvent->Immutable<RawEngine::SizePayload>();
              std::cout << "Window size changed: " << event->Width << 'x' << event->Height << std::endl;
              return true;
          })
          .Register(RE_TOPIC_KEY, [&engine](const RawEngine::EventBase* pEvent)
          {
              const auto& event = pEvent->Immutable<RawEngine::KeyPayload>();
              if (event->Key == GLFW_KEY_ESCAPE && event->Action == GLFW_RELEASE)
              {
                  engine.GetWindow().Close();
                  return true;
              }
              if (event->Key == GLFW_KEY_F11 && event->Action == GLFW_RELEASE)
              {
                  engine.GetWindow().ToggleFullscreen();
                  return true;
              }
              return false;
          });

    auto& scene = engine.LoadEntryScene();
    auto& cube = scene["cube"];
    auto& cube_transform = cube.AddComponent<RawEngine::ComponentType_Transform>();
    auto& cube_model = cube.AddComponent<RawEngine::ComponentType_Model>();

    engine.Start();
}
