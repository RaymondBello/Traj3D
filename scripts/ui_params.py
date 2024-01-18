from enum import Enum
import time
import os, sys
from imgui_bundle import (
    hello_imgui,
    icons_fontawesome,
    imgui,
    immapp,
    implot,
    ImVec2,
    ImVec4,
)
from imgui_bundle.demos_python import demo_utils
from typing import List
import OpenGL.GL as GL
import ctypes

from components import *
from utils import *


class ParameterUI(object):
    def __init__(self, opts, params=None):
        print("ui_param constructor new")
        self.opts = opts
        self.params = params
        # Load application state from parameters
        self.param_state = ParameterUIState()
        self.runner_params = None

        self.buff_size = 1000
        self.mouseX = ScrollingBuffer(self.buff_size)

        self.var = {
            "mouseX": self.mouseX,
            "mouseY": np.array([0 for i in range(self.buff_size)]),
        }

        self.inspector_id_selected = True
        self.inspector_id_input = ""

        self.node_flags = (
            imgui.TreeNodeFlags_.open_on_arrow.value
            | imgui.TreeNodeFlags_.open_on_double_click.value
            | imgui.TreeNodeFlags_.span_avail_width.value
        )
        self.node_selection_mask = 1 << 0

        self.initialize(show_demo=self.opts["show_demo"])

    def initialize(self, show_demo: bool):
        # Load assets
        self.asset_folder = self.opts["asset_folder"]
        hello_imgui.set_assets_folder(self.asset_folder)
        print(f"[INFO] loaded asset folder: {self.asset_folder}")

        self.runner_params = hello_imgui.RunnerParams()
        self.runner_params.app_window_params.window_title = self.opts["title"]
        self.runner_params.imgui_window_params.menu_app_title = self.opts["menu_title"]
        self.runner_params.app_window_params.window_geometry.size = (
            int(self.opts["v_width"]),
            int(self.opts["v_height"]),
        )
        self.runner_params.app_window_params.restore_previous_geometry = True

        # Add fonts
        self.runner_params.callbacks.load_additional_fonts = lambda: self.load_fonts(
            self.opts["font"], self.opts["font_size"]
        )
        # self.load_fonts(self.opts["font"], self.opts["font_size"])

        # self.runner_params.callbacks.post_init = lambda: self.init_3d_resources()
        # self.runner_params.callbacks.before_exit = lambda: self.destroy_3d_resources()

        # Configure status bar
        self.runner_params.imgui_window_params.show_status_bar = True
        self.runner_params.callbacks.show_status = lambda: self.status_bar

        # Configure Menu
        self.runner_params.imgui_window_params.show_menu_bar = True
        self.runner_params.imgui_window_params.show_menu_app = True
        self.runner_params.imgui_window_params.show_menu_view = True
        # self.runner_params.callbacks.show_menus = lambda: self.show_menu_gui(runner_params)
        self.runner_params.callbacks.show_app_menu_items = self.show_menu

        # Load User Settings TODO
        # self.runner_params.callbacks.post_init = lambda: load_settings(app_state)
        # self.runner_params.callbacks.before_exit = lambda: save_settings(app_state)

        # Create the application layout
        self.runner_params.imgui_window_params.default_imgui_window_type = (
            hello_imgui.DefaultImGuiWindowType.provide_full_screen_dock_space
            # hello_imgui.DefaultImGuiWindowType.no_default_window
        )
        self.runner_params.imgui_window_params.enable_viewports = True
        self.runner_params.docking_params = self.create_layout(self.param_state)
        # Add alternative layouts TODO
        # runner_params.alternative_docking_layouts = create_alternative_layouts(app_state)

        # Determine setting save location
        self.runner_params.ini_folder_type = hello_imgui.IniFolderType.current_folder
        self.runner_params.ini_filename = self.opts["log_file"]

        # custom_background is called every frame, and is used to display the custom background
        # self.runner_params.callbacks.custom_background = lambda: self.viewport_render

        # Initialize plots
        implot.create_context()

    def init_3d_resources(self):
        self.full_screen_quad_vao = self.create_full_screen_quad_vao()

    def destroy_3d_resources(self):
        GL.glDeleteVertexArrays(1, [self.full_screen_quad_vao])

    def create_full_screen_quad_vao(self):
        
        
        
        return 10
        
        

    def start_event_loop(self):
        # hello_imgui.run(self.runner_params)

        add_ons_params = immapp.AddOnsParams()
        add_ons_params.with_markdown = True
        immapp.run(self.runner_params, add_ons_params)

    def create_docking_splits(self):
        #    _____________________________________________
        #    |          |                      |          |
        #    | Inspector|                      | Entity   |
        #    |          |    MainDockSpace     |          |
        #    |          |                      |          |
        #    |          |                      |          |
        #    |          |                      |          |
        #    |          |----------------------|----------|
        #    |          |  Logs                           |
        #    ---------------------------------------------|
        # Use to always set this layout
        self.runner_params.docking_params.layout_condition = (
            hello_imgui.DockingLayoutCondition.application_start
        )

        # Inspector
        inspector_split = hello_imgui.DockingSplit()
        inspector_split.initial_dock = "MainDockSpace"
        inspector_split.new_dock = "Inspector"
        inspector_split.direction = imgui.Dir_.left
        inspector_split.ratio = 0.25

        # Logs
        logs_split = hello_imgui.DockingSplit()
        logs_split.initial_dock = "MainDockSpace"
        logs_split.new_dock = "Logs"
        logs_split.direction = imgui.Dir_.down
        logs_split.ratio = 0.25

        # Scene Nodes
        scene_split = hello_imgui.DockingSplit()
        scene_split.initial_dock = "MainDockSpace"
        scene_split.new_dock = "Scene"
        scene_split.direction = imgui.Dir_.right
        scene_split.ratio = 0.3

        return [inspector_split, logs_split, scene_split]

    def create_inspector(self, state: ParameterUIState):
        imgui.push_font(self.font)
        _, self.inspector_id_selected = imgui.checkbox("##", self.inspector_id_selected)
        imgui.same_line()
        imgui.push_item_width(-0.1)
        _, self.inspector_id_input = imgui.input_text(
            "|",
            self.inspector_id_input,
            flags=imgui.InputTextFlags_.chars_no_blank.value,
        )

        imgui.separator()

        # First collapsible header
        if imgui.collapsing_header(
            "Transform", imgui.TreeNodeFlags_.default_open.value
        ):
            # Display hover state and some content within the header
            imgui.text(f"IsItemHovered: {int(imgui.is_item_hovered())}")

        if imgui.collapsing_header("Mesh"):
            # Display hover state and more content within the second header
            imgui.text(f"IsItemHovered: {int(imgui.is_item_hovered())}")

        if imgui.collapsing_header("Rigid Body"):
            # Display hover state and more content within the second header
            imgui.text(f"IsItemHovered: {int(imgui.is_item_hovered())}")

        if imgui.collapsing_header("Mesh Renderer"):
            # Display hover state and more content within the second header
            imgui.text(f"IsItemHovered: {int(imgui.is_item_hovered())}")

        imgui.pop_font()

    def create_sceneview(self):
        imgui.push_font(self.font)
        imgui.text("Scene Framebuffer")

        scene_w = imgui.get_content_region_avail().x
        scene_h = imgui.get_content_region_avail().y
        
        # hello_imgui.log(hello_imgui.LogLevel.info, f"sceneview dimensions {scene_w, scene_h}")
        
        
        
        
        
        # Start the Dear ImGui frame
        # imgui.backends.opengl3_new_frame()
        imgui.pop_font()

    def create_plots(self):
        # Show demo
        if self.opts["show_demo"]:
            imgui.show_demo_window()

        imgui.push_font(self.font)
        imgui.text("Plots")
        imgui.pop_font()

        t = 0.0
        t += imgui.get_io().delta_time
        framerate = 1 / t

        self.mouseX.add_point(framerate, imgui.get_mouse_pos().x)

        if implot.begin_plot("FPS", imgui.ImVec2(-1, 250)):
            implot.setup_axes("Time", "Framerate")
            # implot.setup_axis_limits(implot.ImAxis_.x1.value, )
            implot.plot_line("FPS", self.mouseX.data[0, :])
            implot.end_plot()

    def create_scene_nodes(self):
        imgui.push_font(self.font)

        # 'selection_mask' is a simple representation of what may be the user-side selection state.
        # 'node_clicked' is temporary storage of what node we have clicked to process selection at the end of the loop.
        node_clicked = -1
        for i in range(6):
            # Set node flags based on the selection state.
            node_flags = self.node_flags
            is_selected = (self.node_selection_mask & (1 << i)) != 0
            if is_selected:
                node_flags |= imgui.TreeNodeFlags_.selected
            if i < 3:
                # Items 0..2 are Tree Nodes.
                node_open = imgui.tree_node_ex(str(i), node_flags, f"Entity {i}")
                if imgui.is_item_clicked() and not imgui.is_item_toggled_open():
                    node_clicked = i
                if node_open:
                    imgui.text("uuid: c742b4b1")
                    imgui.tree_pop()

            else:
                # Items 3..5 are Tree Leaves.
                node_flags |= (
                    imgui.TreeNodeFlags_.leaf.value
                    | imgui.TreeNodeFlags_.no_tree_push_on_open.value
                )
                imgui.tree_node_ex(str(i), node_flags, f"Entity {i}")
                if imgui.is_item_clicked() and not imgui.is_item_toggled_open():
                    node_clicked = i

        # Update selection state outside of the tree loop
        if node_clicked != -1:
            if imgui.get_io().key_ctrl:
                self.node_selection_mask ^= 1 << node_clicked  # CTRL+click to toggle
            else:
                self.node_selection_mask = 1 << node_clicked  # Click to single-select

        imgui.pop_font()

    def create_dockable_windows(self, state: ParameterUIState):
        # Inspector

        inspector = hello_imgui.DockableWindow()
        inspector.label = f" {icons_fontawesome.ICON_FA_SEARCH} Inspector"
        inspector.dock_space_name = "Inspector"
        inspector.gui_function = lambda: self.create_inspector(state)

        # Editor
        flight_plots = hello_imgui.DockableWindow()
        flight_plots.label = f" {icons_fontawesome.ICON_FA_IMAGE} Flight Plots"
        flight_plots.dock_space_name = "MainDockSpace"
        flight_plots.gui_function = self.create_plots

        # Scene View
        scene_view = hello_imgui.DockableWindow()
        scene_view.label = f" {icons_fontawesome.ICON_FA_IMAGE} Scene"
        scene_view.dock_space_name = "MainDockSpace"
        scene_view.gui_function = self.create_sceneview

        # Logger
        logs = hello_imgui.DockableWindow()
        logs.label = f" {icons_fontawesome.ICON_FA_TERMINAL} Console"
        logs.dock_space_name = "Logs"
        logs.gui_function = hello_imgui.log_gui

        # Scene Node Graph
        scene_hier = hello_imgui.DockableWindow()
        scene_hier.label = f" {icons_fontawesome.ICON_FA_SITEMAP} Scene Hierarchy"
        scene_hier.dock_space_name = "Scene"
        scene_hier.gui_function = self.create_scene_nodes

        # Imgui Demo
        # if self.opts["show_demo"]:
        #     demo = hello_imgui.DockableWindow()
        #     scene.label = "Demo"
        #     scene.dock_space_name = "Inspector"
        #     scene.gui_function = imgui.show_demo_window

        dockable_windows = [
            inspector,
            flight_plots,
            scene_view,
            logs,
            scene_hier,
        ]
        return dockable_windows

    def create_layout(self, state: ParameterUIState):
        docking_params = hello_imgui.DockingParams()

        # By default, the layout name is already "Default"
        # docking_params.layout_name = "Default"
        docking_params.docking_splits = self.create_docking_splits()
        docking_params.dockable_windows = self.create_dockable_windows(state)
        return docking_params

    def show_menu(self):
        clicked, _ = imgui.menu_item("Reset", "", False)
        if clicked:
            hello_imgui.log(hello_imgui.LogLevel.info, "selected on reset")

        demo_toggle, _ = imgui.menu_item("Show Demo", "", False)
        if demo_toggle:
            self.opts["show_demo"] = not self.opts["show_demo"]

    def load_fonts(self, font, size):
        # Load Fonts
        hello_imgui.imgui_default_settings.load_default_font_with_font_awesome_icons()

        self.font = hello_imgui.load_font_ttf(font, size)
        hello_imgui.log(hello_imgui.LogLevel.info, f"loaded font {self.font}")

    def status_bar(self):
        if self.param_state.is_solving == True:
            imgui.text(f"[SOLVING] {self.param_state.status_message}")
            imgui.same_line()
            imgui.progress_bar(
                self.param_state.loading_progress, hello_imgui.em_to_vec2(7.0, 1.0)
            )
        elif self.param_state.is_running == True:
            imgui.text(f"[RUNNING] {self.param_state.status_message}")
        elif self.param_state.is_paused == True:
            imgui.text(f"[PAUSED] {self.param_state.status_message}")
        elif self.param_state.is_stopped == True:
            imgui.text(f"[STOPPED] {self.param_state.status_message}")
