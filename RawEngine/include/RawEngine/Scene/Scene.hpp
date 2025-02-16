#pragma once

#include <map>
#include <string>
#include <RawEngine/Scene/Entity.hpp>

namespace RawEngine
{
    struct Scene
    {
        Scene();
        ~Scene();

        Entity& operator[](const std::string&);

        std::map<std::string, Entity> Entities;
        std::string MainCamera;
    };
}
