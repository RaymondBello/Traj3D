#pragma once

#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "imgui/misc/cpp/imgui_stdlib.h"
#include "imgui_internal.h"
#include "immapp/immapp.h"
#include "implot/implot.h"

#include "ApplicationSettings.h"
#include "ParameterUIState.h"

class ParameterUI
{
private:

    AppSettings m_settings;
    ParameterUIState m_ui_state;

    HelloImGui::RunnerParams runner_params;
    ImGuiTreeNodeFlags_ node_flags;

    ImPlotContext *m_plot_context = nullptr;

    ImFont *ui_font = nullptr;

public:
    int buffer_size = 1000;
    bool inspector_id_selected = true;
    std::string inspector_id_input = "";

    int node_selection_mask = 1<<0;

    ParameterUI(/* args */);
    ParameterUI(AppSettings settings);
    ~ParameterUI();

    void initialize();
    void load_font(AppSettings settings);
    void status_bar();
    void show_menu();
    void create_inspector(AppSettings &settings);
    HelloImGui::DockingParams create_layout();
    std::vector<HelloImGui::DockingSplit> create_docking_splits();
    std::vector<HelloImGui::DockableWindow> create_docking_windows(AppSettings &settings);
    void start_event_loop();
};


