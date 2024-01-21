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

    // New 

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
