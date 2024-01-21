#pragma once
#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> // for UniformsList




class RenderEngine
{
private:
    /* data */
    const char *m_vert_shader;
    const char *m_frag_shader;

    GLuint m_shader_program;
    GLuint m_quad_vao;

public:
    RenderEngine(/* args */);
    ~RenderEngine();

    // Methods
    void init_resources();
    void destroy_resources();
    std::string get_shader_from_file(std::string file);
};
