#include "ParameterUI.h"


ParameterUI::ParameterUI(/* args */)
{
}

ParameterUI::ParameterUI(AppSettings settings)
{

    this->node_flags = static_cast<ImGuiTreeNodeFlags_>(ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth);

    this->m_settings = settings;

    this->m_renderer = RenderEngine();

    this->initialize();
}

ParameterUI::~ParameterUI()
{
}

void ParameterUI::initialize()
{
    HelloImGui::SetAssetsFolder(this->m_settings.asset_path);
    printf("added asset folder: %s\n", this->m_settings.asset_path.c_str());

    auto mySettings = m_settings;

    this->runner_params.appWindowParams.windowTitle = this->m_settings.title;
    this->runner_params.imGuiWindowParams.menuAppTitle = "File";
    this->runner_params.appWindowParams.windowGeometry.size = {this->m_settings.v_width, this->m_settings.v_height};
    this->runner_params.appWindowParams.restorePreviousGeometry = false;
    // this->runner_params.appWindowParams.borderless = true;
    // this->runner_params.appWindowParams.borderlessMovable = true;
    // this->runner_params.appWindowParams.borderlessResizable = true;
    // this->runner_params.appWindowParams.borderlessClosable = true;

    // Add fonts
    runner_params.callbacks.LoadAdditionalFonts = [=]()
    { this->load_font(mySettings); };

    buffer_size = 2000;

    // Status bar
    this->runner_params.imGuiWindowParams.showStatusBar = true;
    this->runner_params.callbacks.ShowStatus = [this]()
    { this->status_bar(); };

    // Menu Bar
    this->runner_params.imGuiWindowParams.showMenuBar = true;
    this->runner_params.imGuiWindowParams.showMenu_App = true;
    this->runner_params.imGuiWindowParams.showMenu_View = true;
    this->runner_params.callbacks.ShowMenus = [this]()
    { this->show_menu(); };

    // Toolbar

    // Theme
    auto &tweakedTheme = this->runner_params.imGuiWindowParams.tweakedTheme;
    tweakedTheme.Theme = ImGuiTheme::ImGuiTheme_SoDark_AccentBlue;
    tweakedTheme.Tweaks.Rounding = 10.f;
    // 2. Customize ImGui style at startup
    this->runner_params.callbacks.SetupImGuiStyle = []()
    {
        // Reduce spacing between items ((8, 4) by default)
        ImGui::GetStyle().ItemSpacing = ImVec2(6.f, 4.f);
    };

    // Create Layout
    // First, tell HelloImGui that we want full screen dock space (this will create "MainDockSpace")
    this->runner_params.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
    this->runner_params.imGuiWindowParams.enableViewports = true;
    this->runner_params.dockingParams = create_layout();

    // ###############################
    // PostInit & BeforeExit callbacks
    // #####################################################
    // FIXME: Update reading shaders from assets directory
    // #####################################################
    runner_params.callbacks.PostInit = [&, this]()
    { m_renderer.initialize(); };
    // runner_params.callbacks.BeforeExit = [&]()
    // { m_renderer.destroy_resources(); };

    // #####################################################
    // Custom background
    // #####################################################
    runner_params.callbacks.CustomBackground = [&, this]()
    { m_renderer.render(); };

    // Add save location
    this->runner_params.iniFolderType = HelloImGui::IniFolderType::AppUserConfigFolder;
    this->runner_params.iniFilename = this->m_settings.log_file.c_str();

    // Initialize Plots
    this->m_plot_context = ImPlot::CreateContext();
}

HelloImGui::DockingParams ParameterUI::create_layout()
{
    HelloImGui::DockingParams docking_params;

    docking_params.dockingSplits = create_docking_splits();
    docking_params.dockableWindows = create_docking_windows(m_settings);

    return docking_params;
}

std::vector<HelloImGui::DockingSplit> ParameterUI::create_docking_splits()
{
    //     _____________________________________________
    //    |          |                      |          |
    //    | Inspector|                      | Entity   |
    //    |          |    MainDockSpace     |          |
    //    |          |                      |          |
    //    |          |                      |          |
    //    |          |                      |          |
    //    |          |----------------------|----------|
    //    |          |  Logs                           |
    //    ---------------------------------------------|
    HelloImGui::DockingSplit inspector_split;
    inspector_split.initialDock = "MainDockSpace";
    inspector_split.newDock = "Inspector";
    inspector_split.direction = ImGuiDir_Left;
    inspector_split.ratio = 0.2f;

    HelloImGui::DockingSplit logs_split;
    logs_split.initialDock = "Inspector";
    logs_split.newDock = "Logs";
    logs_split.direction = ImGuiDir_Down;
    logs_split.ratio = 0.35f;

    HelloImGui::DockingSplit scene_split;
    scene_split.initialDock = "MainDockSpace";
    scene_split.newDock = "Scene";
    scene_split.direction = ImGuiDir_Right;
    scene_split.ratio = 0.25f;

    std::vector<HelloImGui::DockingSplit> splits{
        inspector_split,
        logs_split,
        scene_split};

    return splits;
}

std::vector<HelloImGui::DockableWindow> ParameterUI::create_docking_windows(AppSettings &settings)
{

    // Inspector
    HelloImGui::DockableWindow w_inspector;
    w_inspector.label = ICON_FA_SEARCH " Inspector";
    w_inspector.dockSpaceName = "Inspector";
    w_inspector.GuiFunction = [&]
    { create_inspector(settings); };

    // Node Hierarchy
    HelloImGui::DockableWindow w_hierarchy;
    w_hierarchy.label = ICON_FA_SITEMAP " Hierarchy";
    w_hierarchy.dockSpaceName = "Scene";
    w_hierarchy.GuiFunction = [&]
    { create_hierarchy(); };

    // Scene View
    // HelloImGui::DockableWindow w_scene;
    // w_scene.label = ICON_FA_IMAGE " Scene";
    // w_scene.dockSpaceName = "MainDockSpace";
    // w_scene.GuiFunction = [&]
    // { create_scene(); };

    // Plots
    HelloImGui::DockableWindow w_plots;
    w_plots.label = ICON_FA_CHART_AREA " Plots";
    w_plots.dockSpaceName = "Scene";
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
            w_inspector,
            w_hierarchy,
            // w_scene,
            w_plots,
            w_logger};

    return dockableWindows;
}

void ParameterUI::create_hierarchy()
{
}

void ParameterUI::create_scene()
{
    ImGui::BeginChild("Scene");
    ImGui::Text("Scene Framebuffer");

    float w_width = ImGui::GetContentRegionAvail().x;
    float w_height = ImGui::GetContentRegionAvail().y;

    printf("width:%0f, height:%0f\n", w_width, w_height);

    ImVec2 pos = ImGui::GetCursorScreenPos();
    printf("screen x:%0f, y:%0f\n", pos.x, pos.y);

    // Check variables
    // printf("Render class m_shader: 0x%0x\n", m_renderer.m_shader_program);
    // printf("Render class m_vao: 0x%0x\n", m_renderer.m_vao);
    // printf("Render class m_vbo: 0x%0x\n", m_renderer.m_vbo);
    // printf("Render class m_fbo: 0x%0x\n", m_renderer.m_fbo);
    // printf("Render class m_texture_id: 0x%0x\n", m_renderer.m_texture_id);

    // Rescale framebuffer
    // glEnable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, m_renderer.m_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w_width, w_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderer.m_texture_id, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_renderer.m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w_width, w_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderer.m_rbo);

    // Update Viewport
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, w_width, w_height);

    ImGui::GetWindowDrawList()->AddImage(
        // (void *)m_renderer.m_texture_id,
        reinterpret_cast<GLuint *>(m_renderer.m_texture_id),
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + w_width, pos.y + w_height),
        ImVec2(0, 1),
        ImVec2(1, 0));


    // Drawing the triangle to the screen
    // Step 1: Bind the Framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER, m_renderer.m_fbo);
    // Step 2: Enable the shader program
    glUseProgram(m_renderer.m_fbo);
    // Step 3: Bind the Vertex Array Object
    glBindVertexArray(m_renderer.m_vao);
    // Step 4: Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // Step 5: Unbind the Vertex Array Object
    glBindVertexArray(0);
    // Step 6: Disable the shader program
    glUseProgram(0);
    // Step 7: Unbind the Framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::EndChild();
}

void ParameterUI::create_plots()
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

void ParameterUI::create_inspector(AppSettings &settings)
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 0.0f, 0.5f, 0.0f)); // Set window background to red
    ImGui::BeginChild("Empty");
    ImGui::PopStyleColor();
    ImGui::Text("Inspector");
    

    ImGui::EndChild();
}

void ParameterUI::show_menu()
{
}

void ParameterUI::status_bar()
{
}

void ParameterUI::load_font(AppSettings settings)
{

    HelloImGui::Log(HelloImGui::LogLevel::Debug, "Adding font: %s, %f\n", settings.font_path.c_str(), settings.font_size);
    
    HelloImGui::ImGuiDefaultSettings::LoadDefaultFont_WithFontAwesomeIcons();
    this->ui_font = HelloImGui::LoadFontTTF(settings.font_path.c_str(), settings.font_size);
}

void ParameterUI::start_event_loop()
{
    ImmApp::Run(this->runner_params);
}
