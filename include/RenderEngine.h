#pragma once
#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui_internal.h"

// #include <GLFW/glfw3.h>
// #include "imgui/backends/imgui_impl_glfw.h"
// #include "imgui/backends/imgui_impl_opengl3_loader.h"
// #include "imgui/backends/imgui_impl_opengl3.h"

#include "hello_imgui/hello_imgui_include_opengl.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> // for UniformsList
// #include <OpenGL/gltypes.h>

class RenderEngine
{
private:
    /* data */
    std::string m_vert_shader;
    std::string m_frag_shader;

public:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_texture_id;
    GLuint m_shader_program;

    RenderEngine(/* args */);
    ~RenderEngine();

    // Methods
    void init_resources();
    void destroy_resources();
    std::string get_shader_from_file(std::string file);
};
