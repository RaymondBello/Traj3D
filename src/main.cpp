
#include <stdio.h>
#include <Application.h>

#ifdef __EMSCRIPTEN__
#include "imgui/examples/libs/emscripten/emscripten_mainloop_stub.h"
#endif

int main()
{
    AppSettings settings;
    settings.title = "Traj3D";
    settings.v_width = 1400;
    settings.v_height = 900;
    settings.log_file = "config.ini";
    settings.font_path = "fonts/SF-Pro.ttf";
    settings.font_size = 17.0;
    settings.asset_path = "assets/";
    settings.show_demo = false;
    settings.restore_previous_dimensions = false;

    Application app = Application(settings);
    app.run();
}
