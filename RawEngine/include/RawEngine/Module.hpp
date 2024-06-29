#pragma once

#include <RawEngine/RawEngine.hpp>

namespace RawEngine
{
    enum ModuleType
    {
        ModuleType_Window,
        ModuleType_Input
    };

    class ModuleBase
    {
    public:
        explicit ModuleBase(Engine& engine);
        virtual ~ModuleBase();

        [[nodiscard]] Engine& GetEngine() const;
        [[nodiscard]] virtual ModuleType GetType() const = 0;

    private:
        Engine& m_Engine;
    };

    template <ModuleType T>
    class Module : public ModuleBase
    {
    public:
        explicit Module(Engine& engine)
            : ModuleBase(engine)
        {
        }

        [[nodiscard]] ModuleType GetType() const override { return T; }
    };
}
