#pragma once

//===================================================
// Define Systems
//===================================================
class ModelSystem
{
private:
    /* data */
    entt::registry *m_registry;

public:

    // Public methods
    ModelSystem(entt::registry *reg)
    {
        HelloImGui::Log(HelloImGui::LogLevel::Info, "Init ModelSystem");
        m_registry = reg;
    }

    bool load_model(ModelComponent model)
    {
        // Show Component attributes
        HelloImGui::Log(HelloImGui::LogLevel::Debug, "model_path: %s, configured: %0d, loaded: %0d", model.m_filename.c_str(), model.is_configured, model.is_loaded);
        return true;
    }

    void process()
    {
        auto view = m_registry->view<ModelComponent>();
        for (auto [entity, model] : view.each())
        {
            // Add functionality 
            if (!model.is_loaded && model.is_configured) // Check if model is not loaded, then load it
            {
                if (load_model(model))
                    model.is_loaded = true;
            }
        }
    }

    // Destructor
    ~ModelSystem(){}
};
