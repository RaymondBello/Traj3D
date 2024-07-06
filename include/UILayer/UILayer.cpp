#include "UILayer.h"

UILayer::UILayer(/* args */)
{
    // m_Scene.get() = Scene();
    // m_Scene = std::make_shared<Scene>();
}

UILayer::~UILayer()
{
}

UILayer::UILayer(AppSettings &settings)
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
    m_SelectedEntityId = -1;
    m_Scene = std::make_shared<Scene>();

    m_Scene->BeginScene();
 
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

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Unbind framebuffer
    // glBindRenderbuffer(GL_RENDERBUFFER, 0);
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
    glClearColor(0.30f, 0.55f, 0.65f, 1.0f); // Sky Blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the scene
    // m_Scene->RenderScene(displaySize.x, displaySize.y);

    auto cameraView = m_Scene->Reg().view<CameraComponent>();
    for (auto entity : cameraView)
    {
        auto &camera = cameraView.get<CameraComponent>(entity);
        if (camera.isPrimary)
        {
            

            for (auto &&[entity, mesh, transform] : m_Scene->Reg().view<MeshComponent, TransformComponent>().each())
            {
                if (mesh.shader.instance != nullptr)
                {
                    mesh.shader.instance->Bind();

                    // Update Model Matrix
                    transform.rotation.x += io.DeltaTime * 40.0f;
                    transform.rotation.y += io.DeltaTime * 20.0f;

                    // reset rotation to 0
                    if (transform.rotation.x > 360.0f)
                        transform.rotation.x = 0.0f;
                    if (transform.rotation.y > 360.0f)
                        transform.rotation.y = 0.0f;

                    // Update Model Matrix
                    mesh.shader.instance->UploadUniformMat4("u_ModelMatrix", transform.getMatrix());

                    // Update View Matrix
                    auto viewMatrix = glm::mat4(1.0f);
                    viewMatrix = glm::lookAt(m_position, m_position + m_lookAt, glm::vec3(0.0f, 1.0f, 0.0f));

                    // camera.camera.updateCameraSize(displaySize.x, displaySize.y);
                    // auto viewMatrix = camera.camera.getViewMatrix();

                    mesh.shader.instance->UploadUniformMat4("u_ViewMatrix", viewMatrix);

                    // Update Projection Matrix
                    auto projectionMatrix = glm::perspective(glm::radians(90.0f), displaySize.x / displaySize.y, 0.1f, 100.0f);
                    // auto projectionMatrix = glm::ortho(-3.0f, 3.0f, -2.0f, 2.0f, -1.0f, 1.0f);
                    mesh.shader.instance->UploadUniformMat4("u_ProjectionMatrix", projectionMatrix);

                    // Bind the VAO for this mesh
                    mesh.vao->Bind();

                    // Setup Face culling and depth testing
                    // glEnable(GL_DEPTH_TEST);

                    // glEnable(GL_CULL_FACE);
                    // glCullFace(GL_BACK);

                    glDrawElements(GL_TRIANGLES, mesh.vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);

                    // glDisable(GL_CULL_FACE);
                    // glDisable(GL_DEPTH_TEST);

                    mesh.vao->Unbind();
                }
            }
        }
    }

    

    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
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
        // io.MouseDown[0] ? m_rotation.x += mouseDelta.y : 0;
        // io.MouseDown[0] ? m_rotation.z += mouseDelta.x : 0;

        // auto view = m_Scene->Reg().view<CameraComponent>();
        // for (auto entity : view)
        // {
        //     auto &cameraComponent = view.get<CameraComponent>(entity);
        //     if (cameraComponent.isPrimary)
        //     {
        //         cameraComponent.camera.updateMouseMovement(mouseDelta.x, mouseDelta.y);
        //     }
        // }

        // Check if mouse is clicked then apply translation

        float xoffset;
        float yoffset;

        if (io.MouseDown[0])
        {
            xoffset = mouseDelta.x * m_mouseSpeed;
            yoffset = mouseDelta.y * m_mouseSpeed;

            yaw += xoffset;
            pitch += yoffset;

            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            m_lookAt.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            m_lookAt.y = sin(glm::radians(pitch));
            m_lookAt.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            m_lookAt = glm::normalize(m_lookAt);
        }
        // io.MouseDown[0] ? m_lookAt.y += mouseDelta.y * m_mouseSpeed : 0;
        // io.MouseDown[0] ? m_lookAt.x += mouseDelta.x * m_mouseSpeed : 0;

        // io.MouseDown
    }
    if (ImGui::IsWindowFocused())
    {
        // Check if keys are pressed then apply translation
        io.KeysData[ImGuiKey_Q].Down ? m_position[1] += m_moveSpeed * dt : 0;
        io.KeysData[ImGuiKey_E].Down ? m_position[1] -= m_moveSpeed * dt : 0;

        m_position += io.KeysData[ImGuiKey_W].Down ? m_moveSpeed * dt * m_lookAt : glm::vec3(0.0f);
        m_position -= io.KeysData[ImGuiKey_S].Down ? m_moveSpeed * dt * m_lookAt : glm::vec3(0.0f);
        m_position += io.KeysData[ImGuiKey_D].Down ? glm::normalize(glm::cross(m_lookAt, m_upVector)) * m_moveSpeed * dt : glm::vec3(0.0f);
        m_position -= io.KeysData[ImGuiKey_A].Down ? glm::normalize(glm::cross(m_lookAt, m_upVector)) * m_moveSpeed * dt : glm::vec3(0.0f);
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

    if (ImGui::Button("Create Object", ImVec2(-1, 0)))
    {
        // Create popup menu with list of available components
        ImGui::OpenPopup("create_object");
    }

    if (ImGui::BeginPopup("create_object"))
    {
        for (const auto &pair : ObjectTypeStringMap)
        {
            if (ImGui::Selectable(pair.second.c_str()))
            {
                m_Scene->AddObject(pair.first);
            }
        }
        ImGui::EndPopup();
    }

    ImGui::Separator();

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
        // Get entity
        auto currentEntity = Entity((entt::entity)m_SelectedEntityId, m_Scene.get());

        // Create popup menu with list of available components
        bool addComponent = false;

        if (ImGui::Button("Add component", ImVec2(-1, 0)))
        {
            // Create popup menu with list of available components
            ImGui::OpenPopup("Add Component");
        }

        if (ImGui::BeginPopup("Add Component"))
        {
            if (ImGui::Selectable("Transform Component"))
            {
                // Check if component already exists
                bool hasComponent = currentEntity.HasComponent<TransformComponent>();

                if (!hasComponent)
                    currentEntity.AddComponent<TransformComponent>();
                else
                {
                    auto tag = currentEntity.GetComponent<TagComponent>().tag;
                    HelloImGui::Log(HelloImGui::LogLevel::Error, "#%0u (%s): Transform component already exists!", (uint32_t)currentEntity.ID(), tag.c_str());
                }
            }
            if (ImGui::Selectable("Camera Component"))
            {
                // Check if component already exists
                bool hasComponent = currentEntity.HasComponent<CameraComponent>();

                if (!hasComponent)
                    currentEntity.AddComponent<CameraComponent>();
                else
                {
                    auto tag = currentEntity.GetComponent<TagComponent>().tag;
                    HelloImGui::Log(HelloImGui::LogLevel::Error, "#%0u (%s): Camera component already exists!", (uint32_t)currentEntity.ID(), tag.c_str());
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
                ImGui::DragFloat3("Rotation", glm::value_ptr(m_Scene->Reg().get<TransformComponent>((entt::entity)m_SelectedEntityId).rotation), 1.0f);
                ImGui::DragFloat3("Scale", glm::value_ptr(m_Scene->Reg().get<TransformComponent>((entt::entity)m_SelectedEntityId).scale), 0.1f);
                ImGui::Separator();
            }
        }

        if (m_Scene->Reg().any_of<CameraComponent>((entt::entity)m_SelectedEntityId))
        {
            if (ImGui::CollapsingHeader(ICON_FA_CAMERA "\tCamera", ImGuiTreeNodeFlags_DefaultOpen))
            {
                auto cameraEntity = Entity((entt::entity)m_SelectedEntityId, m_Scene.get());

                ImGui::DragFloat3("Camera Position", glm::value_ptr(cameraEntity.GetComponent<CameraComponent>().camera.position), 0.1f);
                ImGui::DragFloat3("Front Vector", glm::value_ptr(cameraEntity.GetComponent<CameraComponent>().camera.frontVector), 0.1f,-1.0f,1.0f);
                ImGui::DragFloat3("Up Vector", glm::value_ptr(cameraEntity.GetComponent<CameraComponent>().camera.upVector), 0.1f, -1.0f,1.0f);
                ImGui::DragFloat("Field of View", &cameraEntity.GetComponent<CameraComponent>().camera.fieldOfView, 1.0f, 45, 150.0f);
                ImGui::DragFloat("Look Sensitivity", &cameraEntity.GetComponent<CameraComponent>().camera.lookSensitivity, 0.01f, 0.01f, 50.0f);
                ImGui::DragFloat("Look Sensitivity", &cameraEntity.GetComponent<CameraComponent>().camera.zoomSensitivity, 0.01f, 0.01f, 20.0f);
                ImGui::DragFloat("Move Sensitivity", &cameraEntity.GetComponent<CameraComponent>().camera.moveSensitivity, 1.0f, 1.0f, 100.0f);

                ImGui::Checkbox("Primary Camera", &cameraEntity.GetComponent<CameraComponent>().isPrimary);
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
        ImGui::Text("Camera");
        ImGui::DragFloat3("Look At", glm::value_ptr(m_lookAt), 0.01f);
        ImGui::DragFloat("Mouse Speed", &m_mouseSpeed, 0.01f, 0.1f, 1.0f);
        ImGui::DragFloat("Movement Speed", &m_moveSpeed, 0.01f, 0.1f, 50.0f);
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
