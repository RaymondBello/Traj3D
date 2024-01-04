from app import *


def main():
    print("_main entry")

    opts = {
        "title": "Flight Trajectory",
        "v_width": 1200,
        "v_height": 900,
        "show_demo": True,
        "no_title_bar": False,
        "menubar": True,
        "update_ms": 50,
        "show_metrics": False
    }

    App = MainApplication(opts)
    App.run()


if __name__ == "__main__":
    main()
