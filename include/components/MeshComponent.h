#pragma once


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


struct MeshComponent
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
