#include "RenderEngine.h"

RenderEngine::RenderEngine(/* args */)
{

    // Initialize

    // Set uniform defaults
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::init_resources()
{

    //####################################################
    // Create the shader program
    //####################################################
    HelloImGui::Log(HelloImGui::LogLevel::Info, "Initializing OpenGL version: %s\n", glGetString(GL_VERSION));

    std::string shader_vert_src;
    std::string shader_frag_src;

    shader_vert_src = get_shader_from_file("TrajectorySim.app/Contents/Resources/assets/shaders/shader.vert");
    shader_frag_src = get_shader_from_file("TrajectorySim.app/Contents/Resources/assets/shaders/shader.frag");

    // HelloImGui::Log(HelloImGui::LogLevel::Info, "Vertex shader: %s\n", shader_vert_src.c_str());
    // HelloImGui::Log(HelloImGui::LogLevel::Info, "Fragment shader: %s\n", shader_frag_src.c_str());
    
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
        IM_ASSERT(v_shader_status);
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
        IM_ASSERT(f_shader_status);
    }

    // Create shader program
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, v_shader);
    glAttachShader(shader_program, f_shader);
    glLinkProgram(shader_program);

    // Check for link errors
    GLint is_linked;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &is_linked);
    if (!is_linked) {
        GLchar link_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, link_log);
        HelloImGui::Log(HelloImGui::LogLevel::Error, "Shader program linking failed \n%s", link_log);
        IM_ASSERT(is_linked);
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
    IM_ASSERT(glErrorCount == 0);

    //####################################################
    //  Create the Framebuffer (OLD)
    //####################################################
    // // Create Framebuffer QuadVAO
    // // Define the vertex data for a full-screen quad
    // float vertices[] = {
    //     // positions   // texCoords
    //     -1.0f, -1.0f, 0.0f, 0.0f, // bottom left  (0)
    //     1.0f, -1.0f, 1.0f, 0.0f,  // bottom right (1)
    //     -1.0f, 1.0f, 0.0f, 1.0f,  // top left     (2)
    //     1.0f, 1.0f, 1.0f, 1.0f    // top right    (3)
    // };
    // // Generate and bind the VAO
    // GLuint vao;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // // Generate and bind the VBO
    // GLuint vbo;
    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // // Fill the VBO with vertex data
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // Set the vertex attribute pointers
    // // Position attribute
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);
    // // Texture coordinate attribute
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // // Unbind the VAO (and VBO)
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    //####################################################
    //   Create the Framebuffer 
    //####################################################
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, // 1. vertex x, y, z
        1.0f, -1.0f, 0.0f,  // 2. vertex x, y, z
        0.0f, 1.0f, 0.0f    // 3. vertex x, y, z
    };

    // Vertex Array Obj
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex Buffer Obj
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // FrameBuffer & RenderBuffer Obj
    GLuint fbo, rbo, texture_id;
    const GLint WIDTH = 200;
    const GLint HEIGHT = 200;

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        HelloImGui::Log(HelloImGui::LogLevel::Error, "ERROR: Framebuffer is not complete!\n");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    this->m_vao = vao;
    this->m_vbo = vbo;

    this->m_fbo = fbo;
    this->m_rbo = rbo;
    this->m_texture_id = texture_id;
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
