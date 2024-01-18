#pragma once

#include "ApplicationSettings.h"
#include "ParameterUI.h"

class Application
{
private:
    /* data */
    AppSettings m_settings;
    ParameterUI m_ui;
    

public:
    Application();
    Application(AppSettings settings);
    ~Application();

    // Class methods
    void run();
};
