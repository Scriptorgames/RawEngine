#pragma once

#include <map>
#include <string>
#include <vector>
#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    struct KeyState
    {
        void Update(bool now);

        bool Pre, Now;
    };

    enum AxisType
    {
        AxisType_Key,
        AxisType_Button,
        AxisType_Axis
    };

    AxisType MapAxisType(const std::string& str);
    int MapIndex(AxisType type, const std::string& str);

    struct AxisMode
    {
        AxisType Type;
        int Index;
        bool Invert;
    };

    class InputManager
    {
    public:
        explicit InputManager(Engine& engine);

        void Update();

        bool GetKey(int key);
        bool GetKeyDown(int key);
        bool GetKeyUp(int key);

        InputManager& Reset();
        InputManager& DefineAxis(const std::string& name, const std::vector<AxisMode>& modes);
        float GetAxisRaw(const std::string& name, int jid = -1);
        float GetAxis(const std::string& name, int jid = -1);

    private:
        Engine& m_Engine;

        std::map<int, KeyState> m_KeyMap;
        std::map<std::string, std::vector<AxisMode>> m_AxisMap;
    };
}
