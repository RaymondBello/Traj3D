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
}

void UILayer::destroy_renderer()
{
    glDeleteVertexArrays(0, &m_vao);
    glDeleteBuffers(0, &m_vbo);
    glDeleteBuffers(0, &m_ibo);

}

void UILayer::setup_renderer()
{
    // // Create and initialize a new renderer object
    // m_Renderer = new Renderer();

    // // Set camera position and initialize the orthographic camera with the specified values
    // m_CameraPosition = glm::vec3(5.0f, 5.0f, 1.0f);
    // m_Camera = OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
    // m_Camera.SetPosition(m_CameraPosition);

    // // Create a vertex array for a triangle
    // m_VertexArray = VertexArray::Create();

    // // Define the vertices of the triangle and set up the vertex buffer with the corresponding layout
    // float vertices[3 * 7] = {
    //     -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
    //     0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
    //     0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f};
    // std::shared_ptr<VertexBuffer> vertexBuffer;
    // vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
    // BufferLayout layout = {
    //     {ShaderDataType::Float3, "a_Position"},
    //     {ShaderDataType::Float4, "a_Color"}
    // };
    // vertexBuffer->SetLayout(layout);
    // m_VertexArray->AddVertexBuffer(vertexBuffer);

    // // Define the indices of the triangle and set up the index buffer
    // uint32_t indices[3] = {0, 1, 2};
    // std::shared_ptr<IndexBuffer> indexBuffer;
    // indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    // m_VertexArray->SetIndexBuffer(indexBuffer);

    // // Create a vertex array for a square
    // m_SquareVA = VertexArray::Create();

    // // Define the vertices of the square and set up the vertex buffer with the corresponding layout
    // float squareVertices[3 * 4] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.5f, 0.5f, 0.0f,
    //     -0.5f, 0.5f, 0.0f};
    // std::shared_ptr<VertexBuffer> squareVB;
    // squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    // squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
    // m_SquareVA->AddVertexBuffer(squareVB);

    // // Define the indices of the square and set up the index buffer
    // uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    // std::shared_ptr<IndexBuffer> squareIB;
    // squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    // m_SquareVA->SetIndexBuffer(squareIB);

    // // Compile shader programs from files and create shaders
    // std::string vertSrc, fragSrc;
    // vertSrc = load_shader(get_assets_folder() + "shaders/shader.vert");
    // fragSrc = load_shader(get_assets_folder() + "shaders/shader.frag");
    // m_Shader = Shader::Create(vertSrc, fragSrc);

    // std::string flatVertSrc, flatFragSrc;
    // flatVertSrc = load_shader(get_assets_folder() + "shaders/flat_shader.vert");
    // flatFragSrc = load_shader(get_assets_folder() + "shaders/flat_shader.frag");
    // m_FlatColorShader = Shader::Create(flatVertSrc, flatFragSrc);

    // Print OpenGL version
    HelloImGui::Log(HelloImGui::LogLevel::Info, "Initializing OpenGL version: %s\n", glGetString(GL_VERSION));

    // Compile shader programs from files and create shaders
    std::string vertSrc, fragSrc;
    vertSrc = load_shader(get_assets_folder() + "shaders/default.vert");
    fragSrc = load_shader(get_assets_folder() + "shaders/default.frag");
    m_Shader = new OpenGLShader(vertSrc, fragSrc);

    // Create a vertex array for a triangle
    // m_VertexArray = new OpenGLVertexArray();

    GLfloat vertices[] =
        {
            // position        // color
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    1.0f, 0.0f, 0.0f,   // Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3,  0.0f,    0.0f, 1.0f, 0.0f,  // Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  0.0f, 0.0f, 1.0f   // Upper corner
        };

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



    // // Define the vertices of the triangle and set up the vertex buffer with the corresponding layout
    // std::shared_ptr<OpenGLVertexBuffer> vertexBuffer;
    // vertexBuffer.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices)));
    // BufferLayout layout = {
    //     {ShaderDataType::Float3, "a_Position"}
    // };
    // vertexBuffer->SetLayout(layout);
    // m_VertexArray->AddVertexBuffer(vertexBuffer);


    // Create reference containers for the Vertex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO, EBO;

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Vertex Position Attribute (0) Definition
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0); // Enable the Vertex Attribute so that OpenGL knows to use it

    // Vertex Color Attribute (1) Definition
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeVertexIndices), cubeVertexIndices, GL_STATIC_DRAW);

    // auto initModelMatrix = glm::mat4(1.0f);
    // auto initModelMatrixLocation = glGetUniformLocation(m_Shader->m_RendererID, "u_ModelMatrix");
    // glUniformMatrix4fv(initModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(initModelMatrix));

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->m_vao = VAO;
    this->m_vbo = VBO;
    this->m_ibo = EBO;

    this->m_indexCount = (GLuint)(sizeof(cubeVertexIndices) / sizeof(GLuint));
}

void UILayer::on_renderer_update()
{
    auto &io = ImGui::GetIO();
    auto r = ImVec2(io.DisplaySize.x * io.DisplayFramebufferScale.x,
                    io.DisplaySize.y * io.DisplayFramebufferScale.y);

    ImVec2 displaySize = r;

    // RenderCommand::Clear();
    // RenderCommand::SetClearColor({1.0f, 0.5f, 0.2f, 1});
    // RenderCommand::SetViewport(0, 0, displaySize.x, displaySize.y);
    glClearColor(0.30f, 0.55f, 0.65f, 1.0f);
    glViewport(0, 0, (GLsizei)displaySize.x, (GLsizei)displaySize.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glUseProgram(m_Shader->m_RendererID);
    auto modelMatrix = glm::mat4(1.0f);

    // Add translation to the model matrix
    modelMatrix = glm::translate(modelMatrix, m_position);

    // Add rotation to the model matrix
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));

    // Add scale to the model matrix
    modelMatrix = glm::scale(modelMatrix, m_scale);

    auto shaderId = m_Shader->m_RendererID;
    auto modelMatrixLocation = glGetUniformLocation(shaderId, "u_ModelMatrix");
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    auto viewMatrix = glm::mat4(1.0f);
    auto viewMatrixLocation = glGetUniformLocation(shaderId, "u_ViewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    auto projectionMatrix = glm::perspective(glm::radians(60.0f), displaySize.x / displaySize.y, 0.1f, 100.0f);
    // auto projectionMatrix = glm::ortho(-3.0f, 3.0f, -2.0f, 2.0f, -1.0f, 1.0f);
    // Create a projection matrix with the ratio of 16:9 but 3.

    auto projectionMatrixLocation = glGetUniformLocation(shaderId, "u_ProjectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // HelloImGui::Log(HelloImGui::LogLevel::Info, "DeltaTime: %0f\n", io.DeltaTime);

    glBindVertexArray(m_vao);

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);


    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    // glDepthFunc(GL_GREATER);
    // glDisable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CCW);
    // glCullFace(GL_FRONT);
    glCullFace(GL_BACK);
    // glDisable(GL_CULL_FACE);


    // m_Camera.SetPosition(m_CameraPosition);
    // m_Camera.SetRotation(m_CameraRotation);

    // m_Renderer->BeginScene(m_Camera);

    // glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    // // std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->Bind();
    // ((OpenGLShader *)m_FlatColorShader)->Bind();

    // // std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
    // ((OpenGLShader *)m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

    // for (int y = 0; y < 20; y++)
    // {
    //     for (int x = 0; x < 20; x++)
    //     {
    //         glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
    //         glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

    //         // auto flatColorShader = ((OpenGLShader *)m_FlatColorShader);
    //         // auto squareVA = ((VertexArray *)m_SquareVA);

    //         // auto flatShader = std::make_shared<OpenGLShader>(flatColorShader);
    //         m_Renderer->Submit(*m_FlatColorShader, *m_SquareVA, transform);
    //     }
    // }

    // m_Renderer->Submit(*m_Shader, *m_VertexArray);

    // m_Renderer->EndScene();
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
    ImGui::ShowDemoWindow();
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

    {
        ImGui::Text("Transform");
        ImGui::Separator();
        ImGui::DragFloat3("Position", glm::value_ptr(m_position), 0.1f);
        ImGui::DragFloat3("Rotation", glm::value_ptr(m_rotation), 1.0f, -180.0f, 180.0f);
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
}

void UILayer::status_bar()
{
}
