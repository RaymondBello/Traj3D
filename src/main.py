import os
from app import *


def main():
    print("_main entry")

    opts = {
        "title": "Flight Trajectory",
        "menu_title": "File",
        "v_width": 1200,
        "v_height": 900,
        "show_demo": False,
        "no_title_bar": False,
        "menubar": True,
        "log_file": "config.ini",
        "font": "fonts/SF-Pro.ttf",
        "font_size": 18,
        "update_ms": 1,
        "show_metrics": False,
        "show_xyz_grid": [False, False, True],
        "asset_folder": os.path.dirname(__file__).replace("src", "assets"),
    }

    App = MainApplication(opts)
    App.run()


if __name__ == "__main__":
    main()
