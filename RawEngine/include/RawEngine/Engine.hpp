#pragma once

#include <memory>
#include <vector>
#include <RawEngine/Module.hpp>

namespace RawEngine
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        template <ModuleType T>
        std::shared_ptr<Module<T>> AddModule(auto... args)
        {
            auto module = std::make_shared<Module<T>>(*this, args...);
            m_Modules.push_back(module);
            return module;
        }

        template <ModuleType T>
        std::shared_ptr<Module<T>> GetModule()
        {
            for (const auto& module : m_Modules)
                if (module->GetType() == T)
                    return std::dynamic_pointer_cast<Module<T>>(module);
            return {};
        }

        void Start();

    private:
        std::vector<std::shared_ptr<ModuleBase>> m_Modules;
    };
}
