#pragma once

#include "ApplicationSettings.h"
#include "ParameterUI.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <entt/entt.hpp>

// Components
#include <CameraComponent.h>
#include <MeshComponent.h>

// Systems
#include <MeshSystem.h>

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
        auto &mesh = m_registry.emplace<MeshComponent>(entity);
        mesh.is_configured = true; // Since mesh path is set

        if (i % 2 == 0)
        {
            camera.ROTATION_SPEED = 5.0f;
            mesh.m_filename = get_assets_dir() + "models/Starship.stl";
        } else
        {
            camera.ROTATION_SPEED = 10.0f;
            mesh.m_filename = get_assets_dir() + "models/SuperHeavy_Booster.stl";
        }
    }


    // Init Systems
    auto mesh_system = MeshSystem(&m_registry);
    mesh_system.process();
    mesh_system.process();

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
