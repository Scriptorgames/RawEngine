#include <RawEngine/Scene/Scene.hpp>

RawEngine::Scene::Scene() = default;

RawEngine::Scene::~Scene() = default;

RawEngine::Entity& RawEngine::Scene::operator[](const std::string& key) { return Entities[key]; }
