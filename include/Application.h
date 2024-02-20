#pragma once

#include "ApplicationSettings.h"
#include "UILayer/UILayer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <entt/entt.hpp>

// Components
// #include <Components.h>

// Systems
// #include <Systems.h>

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
    AppSettings m_settings;
    UILayer m_ui;

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

    // // Create entities and registry
    // m_registry = entt::registry();

    // for (auto i = 0u; i < 4u; ++i)
    // {
    //     const auto entity = m_registry.create();
    //     auto &camera = m_registry.emplace<CameraComponent>(entity);

    //     if (i % 2 == 0)
    //     {
    //         camera.ROTATION_SPEED = 5.0f;
    //         m_registry.emplace<ModelComponent>(entity, get_assets_dir() + "models/StarShip.stl");
    //     } else
    //     {
    //         camera.ROTATION_SPEED = 10.0f;
    //         m_registry.emplace<ModelComponent>(entity, get_assets_dir() + "models/SuperHeavy_Booster.stl");
    //     }
    // }

    // // Init Systems
    // auto model_system = ModelSystem(&m_registry);
    // model_system.process();

    // Init UI
    printf("created app: %s with settings\n", settings.title.c_str());
    this->m_settings = settings;
    this->m_ui = UILayer(settings);
}

Application::~Application()
{
}

void Application::run()
{
    printf("Running App\n");
    this->m_ui.start_event_loop();
}
