#include <stdio.h>
#include "../include/Application.h"

int main(int, char **)
{
    AppSettings settings;
    settings.title = "Flight Trajectory";
    settings.v_width = 1400;
    settings.v_height = 900;
    settings.log_file = "config.ini";
    settings.font_path = "fonts/SF-Pro.ttf";
    settings.font_size = 17.0;
    settings.asset_path = "assets/";

    Application app = Application(settings);
    app.run();
}
