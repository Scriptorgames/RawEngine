#pragma once

#include <map>
#include <RawEngine/Module.hpp>

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

    template <>
    class Module<ModuleType_Input> : public ModuleBase
    {
    public:
        explicit Module(Engine& engine);

        [[nodiscard]] ModuleType GetType() const override;

        void Update();

        bool GetKey(int key);
        bool GetKeyDown(int key);
        bool GetKeyUp(int key);

        void DefineAxis(const std::string& id, const std::vector<AxisConfig>& configs);
        float GetAxis(const std::string& id, int jid = -1);

    private:
        std::map<int, KeyState> m_KeyMap;
        std::map<std::string, std::vector<AxisConfig>> m_AxisMap;
    };

    using Input = Module<ModuleType_Input>;
}
