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

// ---GLM--------------------------------------------
#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>
#include <lib/glm/gtc/type_ptr.hpp>
// ---ASSIMP-----------------------------------------
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// ---OPENGL----------------------------------------
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLVertexArray.h"
#include "OpenGL/OpenGLBuffer.h"
// ---RENDERER----------------------------------------
#include "Renderer/OrthographicCamera.h"
// ---SCENE & ENTITIES--------------------------------
#include "Components.h"
#include "Geometry.h"

#include "Scene/Scene.h"
#include "Scene/Entity.h"

// ---------------------------------------------------
inline std::string get_assets_folder()
{
#ifndef __EMSCRIPTEN__
    return "assets/";
#else
    return "/";
#endif
}
// ---------------------------------------------------


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

    // Shader
    OpenGLShader *m_Shader = nullptr;
    OpenGLShader *m_ScreenShader = nullptr;

    std::shared_ptr<OpenGLVertexArray> m_CubeVAO;
    std::shared_ptr<OpenGLVertexArray> m_PlaneVAO;
    std::shared_ptr<OpenGLVertexArray> m_ScreenQuadVAO;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_indexCount;

    GLuint m_frameBuffer;
    GLuint m_textureColorBuffer;
    GLuint m_textureRenderBuffer;

    GLuint m_fbo = 0;
    GLuint m_fboColorAttachment = 0, m_fboDepthAttachment = 0;

    // UI Variables
    float m_rotationX = 45.0f;
    float m_rotationY = 30.0f;

    float m_mouseSpeed = 0.01f;

    glm::vec3 m_position = {-0.5f, -0.2f, -2.0f};
    glm::vec3 m_lookAt   = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_rotation = {-96.0f, -5.0f, -75.0f};
    glm::vec3 m_scale    = {1.0f, 1.0f, 1.0f};

    glm::mat4 m_modelMatrix = glm::mat4(1.0f);


    // Camera
    OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};

    float m_CameraMoveSpeed = 5.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    // Plotting
    uint64_t PLOT_BUFFER_SIZE = 1000;

    // Entities
    uint32_t m_SelectedEntityId;

    // Simulation


public:
    // UI Entity Inspector
    std::shared_ptr<uint32_t> m_Selected_entity;

    // Scene
    std::shared_ptr<Scene> m_Scene;
    // Scene* m_Scene;

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
    void create_scene();


    // Renderer related
    void setup_renderer();
    void destroy_renderer();
    void on_renderer_update();

    // Layout & Docking
    HelloImGui::DockingParams create_layout();
    std::vector<HelloImGui::DockingSplit> create_docking_splits();
    std::vector<HelloImGui::DockableWindow> create_docking_windows(AppSettings &settings);
};
