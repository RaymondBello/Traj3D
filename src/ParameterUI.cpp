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

    // PostInit & BeforeExit callbacks
    runner_params.callbacks.PostInit = [&, this]()
    { m_renderer.init_resources(); };
    runner_params.callbacks.BeforeExit = [&]()
    { m_renderer.destroy_resources(); };

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
    inspector_split.ratio = 0.25f;

    HelloImGui::DockingSplit logs_split;
    logs_split.initialDock = "MainDockSpace";
    logs_split.newDock = "Logs";
    logs_split.direction = ImGuiDir_Down;
    logs_split.ratio = 0.25f;

    HelloImGui::DockingSplit scene_split;
    scene_split.initialDock = "MainDockSpace";
    scene_split.newDock = "Scene";
    scene_split.direction = ImGuiDir_Right;
    scene_split.ratio = 0.3f;

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

    // Plots
    HelloImGui::DockableWindow w_plots;
    w_plots.label = ICON_FA_CHART_AREA " Plots";
    w_plots.dockSpaceName = "MainDockSpace";
    w_plots.GuiFunction = [&]
    { create_plots(); };

    // Scene View
    HelloImGui::DockableWindow w_scene;
    w_scene.label = ICON_FA_IMAGE " Scene";
    w_scene.dockSpaceName = "MainDockSpace";
    w_scene.GuiFunction = [&]
    { create_scene(); };

    // Logger
    HelloImGui::DockableWindow w_logger;
    w_logger.label = ICON_FA_TERMINAL " Console";
    w_logger.dockSpaceName = "Logs";
    w_logger.GuiFunction = []
    { HelloImGui::LogGui(); };

    // Node Hierarchy
    HelloImGui::DockableWindow w_hierarchy;
    w_hierarchy.label = ICON_FA_SITEMAP " Hierarchy";
    w_hierarchy.dockSpaceName = "Scene";
    w_hierarchy.GuiFunction = [&]
    { create_hierarchy(); };

    std::vector<HelloImGui::DockableWindow>
        dockableWindows{
            w_inspector,
            w_scene,
            w_plots,
            w_logger,
            w_hierarchy};

    return dockableWindows;
}

void ParameterUI::create_hierarchy()
{
}

void ParameterUI::create_scene()
{
    ImGui::Text("Scene Framebuffer");

    float w_width = ImGui::GetContentRegionAvail().x;
    float w_height = ImGui::GetContentRegionAvail().y;

    // printf("width:%0f, height:%0f\n", w_width, w_height);


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
    ImGui::Text("Inspector");
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
