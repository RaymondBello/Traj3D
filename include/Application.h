#pragma once

#include "ApplicationSettings.h"
#include "ParameterUI.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <entt/entt.hpp>

// Components
#include <Components.h>

// Systems
#include <Systems.h>

std::string get_assets_dir()
{
#ifndef __EMSCRIPTEN__
    return "assets/";
#else
    return "/";
#endif
}

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

Application::Application()
{
    printf("created app\n");
}

Application::Application(AppSettings settings)
{

    // Create entities and registry
    m_registry = entt::registry();

    for (auto i = 0u; i < 4u; ++i)
    {
        const auto entity = m_registry.create();
        auto &camera = m_registry.emplace<CameraComponent>(entity);
        auto &model = m_registry.emplace<ModelComponent>(entity);
        model.is_configured = true; // Since model path is set

        if (i % 2 == 0)
        {
            camera.ROTATION_SPEED = 5.0f;
            model.m_filename = get_assets_dir() + "models/Starship.stl";
        } else
        {
            camera.ROTATION_SPEED = 10.0f;
            model.m_filename = get_assets_dir() + "models/SuperHeavy_Booster.stl";
        }
    }


    // Init Systems
    auto model_system = ModelSystem(&m_registry);
    model_system.process();
    model_system.process();

    // Init UI
    this->m_settings = settings;
    printf("created app: %s with settings\n", (char *)&this->m_settings.title);
    this->m_ui = ParameterUI(settings);
}

Application::~Application()
{
}

void Application::run()
{
    printf("Running App\n");
    this->m_ui.start_event_loop();
}
