#pragma once

class MeshSystem
{
private:
    /* data */
    entt::registry *m_registry;

public:
    MeshSystem(entt::registry *reg);
    ~MeshSystem();
    bool load_mesh(MeshComponent mesh);
    void process();
};

MeshSystem::MeshSystem(entt::registry *reg)
{
    HelloImGui::Log(HelloImGui::LogLevel::Info, "Init MeshSystem");
    m_registry = reg;
}


bool MeshSystem::load_mesh(MeshComponent mesh)
{

    // Show Component attributes
    HelloImGui::Log(HelloImGui::LogLevel::Debug, "mesh_path: %s, configured: %0d, loaded: %0d", mesh.m_filename.c_str(), mesh.is_configured, mesh.is_loaded);

    
    return true;
}

void MeshSystem::process()
{
    auto view = m_registry->view<MeshComponent>();
    for (auto [entity, mesh] : view.each())
    {
        

        // Add functionality 
        if (!mesh.is_loaded && mesh.is_configured) // Check if mesh is not loaded, then load it
        {
            if (load_mesh(mesh))
                mesh.is_loaded = true;
        }
    }
}

MeshSystem::~MeshSystem()
{}
