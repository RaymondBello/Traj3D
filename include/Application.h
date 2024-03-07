#pragma once

#include "ApplicationSettings.h"
#include "UILayer/UILayer.h"


#include <entt/entt.hpp>

// Components

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
    m_settings = settings;
}

Application::~Application()
{
}

void Application::run()
{
    printf("Running App\n");

    HelloImGui::SetAssetsFolder(m_settings.asset_path);
    printf("Added asset folder: %s\n", m_settings.asset_path.c_str());

    m_ui = UILayer(m_settings);

    HelloImGui::RunnerParams runner_params;

    runner_params.appWindowParams.windowTitle = m_settings.title;
    runner_params.imGuiWindowParams.menuAppTitle = "File";
    runner_params.appWindowParams.windowGeometry.size = {m_settings.v_width, m_settings.v_height};
    runner_params.appWindowParams.restorePreviousGeometry = m_settings.restore_previous_dimensions;
    // runner_params.callbacks.LoadAdditionalFonts = [&]()
    // {m_ui.setup_fonts(m_settings); };
    runner_params.callbacks.LoadAdditionalFonts = std::bind(&UILayer::setup_fonts, &m_ui, m_settings);

    // Status bar
    runner_params.imGuiWindowParams.showStatusBar = true;
    runner_params.fpsIdling.enableIdling = m_settings.fps_idling;
    // runner_params.callbacks.ShowStatus = [&]()
    // { m_ui.status_bar(); };
    runner_params.callbacks.ShowStatus = std::bind(&UILayer::status_bar, &m_ui);

    // Menu Bar
    runner_params.imGuiWindowParams.showMenuBar = true;
    runner_params.imGuiWindowParams.showMenu_App = true;
    runner_params.imGuiWindowParams.showMenu_View = true;
    // runner_params.callbacks.ShowMenus = [&]()
    // { m_ui.show_menu(); };
    runner_params.callbacks.ShowMenus = std::bind(&UILayer::show_menu, &m_ui);

    // Theme
    auto &tweakedTheme = runner_params.imGuiWindowParams.tweakedTheme;
    tweakedTheme.Theme = ImGuiTheme::ImGuiTheme_SoDark_AccentBlue;
    tweakedTheme.Tweaks.Rounding = 10.f;
    runner_params.callbacks.SetupImGuiStyle = []()
    { ImGui::GetStyle().ItemSpacing = ImVec2(6.f, 4.f); };

    // Create Layout
    runner_params.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
    runner_params.imGuiWindowParams.enableViewports = true;
    runner_params.dockingParams = m_ui.create_layout();

    // Add save location
    runner_params.iniFolderType = HelloImGui::IniFolderType::AppUserConfigFolder;
    runner_params.iniFilename = m_settings.log_file.c_str();

    // Initialize Plots
    auto plot_context = ImPlot::CreateContext();

    // ###############################
    // PostInit & BeforeExit callbacks
    // #####################################################
    // runner_params.callbacks.PostInit = [&]()
    // { m_ui.setup_renderer(); };
    // runner_params.callbacks.BeforeExit = [&]()
    // { m_ui.destroy_renderer(); };

    runner_params.callbacks.PostInit = std::bind(&UILayer::setup_renderer, &m_ui);
    runner_params.callbacks.BeforeExit = std::bind(&UILayer::destroy_renderer, &m_ui);

    // #####################################################
    // Custom background
    // #####################################################
    // runner_params.callbacks.CustomBackground = [&]()
    // { m_ui.on_renderer_update(); };
    runner_params.callbacks.CustomBackground = std::bind(&UILayer::on_renderer_update, &m_ui);

    ImmApp::Run(runner_params);

}
