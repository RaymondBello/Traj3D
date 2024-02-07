#pragma once

// #include <stdio.h>
// #include <sstream>
// #include <iostream>
// #include <fstream>
// #include <string>

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
    float aspect;
    float fov;
    float near;
    float far;
    float distance = 5.0f;
    glm::vec3 mFocus = {0.0f, 0.0f, 0.0f};

    // Orientation
    float pitch = 0.0f;
    float yaw = 0.0f;

    // World position and mouse screen coords
    glm::mat4 view_mat;
    glm::mat4 proj_mat = glm::mat4{1.0f};
    glm::vec3 position = {0.0f, 0.0f, 0.0f};

    // Mouse 2d screen coords
    glm::vec2 curr_mouse;

};



struct ModelComponent
{
    // Path to mesh
    std::string filename;

    // Utilities to load meshes
    Assimp::Importer importer; // https://assimp-docs.readthedocs.io/en/v5.1.0/ ... (An older Assimp website: http://assimp.sourceforge.net/lib_html/index.html)
    const aiScene *scene = nullptr;
    aiNode *root_node = nullptr; // Only being used in the: load_model_cout_console() function.

    // Mesh Struct
    struct Mesh
    {
        unsigned int vao  = 0;
        unsigned int vbo1 = 0;
        unsigned int vbo2 = 0;
        unsigned int vbo3 = 0;
        unsigned int ebo  = 0;
        unsigned int tex_handle;

        std::vector<glm::vec3> vert_positions;
        std::vector<glm::vec3> vert_normals;
        std::vector<glm::vec2> tex_coords;
        std::vector<unsigned int> vert_indices;
    };

    struct Texture
    {
        unsigned int textureID;
        std::string image_name;
    };
    
    // Bool to manage state
    bool is_configured = false;
    bool is_loaded = false;

    // Lists
    unsigned int num_meshes;
    std::vector<Mesh> mesh_list;
    std::vector<Texture> texture_list;

    // Constructor with no arguments
    ModelComponent() : is_configured(false) {}

    // Constructor with path argument
    ModelComponent(const std::string& path) : filename(path), is_configured(true) {}
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

