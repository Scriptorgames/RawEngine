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

    struct AxisConfig
    {
        AxisType Type;
        int Index;
        bool Negate;
    };

    class Input
    {
    public:
        explicit Input(Engine& engine);

        void Update();

        bool GetKey(int key);
        bool GetKeyDown(int key);
        bool GetKeyUp(int key);

        Input& DefineAxis(const std::string& id, const std::vector<AxisConfig>& configs);
        float GetAxisRaw(const std::string& id, int jid = -1);
        float GetAxis(const std::string& id, int jid = -1);

    private:
        Engine& m_Engine;

        std::map<int, KeyState> m_KeyMap;
        std::map<std::string, std::vector<AxisConfig>> m_AxisMap;
    };
}
