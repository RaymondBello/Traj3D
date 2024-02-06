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
    std::string log_file;
    std::string font_path;
    std::string asset_path;
    float font_size;
};

