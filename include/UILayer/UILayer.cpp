#include "UILayer.h"

UILayer::UILayer(/* args */)
    : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
}

UILayer::~UILayer()
{
}

UILayer::UILayer(AppSettings &settings)
    : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
    m_settings = settings;
    initialize();
    // setup_renderer();
}

void UILayer::setup_renderer()
{
    m_CameraPosition = glm::vec3(5.0f, 5.0f, 1.0f);
    m_Camera = OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
    m_Camera.SetPosition(m_CameraPosition);

    // Triangle
    m_VertexArray = VertexArray::Create();

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};

    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"}
    };

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = {0, 1, 2};
    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    // Square Geometry
    m_SquareVA = VertexArray::Create();

    float squareVertices[3 * 4] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    std::shared_ptr<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer> squareIB;
    squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    // Compile shader program from files
    std::string vertSrc, fragSrc;
    vertSrc = load_shader(get_assets_folder() + "shaders/shader.vert");
    fragSrc = load_shader(get_assets_folder() + "shaders/shader.frag");
    m_Shader = Shader::Create(vertSrc, fragSrc);

    std::string flatVertSrc, flatFragSrc;
    flatVertSrc = load_shader(get_assets_folder() + "shaders/flat_shader.vert");
    flatFragSrc = load_shader(get_assets_folder() + "shaders/flat_shader.frag");
    m_FlatColorShader = Shader::Create(flatVertSrc, flatFragSrc);
}

void UILayer::on_renderer_update()
{
    auto &io = ImGui::GetIO();
    auto r = ImVec2(io.DisplaySize.x * io.DisplayFramebufferScale.x,
                    io.DisplaySize.y * io.DisplayFramebufferScale.y);

    ImVec2 displaySize = r;

    RenderCommand::Clear();
    RenderCommand::SetClearColor({1.0f, 0.5f, 0.2f, 1});
    RenderCommand::SetViewport(0, 0, displaySize.x, displaySize.y);

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    Renderer::BeginScene(m_Camera);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    // std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->Bind();
    ((OpenGLShader *)m_FlatColorShader)->Bind();

    // std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
    ((OpenGLShader *)m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

            auto flatColorShader = ((OpenGLShader *)m_FlatColorShader);
            auto squareVA = ((VertexArray *)m_SquareVA);

            // auto flatShader = std::make_shared<OpenGLShader>(flatColorShader);
            // Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
        }
    }

    // Renderer::Submit(m_Shader, m_VertexArray);

    Renderer::EndScene();
}


void UILayer::initialize()
{
    HelloImGui::SetAssetsFolder(m_settings.asset_path);
    printf("added asset folder: %s\n", m_settings.asset_path.c_str());

    // Initialize runner params
    m_runner_params.appWindowParams.windowTitle = m_settings.title;
    m_runner_params.imGuiWindowParams.menuAppTitle = "File";
    m_runner_params.appWindowParams.windowGeometry.size = {m_settings.v_width, m_settings.v_height};
    m_runner_params.appWindowParams.restorePreviousGeometry = m_settings.restore_previous_dimensions;

    // Add fonts
    auto my_settings = m_settings;
    m_runner_params.callbacks.LoadAdditionalFonts = [=]()
    { this->setup_fonts(my_settings); };

    // Setup plotting buffers
    PLOT_BUFFER_SIZE = 5000;

    // Status bar
    m_runner_params.imGuiWindowParams.showStatusBar = true;
    m_runner_params.callbacks.ShowStatus = [this]()
    { this->status_bar(); };

    // Menu Bar
    m_runner_params.imGuiWindowParams.showMenuBar = true;
    m_runner_params.imGuiWindowParams.showMenu_App = true;
    m_runner_params.imGuiWindowParams.showMenu_View = true;
    m_runner_params.callbacks.ShowMenus = [this]()
    { this->show_menu(); };

    // Theme
    auto &tweakedTheme = m_runner_params.imGuiWindowParams.tweakedTheme;
    tweakedTheme.Theme = ImGuiTheme::ImGuiTheme_SoDark_AccentBlue;
    tweakedTheme.Tweaks.Rounding = 10.f;
    // 2. Customize ImGui style at startup
    m_runner_params.callbacks.SetupImGuiStyle = []()
    {
        // Reduce spacing between items ((8, 4) by default)
        ImGui::GetStyle().ItemSpacing = ImVec2(6.f, 4.f);
    };

    // Create Layout
    // First, tell HelloImGui that we want full screen dock space (this will create "MainDockSpace")
    m_runner_params.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
    m_runner_params.imGuiWindowParams.enableViewports = true;
    m_runner_params.dockingParams = create_layout();

    // Add save location
    m_runner_params.iniFolderType = HelloImGui::IniFolderType::AppUserConfigFolder;
    m_runner_params.iniFilename = this->m_settings.log_file.c_str();

    // Initialize Plots
    this->m_plot_context = ImPlot::CreateContext();

    // ###############################
    // PostInit & BeforeExit callbacks
    // #####################################################
    m_runner_params.callbacks.PostInit = [&, this]()
    { setup_renderer(); };
    // runner_params.callbacks.BeforeExit = [&]()
    // { m_renderer.destroy_resources(); };

    // #####################################################
    // Custom background
    // #####################################################
    m_runner_params.callbacks.CustomBackground = [&, this]()
    { on_renderer_update(); };
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
    inspector_split.direction = ImGuiDir_Right;
    inspector_split.ratio = 0.2f;

    HelloImGui::DockingSplit logs_split;
    logs_split.initialDock = "MainDockSpace";
    logs_split.newDock = "Logs";
    logs_split.direction = ImGuiDir_Down;
    logs_split.ratio = 0.2f;

    HelloImGui::DockingSplit scene_split;
    scene_split.initialDock = "Inspector";
    scene_split.newDock = "Scene";
    scene_split.direction = ImGuiDir_Up;
    scene_split.ratio = 0.35f;

    std::vector<HelloImGui::DockingSplit> splits{
        inspector_split,
        logs_split,
        scene_split};

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

    // Node Hierarchy
    HelloImGui::DockableWindow w_hierarchy;
    w_hierarchy.label = ICON_FA_SITEMAP " Hierarchy";
    w_hierarchy.dockSpaceName = "Scene";
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
            w_inspector,
            w_hierarchy,
            w_plots,
            w_logger};

    return dockableWindows;
}

void UILayer::create_hierarchy()
{
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
    ImGui::Text("Inspector");

    ImGui::EndChild();
}

void UILayer::start_event_loop()
{
    ImmApp::Run(m_runner_params);
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
}

void UILayer::status_bar()
{
}
