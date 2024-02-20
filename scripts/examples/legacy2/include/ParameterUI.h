#pragma once

#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include <stdio.h>
#include "imgui/misc/cpp/imgui_stdlib.h"
#include "imgui_internal.h"
#include "immapp/immapp.h"
#include "implot/implot.h"

#include "stb_hello_imgui/stb_image.h"

#include "ApplicationSettings.h"
#include "ParameterUIState.h"

#include "RenderEngine.h"


class ParameterUI
{
private:

    AppSettings m_settings;
    ParameterUIState m_ui_state;

    HelloImGui::RunnerParams runner_params;
    ImGuiTreeNodeFlags_ node_flags;

    ImPlotContext *m_plot_context = nullptr;

    ImFont *ui_font = nullptr;

    // Render Engine
    RenderEngine m_renderer;


public:
    int buffer_size = 1000;
    bool inspector_id_selected = true;
    std::string inspector_id_input = "";

    int node_selection_mask = 1<<0;

    ParameterUI(/* args */);
    ParameterUI(AppSettings settings);
    ~ParameterUI();

    // Methods
    void initialize();

    // Callbacks
    void load_font(AppSettings settings);
    void status_bar();
    void show_menu();

    // Window callbacks
    void create_inspector(AppSettings &settings);
    void create_plots();
    void create_scene();
    void create_hierarchy();

    // Layout & Docking
    HelloImGui::DockingParams create_layout();
    std::vector<HelloImGui::DockingSplit> create_docking_splits();
    std::vector<HelloImGui::DockableWindow> create_docking_windows(AppSettings &settings);

    // Main Loop
    void start_event_loop();
};


