#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <memory>

#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include <stdio.h>
#include "imgui/misc/cpp/imgui_stdlib.h"
#include "imgui_internal.h"
#include "immapp/immapp.h"
#include "implot/implot.h"

#include "stb_hello_imgui/stb_image.h"

#include <entt/entt.hpp>

#include "ApplicationSettings.h"

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>

// ---Renderer------------------------
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "OpenGL/OpenGLShader.h"

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include "Renderer/OrthographicCamera.h"
    // -----------------------------------

    inline std::string get_assets_folder()
{
#ifndef __EMSCRIPTEN__
    return "assets/";
#else
    return "/";
#endif
}

class UILayer
{
private:
    // Utilities
    AppSettings m_settings;
    HelloImGui::RunnerParams m_runner_params;

    // Node flags
    ImGuiTreeNodeFlags_ m_node_flags;

    // UI Pointers
    ImFont *m_ui_font = nullptr;
    ImPlotContext *m_plot_context = nullptr;

    // Renderer
    Shader *m_Shader = nullptr;
    VertexArray *m_VertexArray = nullptr;

    Shader *m_FlatColorShader = nullptr;
    VertexArray *m_SquareVA = nullptr;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};

    // std::shared_ptr<Shader> m_Shader;
    // std::shared_ptr<VertexArray> m_VertexArray;

    // Camera
    OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;

    float m_CameraMoveSpeed = 5.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    // Plotting
    uint64_t PLOT_BUFFER_SIZE = 1000;

    // Simulation


public:
    // Entity Component Registry
    std::shared_ptr<entt::registry> m_registry;

    // UI Entity Inspector
    std::shared_ptr<uint32_t> m_selected_entity;

    UILayer(/* args */);
    UILayer(AppSettings& settings);
    ~UILayer();

    // Main Loop
    void start_event_loop();

    // Methods
    void initialize();
    void setup_fonts(AppSettings settings);
    void status_bar();
    void show_menu();

    // Window callbacks
    void create_inspector(AppSettings &settings);
    void create_plots();
    void create_hierarchy();

    // Renderer related
    void setup_renderer();
    void on_renderer_update();
    std::string load_shader(std::string file);

    // Layout & Docking
    HelloImGui::DockingParams create_layout();
    std::vector<HelloImGui::DockingSplit> create_docking_splits();
    std::vector<HelloImGui::DockableWindow> create_docking_windows(AppSettings &settings);
};
