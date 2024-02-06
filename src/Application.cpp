#include "Application.h"

struct position
{
    float x;
    float y;
};

struct velocity
{
    float dx;
    float dy;
};


Application::Application(/* args */)
{
    printf("created app\n");
}


Application::Application(AppSettings settings)
{
    

    m_registry = entt::registry();

    for (auto i = 0u; i < 10u; ++i)
    {
        const auto entity = m_registry.create();
        auto& camera = m_registry.emplace<CameraComponent>(entity);

        camera.ROTATION_SPEED = 10.0f;
        if (i % 2 == 0) { camera.ROTATION_SPEED = 5.0f; }
    }

    // use a range-for
    auto view = m_registry.view<const CameraComponent>();
    for (auto [entity, cam] : view.each())
    {
        HelloImGui::Log(HelloImGui::LogLevel::Debug, "Entity: %0d, rotation: %0f", entity, cam.ROTATION_SPEED);
    }

    this->m_settings = settings;
    printf("created app: %s with settings\n", (char *)&this->m_settings.title);
    this->m_ui = ParameterUI(settings);
}

Application::~Application()
{
}

void Application::run()
{
    printf("Running App\n");
    this->m_ui.start_event_loop();
}