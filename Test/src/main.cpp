#include <filesystem>
#include <iostream>
#include <RawEngine/Engine.hpp>
#include <RawEngine/Event.hpp>
#include <RawEngine/Manager/EventManager.hpp>
#include <RawEngine/Manager/SceneManager.hpp>
#include <RawEngine/Manager/WindowManager.hpp>
#include <RawEngine/Scene/Entity.hpp>

int main()
{
    RawEngine::Engine engine;

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

    engine.Start();
}
