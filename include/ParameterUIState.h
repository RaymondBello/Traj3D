#pragma once

#include <sstream>

struct ParameterUIState
{
    bool is_solving = false;
    bool is_running = true;
    bool is_paused = false;
    float loading_progress = 0.0;
    std::string status_message = "[]";
};
