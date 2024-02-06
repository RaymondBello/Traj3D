
struct ShaderComponent
{
    unsigned int m_shader_id;
    unsigned int m_shader_type;

    bool is_active= false;
    bool is_compiled = false;

    const char *m_shader_source;

};
