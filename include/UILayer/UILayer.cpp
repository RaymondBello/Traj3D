#include "UILayer.h"

UILayer::UILayer(/* args */)
    : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
    // m_Scene.get() = Scene();
    // m_Scene = std::make_shared<Scene>();
}

UILayer::~UILayer()
{
}

UILayer::UILayer(AppSettings &settings)
    : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
    m_settings = settings;
    initialize();
}

void UILayer::destroy_renderer()
{
    glDeleteVertexArrays(0, &m_vao);
    glDeleteBuffers(0, &m_vbo);
    glDeleteBuffers(0, &m_ibo);
}

void UILayer::setup_renderer()
{
    // Macros
    #define VSHADER(name) load_shader(get_assets_folder() + "shaders/" #name ".vert")
    #define FSHADER(name) load_shader(get_assets_folder() + "shaders/" #name ".frag")

    GLfloat cubeVertices[] = {
        // front
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 0 (red)
        0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f,  // 1 (orange)
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,   // 2 (yellow)
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 3 (green)

        // top
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 4 (blue)
        0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // 5 (indigo)
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,   // 6 (violet)
        -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,  // 7 (gray)

        // left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // 8 (cyan)
        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.5f,  // 9 (pink)
        -0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 0.5f,   // 10 (light green)
        -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 1.0f,  // 11 (light blue)

        // right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, // 12 (dark pink)
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  // 13 (light yellow)
        0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // 14 (dark purple)
        0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.0f,  // 15 (orange yellow)

        // back
        -0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 1.0f, // 16 (light blue)
        0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  // 17 (yellow green)
        0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 0.0f,   // 18 (dark green)
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f,  // 19 (dark pink)

        // bottom
        -0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f, // 20
        0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f,  // 21
        0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f, // 22
        -0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f // 23
    };

    GLuint cubeVertexIndices[] = {
        // front
        0, 1, 2, // first triangle
        2, 3, 0, // second triangle

        // top
        4, 5, 6, // first triangle
        6, 7, 4, // second triangle

        // left
        8, 9, 10,  // first triangle
        10, 11, 8, // second triangle

        // right
        14, 13, 12, // 12, 13, 14, // first triangle
        12, 15, 14, // 14, 15, 12, // second triangle

        // back
        18, 17, 16, // 16, 17, 18, // first triangle
        16, 19, 18, // 18, 19, 16, // second triangle

        // bottom
        20, 21, 22, // first triangle
        22, 23, 20  // second triangle
    };

    // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    GLfloat quadVertices[] = {
        // positions   // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    // Print OpenGL version
    HelloImGui::Log(HelloImGui::LogLevel::Info, "Initializing OpenGL version: %s\n", glGetString(GL_VERSION));

    // Create a scene
    m_Scene = std::make_shared<Scene>();
    m_SelectedEntityId = -1;

    m_Shader = new OpenGLShader(VSHADER(default), FSHADER(default));
    // m_Shader = new OpenGLShader(VSHADER(fb_shader), FSHADER(fb_shader));
    // m_ScreenShader = new OpenGLShader(VSHADER(fb_screen_shader), FSHADER(fb_screen_shader));

    // Create a vertex array for a cube
    m_CubeVAO = std::make_shared<OpenGLVertexArray>();
    auto cubeVBO = std::make_shared<OpenGLVertexBuffer>(cubeVertices, sizeof(cubeVertices));
    BufferLayout cubeLayout = {
        {ShaderDataType::Float3, "a_Position"},
        // {ShaderDataType::Float2, "a_TexCoords"}
        {ShaderDataType::Float3, "a_Color"}
    };
    cubeVBO->SetLayout(cubeLayout);
    m_CubeVAO->AddVertexBuffer(cubeVBO);
    m_CubeVAO->SetIndexBuffer(std::make_shared<OpenGLIndexBuffer>(cubeVertexIndices, sizeof(cubeVertexIndices) / sizeof(GLuint)));

    m_Shader->Bind();
    m_Shader->UploadUniformMat4("u_ModelMatrix", glm::mat4(1.0f));
    m_Shader->Unbind();

    // m_Shader->Bind();
    // m_Shader->UploadUniformInt("u_Texture1", 0);
    // m_Shader->Unbind();

    // m_ScreenShader->Bind();
    // m_ScreenShader->UploadUniformInt("u_ScreenTexture", 0);
    // m_ScreenShader->Unbind();


    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    // Create a framebuffer
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    // create a color attachment texture
    glGenTextures(1, &m_textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_settings.v_width, m_settings.v_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &m_textureRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_textureRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_settings.v_width, m_settings.v_height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_textureRenderBuffer);         // now actually attach it

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        HelloImGui::Log(HelloImGui::LogLevel::Error, "Framebuffer is incomplete!");
    }
    // glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Unbind framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void UILayer::on_renderer_update()
{
    auto &io = ImGui::GetIO();
    auto r = ImVec2(io.DisplaySize.x * io.DisplayFramebufferScale.x,
                    io.DisplaySize.y * io.DisplayFramebufferScale.y);

    ImVec2 displaySize = r;

    // Clear the viewport
    glClearColor(0.133f, 0.545f, 0.133f, 1.0f); // Forest Green
    glViewport(0, 0, (GLsizei)displaySize.x, (GLsizei)displaySize.y);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glEnable(GL_DEPTH_TEST);

    // Clear the framebuffer
    glClearColor(0.30f, 0.55f, 0.65f, 1.0f);
    // glViewport(0, 0, (GLsizei)displaySize.x, (GLsizei)displaySize.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Bind();

    // Add the model matrix and translate it
    auto modelMatrix = glm::mat4(1.0f);
    // modelMatrix = glm::translate(modelMatrix, m_position);
    // // Add rotation to the model matrix
    // modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
    // modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    // modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
    // // Add scale to the model matrix
    // modelMatrix = glm::scale(modelMatrix, m_scale);

    // Set the model matrix in the shader
    m_Shader->UploadUniformMat4("u_ModelMatrix", glm::mat4(1.0f));

    // Add the view matrix
    auto viewMatrix = glm::mat4(1.0f);
    // Set the view matrix in the shader
    viewMatrix = glm::translate(viewMatrix, m_position);
    // Add rotation to the view matrix
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
    // Add scale to the view matrix
    viewMatrix = glm::scale(viewMatrix, m_scale);
    m_Shader->UploadUniformMat4("u_ViewMatrix", viewMatrix);

    // Create a projection matrix either orthographic or perspective
    auto projectionMatrix = glm::perspective(glm::radians(60.0f), displaySize.x / displaySize.y, 0.1f, 100.0f);
    // auto projectionMatrix = glm::ortho(-3.0f, 3.0f, -2.0f, 2.0f, -1.0f, 1.0f);

    // Set the projection matrix in the shader
    m_Shader->UploadUniformMat4("u_ProjectionMatrix", projectionMatrix);

    // Bind the VAO
    m_CubeVAO->Bind();

    glDrawElements(GL_TRIANGLES, m_CubeVAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 36);

    // Unbind the VAO and shader
    m_CubeVAO->Unbind();

    // Setup Depth Testing
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    // glDepthFunc(GL_GREATER);
    // glDisable(GL_DEPTH_TEST);

    // Setup Face Culling
    glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CCW);
    // glCullFace(GL_FRONT);
    glCullFace(GL_BACK);
    // glDisable(GL_CULL_FACE);

    // Unbind the shader
    m_Shader->Unbind();

    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);

    // // Clear the screen
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // m_ScreenShader->Bind();
    // // Bind the VAO
    // m_ScreenQuadVAO->Bind();
    // glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
    // glDrawArrays(GL_TRIANGLES, 0, 6);

    // // Unbind the VAO and shader
    // m_ScreenQuadVAO->Unbind();
    // m_ScreenShader->Unbind();

}

void UILayer::initialize()
{
    HelloImGui::Log(HelloImGui::LogLevel::Info, "Initializing UI Layer\n");
}

void UILayer::setup_fonts(AppSettings settings)
{
    HelloImGui::Log(HelloImGui::LogLevel::Debug, "Adding font: %s, %f\n", settings.font_path.c_str(), settings.font_size);

    HelloImGui::ImGuiDefaultSettings::LoadDefaultFont_WithFontAwesomeIcons();
    this->m_ui_font = HelloImGui::LoadFontTTF(settings.font_path.c_str(), settings.font_size);
}

HelloImGui::DockingParams UILayer::create_layout()
{
    HelloImGui::DockingParams docking_params;

    docking_params.dockingSplits = create_docking_splits();
    docking_params.dockableWindows = create_docking_windows(m_settings);

    return docking_params;
}

std::vector<HelloImGui::DockingSplit> UILayer::create_docking_splits()
{
    //     __________________________________
    //    |                      |          |
    //    |                      | Entity   |
    //    |    MainDockSpace     |          |
    //    |    | SceneView       |          |
    //    |                      |          |
    //    |                      |          |
    //    |----------------------|----------|
    //    |  Logs                           |
    //    ----------------------------------|
    HelloImGui::DockingSplit inspector_split;
    inspector_split.initialDock = "MainDockSpace";
    inspector_split.newDock = "Inspector";
    inspector_split.direction = ImGuiDir_Right;
    inspector_split.ratio = 0.25f;

    HelloImGui::DockingSplit logs_split;
    logs_split.initialDock = "MainDockSpace";
    logs_split.newDock = "Logs";
    logs_split.direction = ImGuiDir_Down;
    logs_split.ratio = 0.2f;

    HelloImGui::DockingSplit hierarchy;
    hierarchy.initialDock = "Inspector";
    hierarchy.newDock = "Hierarchy";
    hierarchy.direction = ImGuiDir_Up;
    hierarchy.ratio = 0.35f;

    std::vector<HelloImGui::DockingSplit> splits{
        inspector_split,
        logs_split,
        hierarchy};
    return splits;
}

std::vector<HelloImGui::DockableWindow> UILayer::create_docking_windows(AppSettings &settings)
{

    // Inspector
    HelloImGui::DockableWindow w_inspector;
    w_inspector.label = ICON_FA_SEARCH " Inspector";
    w_inspector.dockSpaceName = "Inspector";
    w_inspector.GuiFunction = [&]
    { create_inspector(settings); };

    // Scene
    HelloImGui::DockableWindow w_scene;
    // w_scene.label = ICON_FA_CROSSHAIRS " Simulation";
    w_scene.label = ICON_FA_TV " Scene";
    w_scene.dockSpaceName = "MainDockSpace";
    w_scene.GuiFunction = [&]
    { create_scene(); };

    // Node Hierarchy
    HelloImGui::DockableWindow w_hierarchy;
    w_hierarchy.label = ICON_FA_SITEMAP " Hierarchy";
    w_hierarchy.dockSpaceName = "Hierarchy";
    w_hierarchy.GuiFunction = [&]
    { create_hierarchy(); };

    // Plots
    HelloImGui::DockableWindow w_plots;
    w_plots.label = ICON_FA_CHART_AREA " Plots";
    w_plots.dockSpaceName = "Inspector";
    w_plots.GuiFunction = [&]
    { create_plots(); };

    // Logger
    HelloImGui::DockableWindow w_logger;
    w_logger.label = ICON_FA_TERMINAL " Console";
    w_logger.dockSpaceName = "Logs";
    w_logger.GuiFunction = []
    { HelloImGui::LogGui(); };

    std::vector<HelloImGui::DockableWindow>
        dockableWindows{
            w_scene,
            w_inspector,
            w_hierarchy,
            w_plots,
            w_logger};

    return dockableWindows;
}

void UILayer::create_scene()
{
    ImGui::BeginChild("Scene");

    auto& io = ImGui::GetIO();
    auto dt = io.DeltaTime;

    // Get window size and content region size
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 contentRegion = ImGui::GetContentRegionAvail();
    ImVec2 mouseDelta = io.MouseDelta;

    if (ImGui::IsWindowFocused() && ImGui::IsWindowHovered())
    {
        if (m_SelectedEntityId != -1)
        {
            // ImGui::Text("Selected Entity: %d", m_SelectedEntityId);
            // ImGui::Text("Mouse Clicked: %d", io.MouseDown[0]);
        }

        // Check if mouse is clicked then apply rotation
        io.MouseDown[0] ? m_rotation.x += mouseDelta.y : 0;
        io.MouseDown[0] ? m_rotation.z += mouseDelta.x : 0;
    }
    if (ImGui::IsWindowFocused())
    {
        // Check if keys are pressed then apply translation
        io.KeysData[ImGuiKey_A].Down ? m_position[0] += 1.0f * dt : 0;
        io.KeysData[ImGuiKey_D].Down ? m_position[0] -= 1.0f * dt : 0;

        io.KeysData[ImGuiKey_Q].Down ? m_position[1] -= 1.0f * dt : 0;
        io.KeysData[ImGuiKey_E].Down ? m_position[1] += 1.0f * dt : 0;

        io.KeysData[ImGuiKey_W].Down ? m_position[2] += 1.0f * dt : 0;
        io.KeysData[ImGuiKey_S].Down ? m_position[2] -= 1.0f * dt : 0;
    }

    ImGui::Image((void *)(intptr_t)m_textureColorBuffer, ImVec2(contentRegion.x, contentRegion.y), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::EndChild();
}

void UILayer::create_hierarchy()
{
    if (m_settings.show_demo)
        ImGui::ShowDemoWindow();

    static int selectionMask = (1 << 0);
    int node_clicked = -1;

    static uint32_t selectedEntity = -1;
    uint32_t entityClicked = -1;

    m_Scene->Reg().view<TagComponent>().each([&entityClicked](auto entity, auto &tag)
    {
        ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        bool isSelected = (selectedEntity == (uint32_t)entity);
        if (isSelected)
        {
            node_flags |= ImGuiTreeNodeFlags_Selected;
        }
        bool node_open = ImGui::TreeNodeEx((void *)(intptr_t)entity, node_flags, "%s", tag.tag.c_str());
        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        {
            entityClicked = (uint32_t)entity;
        }
        if (node_open)
        {
            ImGui::Text("Tag: %s", tag.tag.c_str());
            ImGui::TreePop();
        }
    });

    if (entityClicked != -1)
    {
        // Update selection state
        // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
        if (ImGui::GetIO().KeyCtrl)
        {
            selectedEntity = -1;                  // CTRL+click to toggle
            m_SelectedEntityId = -1;
        }
        else                                      // if (!(selectionMask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
        {
            selectedEntity = entityClicked;       // Click to single-select
            m_SelectedEntityId = selectedEntity;
        }    
            
    }

}

void UILayer::create_plots()
{
    // if (ImGui::Button("Show Demo", HelloImGui::EmToVec2(7.f, 0.f)))
    //     ImGui::ShowDemoWindow();
    float t = ImGui::GetIO().DeltaTime;
    float framerate = 1 / t;
    // printf("framerate: %0f\n", framerate);

    // Append to plot data
    if (ImPlot::BeginPlot("FPS", ImVec2(-1, 250)))
    {

        // Setup Axis
        // Plot data
        ImPlot::EndPlot();
    }
}

void UILayer::create_inspector(AppSettings &settings)
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 0.0f, 0.5f, 0.0f)); // Set window background to red
    ImGui::BeginChild("Empty");
    ImGui::PopStyleColor();

    // Get entity
    if (m_SelectedEntityId != -1)
    {
        // Create popup menu with list of available components
        bool addComponent = false;

        if (ImGui::Button("Add component", ImVec2(-1, 0)))
        {
            // Create popup menu with list of available components
            ImGui::OpenPopup("Add Component");
        }

        if (ImGui::BeginPopup("Add Component"))
        {
            if (ImGui::Selectable("Transform"))
            {
                bool hasComponent = m_Scene->Reg().any_of<TransformComponent>((entt::entity)m_SelectedEntityId);
                if (!hasComponent)
                    m_Scene->Reg().emplace<TransformComponent>((entt::entity)m_SelectedEntityId);
                else
                {
                    auto tag = m_Scene->Reg().get<TagComponent>((entt::entity)m_SelectedEntityId).tag;
                    HelloImGui::Log(HelloImGui::LogLevel::Error, "#%0u (%s): Transform component already exists!", (uint32_t)m_SelectedEntityId, tag.c_str());
                }
            }
            if (ImGui::Selectable("Camera Component"))
            {
                bool hasComponent = m_Scene->Reg().any_of<CameraComponent>((entt::entity)m_SelectedEntityId);
                if (!hasComponent)
                    m_Scene->Reg().emplace<CameraComponent>((entt::entity)m_SelectedEntityId);
                else
                {
                    auto tag = m_Scene->Reg().get<TagComponent>((entt::entity)m_SelectedEntityId).tag;
                    HelloImGui::Log(HelloImGui::LogLevel::Error, "#%0u (%s): Camera component already exists!", (uint32_t)m_SelectedEntityId, tag.c_str());
                }
            }
            ImGui::EndPopup();
        }

        ImGui::Separator();

        if (m_Scene->Reg().any_of<TagComponent>((entt::entity)m_SelectedEntityId))
        {
            // Get tag
            static bool allowEditing = true;
            static std::string tag;
            auto& tagComponent = m_Scene->Reg().get<TagComponent>((entt::entity)m_SelectedEntityId);
            tag = tagComponent.tag;

            ImGui::Checkbox("##", &allowEditing);
            ImGui::SameLine();
            ImGui::InputText("Name", &tagComponent.tag, allowEditing ? 0 : ImGuiInputTextFlags_ReadOnly);
            ImGui::Separator();
        }

        if (m_Scene->Reg().any_of<TransformComponent>((entt::entity)m_SelectedEntityId))
        {
            if (ImGui::CollapsingHeader(ICON_FA_LOCATION_ARROW "\tTransform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::DragFloat3("Position", glm::value_ptr(m_Scene->Reg().get<TransformComponent>((entt::entity)m_SelectedEntityId).position), 0.1f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(m_Scene->Reg().get<TransformComponent>((entt::entity)m_SelectedEntityId).rotation), 1.0f, -180.0f, 180.0f);
                ImGui::DragFloat3("Scale", glm::value_ptr(m_Scene->Reg().get<TransformComponent>((entt::entity)m_SelectedEntityId).scale), 0.1f);
                ImGui::Separator();
            }
        }

        if (m_Scene->Reg().any_of<CameraComponent>((entt::entity)m_SelectedEntityId))
        {
            if (ImGui::CollapsingHeader(ICON_FA_CAMERA "\tCamera", ImGuiTreeNodeFlags_DefaultOpen))
            {
                static bool primaryCamera = true;
                ImGui::DragFloat3("Position", glm::value_ptr(m_CameraPosition), 0.1f);
                ImGui::DragFloat("Rotation", &m_CameraRotation, 1.0f, -180.0f, 180.0f);
                ImGui::DragFloat("Move Speed", &m_CameraMoveSpeed, 1.0f, 0.0f, 100.0f);
                ImGui::DragFloat("Rotation Speed", &m_CameraRotationSpeed, 1.0f, 0.0f, 360.0f);
                ImGui::Checkbox("Primary Camera", &primaryCamera);
                ImGui::Separator();
            }
        }

    } else
    {
        std::string noEntitySelected = "No entity selected";
        std::string deselect = "CTRL+RClick to deselect";
        // Center the text in the window
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(noEntitySelected.c_str()).x) / 2);
        ImGui::Text("%s", noEntitySelected.c_str());
        ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(deselect.c_str()).x) / 2);
        ImGui::Text("%s", deselect.c_str());

        ImGui::Separator();

        ImGui::DragFloat3("Position", glm::value_ptr(m_position), 0.1f);
        ImGui::DragFloat3("Rotation", glm::value_ptr(m_rotation), 1.0f);
        ImGui::DragFloat3("Scale", glm::value_ptr(m_scale), 0.1f);
    }
    
    ImGui::EndChild();
}

void UILayer::start_event_loop()
{
    // ImmApp::Run(m_runner_params);
}

std::string UILayer::load_shader(std::string file)
{
    // Open a file and read the content into a char *
    std::string content;
    std::ifstream fileStream(file, std::ios::in);

    if (!fileStream.is_open())
    {
        HelloImGui::Log(HelloImGui::LogLevel::Error, "Could not read file: %s\n", file.c_str());
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();

    std::string filename = file.substr(file.find_last_of("/") + 1);
    HelloImGui::Log(HelloImGui::LogLevel::Debug, "Loaded shader: %s\n", filename.c_str());

    return content;
}

void UILayer::show_menu()
{
    if (ImGui::BeginMenu("Settings"))
    {
        if (ImGui::BeginMenu("Demo Window"))
        {
            ImGui::Checkbox("Show", &m_settings.show_demo);
            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }
}

void UILayer::status_bar()
{
}
