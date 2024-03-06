#pragma once
#include <entt/entt.hpp>

#include "Components.h"

class Scene
{
public:
    Scene();
    ~Scene();

    entt::entity CreateEntity();

    // TEMP
    entt::registry &Reg() { return m_Registry; }

    void OnUpdate(float dt);

private:
    entt::registry m_Registry;
};
