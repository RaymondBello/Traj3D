#include "Application.h"


Application::Application(/* args */)
{
    printf("created app\n");
}

Application::Application(AppSettings settings)
{
    this->m_settings = settings;
    printf("created app: %s with settings\n", (char*) &this->m_settings.title);

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