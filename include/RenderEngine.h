#pragma once
#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "hello_imgui/internal/whereami/whereami_cpp.h"
#include "hello_imgui/hello_imgui_include_opengl.h"

#include <lib/glm/vec3.hpp>                 // glm::vec3
#include <lib/glm/vec4.hpp>                 // glm::vec4
#include <lib/glm/mat4x4.hpp>               // glm::mat4
#include <lib/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map> // for UniformsList
// #include <OpenGL/gltypes.h>



struct _Vec2
{
    float x, y;
};

struct _Vec3
{
    float x, y, z;
};

struct _Vec4
{
    float w, x, y, z;
};

template <typename T>
void ApplyUniform(GLint location, const T &value)
{
    if constexpr (std::is_same<T, int>::value)
        glUniform1i(location, value);
    else if constexpr (std::is_same<T, float>::value)
        glUniform1f(location, value);
    else if constexpr (std::is_same<T, _Vec3>::value)
        glUniform3fv(location, 1, &value.x);
    else if constexpr (std::is_same<T, _Vec2>::value)
        glUniform2fv(location, 1, &value.x);
    else if constexpr (std::is_same<T, _Vec4>::value)
        glUniform4fv(location, 1, &value.x);
    else
        IM_ASSERT(false); // Error-out hard, handle all types
}




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

    // UniformsList Uniforms; // the uniforms of the shader program, that enable to modify the shader parameters

    RenderEngine(/* args */);
    ~RenderEngine();

    // Methods
    void initialize();
    void render();
    void destroy_resources();
    std::string get_shader_from_file(std::string file);
};
