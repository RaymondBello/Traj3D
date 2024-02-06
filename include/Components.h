#pragma once

// #include <stdio.h>
// #include <sstream>
// #include <iostream>
// #include <fstream>
// #include <string>

//===================================================
// Define Helper structs
//===================================================
struct Vertex
{
    glm::vec3 m_pos;
    glm::vec2 m_tex;
    glm::vec3 m_normal;

    Vertex() : m_pos(glm::vec3(0.0f)), m_tex(glm::vec2(0.0f)), m_normal(glm::vec3(0.0f)) {}

    Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 normal)
    {
        m_pos = pos;
        m_tex = tex;
        m_normal = normal;
    }

    Vertex(glm::vec3 pos, glm::vec2 tex)
    {
        m_pos = pos;
        m_tex = tex;
        m_normal = glm::vec3(0.0f, 0.0f, 0.0f);
    }
};


//===================================================
// Define Components
//===================================================
struct TransformComponent
{
    /* data */
};

struct CameraComponent
{
    // Constants (make const?)
    float ROTATION_SPEED  = 2.0f;
    const glm::vec3 RIGHT       = {1.0f, 0.0f, 0.0f};
    const glm::vec3 UP          = {0.0f, 1.0f, 0.0f};
    const glm::vec3 FORWARD     = {0.0f, 0.0f, -1.0f};

    // Camera Attributes
    float m_aspect;
    float m_fov;
    float m_near;
    float m_far;
    float m_distance = 5.0f;
    glm::vec3 mFocus = {0.0f, 0.0f, 0.0f};

    // Orientation
    float m_pitch = 0.0f;
    float m_yaw = 0.0f;

    // World position and mouse screen coords
    glm::mat4 m_view_mat;
    glm::mat4 m_proj_mat = glm::mat4{1.0f};
    glm::vec3 m_position = {0.0f, 0.0f, 0.0f};

    // Mouse 2d screen coords
    glm::vec2 m_curr_mouse;

};

struct ModelComponent
{
    // Path to mesh
    std::string m_filename;

    // Vertex buffer array and index array
    GLuint m_vbo;
    GLuint m_ebo;

    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

    // Bool to manage state
    bool is_configured = false;
    bool is_loaded = false;

    // Size of arrays
    unsigned int m_num_indices;
    unsigned int m_num_materials;

};

struct ShaderComponent
{
    unsigned int m_shader_id;

    std::string m_vert_shader;
    std::string m_frag_shader;

    const char *m_shader_source;

    bool is_active= false;
    bool is_compiled = false;
};

