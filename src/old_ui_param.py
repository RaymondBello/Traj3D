import dearpygui.dearpygui as dpg


class ParameterUI(object):
    def __init__(self, opts, params=None):
        print("ui_param constructor")
        self.opts = opts
        self.params = params

        self.initialize(show_demo=self.opts["show_demo"])

    def initialize(self, show_demo: bool):
        self.context = dpg.create_context()
        self.viewport = dpg.create_viewport(
            title=self.opts["title"],
            width=self.opts["v_width"],
            height=self.opts["v_height"],
        )

        if show_demo:
            import dearpygui.demo as demo

            demo.show_demo()

        dpg.setup_dearpygui()

    def create_window(self, params):
        "Create a window and menubar"
        self.params = params

        with dpg.window(
            label=self.opts["title"],
            width=self.opts["v_width"],
            height=self.opts["v_height"],
            no_title_bar=self.opts["no_title_bar"],
            pos=(0, 0),
            tag="__app_id",
            menubar=self.opts["menubar"],
        ):
            with dpg.menu_bar():
                dpg.add_menu_item(label="Save")
                dpg.add_menu_item(label="Reset")

            with dpg.group(horizontal=True, horizontal_spacing=20):
                dpg.add_button(label="Start")
                dpg.add_button(label="Stop")
                dpg.add_text("Status: []")

            with dpg.group(horizontal=True):
                with dpg.tab_bar():
                    with dpg.tab(label="Parameters"):
                        self.create_all_params()
                    with dpg.tab(label="Control & Guidance"):
                        dpg.add_button(label="Header 2")
                    with dpg.tab(label="Data Visualization"):
                        dpg.add_button(label="Header 3")

        dpg.show_viewport()

    def ui_update(self, sender, app_data, user_data):
        print(f"sender: {sender}, \t app_data: {app_data}, \t user_data: {user_data}")

    def create_all_params(self):
        """Create parameter fields"""

        def add_param(sect, item):
            if self.params[sect][item]["size"] == 1:
                self.params[sect][item]["tag"] = dpg.add_slider_float(
                    label=self.params[sect][item]["tip"],
                    default_value=self.params[sect][item]["value"][0],
                    min_value=self.params[sect][item]["minmax"][0],
                    max_value=self.params[sect][item]["minmax"][1],
                    callback=self.ui_update,
                    format=f"%.4f {self.params[sect][item]['unit']}",
                )

            if self.params[sect][item]["size"] == 3:
                self.params[sect][item]["tag"] = dpg.add_drag_floatx(
                    size=3,
                    label=self.params[sect][item]["tip"],
                    default_value=self.params[sect][item]["value"],
                    min_value=self.params[sect][item]["minmax"][0],
                    max_value=self.params[sect][item]["minmax"][1],
                    callback=self.ui_update,
                    format=f"%.4f {self.params[sect][item]['unit']}",
                )

            print(f"[INFO] Parameter added {sect}.{item}")
            # print(self.params[sect][item])

        def add_param_section(section):
            dpg.add_text(section)
            for p in self.params[section]:
                add_param(section, p)

        for key in self.params:
            if key == "Initial Conditions":
                add_param_section(key)
