#pragma once

#include "ApplicationSettings.h"
#include "ParameterUI.h"

#include <entt/entt.hpp>
#include <CameraComponent.h>


class Application
{
private:
    /* data */
    AppSettings m_settings;
    ParameterUI m_ui;
    entt::registry m_registry;

public:
    Application();
    Application(AppSettings settings);
    ~Application();

    // Class methods
    void run();
};
