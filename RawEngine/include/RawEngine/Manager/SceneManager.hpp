#pragma once

#include <RawEngine/RawEngine.hpp>
#include <RawEngine/Scene/Scene.hpp>

namespace RawEngine
{
    class SceneManager
    {
    public:
        explicit SceneManager(Engine& engine);

        Scene& LoadEntryScene();
        Scene& LoadScene(size_t index);

        Scene& GetLoadedScene();

        void Init();
        void Start();
        void Update();
        void Stop();
        void Destroy();

    private:
        Engine& m_Engine;

        std::map<std::string, Scene> m_Scenes;
        Scene m_LoadedScene;
    };
}
