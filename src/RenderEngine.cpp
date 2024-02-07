#include "RenderEngine.h"

std::string get_assets_folder()
{
#ifndef __EMSCRIPTEN__
    return "assets/";
#else
    return "/";
#endif
}

RenderEngine::RenderEngine(/* args */)
{

    // Initialize

    // Set uniform defaults
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::initialize()
{
    HelloImGui::Log(HelloImGui::LogLevel::Info, "Initializing OpenGL version: %s\n", glGetString(GL_VERSION));

    // Initialize shader source
    std::string shader_vert_src;
    std::string shader_frag_src;


    // Create shader program
    shader_vert_src = get_shader_from_file(get_assets_folder() + "shaders/shader.vert");
    shader_frag_src = get_shader_from_file(get_assets_folder() + "shaders/shader.frag");
    

    // Compile vertex shader
    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, reinterpret_cast<const GLchar *const *>(&shader_vert_src), NULL);
    glCompileShader(v_shader);

    // Check if compile failed
    GLint v_shader_status;
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &v_shader_status);
    if (!v_shader_status)
    {
        GLchar info_log[512];
        glGetShaderInfoLog(v_shader, 512, NULL, info_log);
        HelloImGui::Log(HelloImGui::LogLevel::Error, "Vertex shader compile failed \n%s", info_log);
//        IM_ASSERT(v_shader_status);
    }

    // Compile fragment shader
    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, reinterpret_cast<const GLchar *const *>(&shader_frag_src), NULL);
    glCompileShader(f_shader);

    // Check if compile failed
    GLint f_shader_status;
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_shader_status);
    if (!f_shader_status)
    {
        GLchar frag_log[512];
        glGetShaderInfoLog(f_shader, 512, NULL, frag_log);
        HelloImGui::Log(HelloImGui::LogLevel::Error, "Fragment shader compile failed \n%s", frag_log);
//        IM_ASSERT(f_shader_status);
    }

    // Create shader program
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, v_shader);
    glAttachShader(shader_program, f_shader);
    glLinkProgram(shader_program);

    // Check for link errors
    GLint is_linked;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &is_linked);
    if (!is_linked)
    {
        GLchar link_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, link_log);
        HelloImGui::Log(HelloImGui::LogLevel::Error, "Shader program linking failed \n%s", link_log);
//        IM_ASSERT(is_linked);
    }

    // Validate shader
    // glValidateProgram(shader);
    // glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    this->m_shader_program = shader_program;

    // Delete shader objects
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    // Check for any openGL errors
    int glErrorCount = 0;
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        HelloImGui::Log(HelloImGui::LogLevel::Error, "OpenGL error: %0d\n", err);
        ++glErrorCount;
    }
//    IM_ASSERT(glErrorCount == 0);

    // Add Uniforms
    // Uniforms.AddUniform("BG_COLOR", MyVec3{0.8f, 0.9f, 0.6f});

    // Create vertex
    // Define the vertex data for a full-screen quad
    // Vertices coordinates
    GLfloat vertices[] =
        {
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,   // Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
        };

    // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO;

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->m_vao = VAO;
    this->m_vbo = VBO;
}


void RenderEngine::render()
{
    // ####################################################
    //  Create the shader program
    // ####################################################
    // HelloImGui::Log(HelloImGui::LogLevel::Info, "Initializing Renderer. OpenGL version: %s\n", glGetString(GL_VERSION));

    auto &io = ImGui::GetIO();
    auto r = ImVec2(io.DisplaySize.x * io.DisplayFramebufferScale.x,
                    io.DisplaySize.y * io.DisplayFramebufferScale.y);

    ImVec2 displaySize = r;
    glClearColor(0.30f, 0.55f, 0.65f, 1.0f);
    glViewport(0, 0, (GLsizei)displaySize.x, (GLsizei)displaySize.y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_shader_program);
    glBindVertexArray(m_vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0); // Unbind the VAO
    glUseProgram(0);      // Unbind the shader program
}

void RenderEngine::destroy_resources()
{
}

std::string RenderEngine::get_shader_from_file(std::string file)
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

    HelloImGui::Log(HelloImGui::LogLevel::Debug, "Got shader %s\n", file.c_str());

    return content;
}
