#pragma once
#include <sstream>

struct AppSettings
{
    std::string title;
    int v_width;
    int v_height;
    bool show_demo;
    bool no_title_bar;
    bool menubar;
    bool fps_idling;
    bool restore_previous_dimensions;
    std::string log_file;
    std::string font_path;
    std::string asset_path;
    float font_size;
};

