import numpy as np
import pyqtgraph as pg
import pyqtgraph.opengl as gl
from pyqtgraph import functions as fn
from pyqtgraph.Qt import QtCore, QtGui

import dearpygui.dearpygui as dpg
import dearpygui.demo as demo

from ui_viewport import *

# Create a variable dict
variables = {
    "id": 0,
}

dpg.create_context()
dpg.create_viewport(title="Flight Trajectory", width=1200, height=900)

demo.show_demo()

dpg.setup_dearpygui()


def ui_update(sender, app_data, user_data):
    print(f"sender: {sender}, \t app_data: {app_data}, \t user_data: {user_data}")
    print(variables)
    print(f"Got: {dpg.get_value(sender)}")


with dpg.window(
    label="Flight Trajectory",
    width=1200,
    # no_title_bar=True,
    # autosize=True,
    height=900,
    pos=(0, 0),
    tag="__app_id",
    menubar=True,
):
    with dpg.menu_bar():
        dpg.add_menu(label="File")
        dpg.add_menu(label="Options")

    with dpg.group(horizontal=True, horizontal_spacing=20):
        dpg.add_button(label="Start")
        dpg.add_button(label="Stop")
        dpg.add_text("Status: ")

    with dpg.group(horizontal=True):
        with dpg.tab_bar():
            with dpg.tab(label="Parameters"):
                
                dpg.add_text("Initial Conditions")
                variables["start_position"] = dpg.add_drag_floatx(
                    label=f"Position @ t0",
                    min_value=0.0,
                    max_value=100.0,
                    size=3,
                    callback=ui_update,
                )
                print(variables["start_position"])

            with dpg.tab(label="Control & Guidance"):
                dpg.add_button(label="Header 2")
            with dpg.tab(label="Data Visualization"):
                dpg.add_button(label="Header 3")

dpg.show_viewport()


app = pg.mkQApp("Trajectory Viewport")

viewport = Viewport()


# Load mesh and display
mesh1 = trimesh.load("resources/StarShip.stl")
print(mesh1.vertices.shape)
mesh2 = trimesh.load("resources/SuperHeavy_Booster.stl")
print(mesh2.vertices.shape)

booster_length = 142
vehicle_scale = 0.1

mesh_inst = viewport.add_mesh(mesh1, color=(192, 192, 192, 255), pos=[0, 0, 0])
mesh_inst2 = viewport.add_mesh(mesh2, color=(192, 192, 192, 255), pos=[0, 0, 0])

viewport.update_mesh(mesh_inst, mesh1, [0, 0, booster_length, 0, 0, 0])
# viewport.update_mesh(mesh_inst2, mesh2, [0, 0, 0, np.pi / 2, 0, 0])

mesh_inst.scale(vehicle_scale, vehicle_scale, vehicle_scale)
mesh_inst2.scale(vehicle_scale, vehicle_scale, vehicle_scale)

w = viewport.viewer
# w = gl.GLViewWidget()
w.setFixedWidth(900)
w.setFixedHeight(700)
# w.setFixedWidth(100)
# w.setFixedHeight(100)
w.show()

w.setWindowTitle("Trajectory Simulation")
w.setCameraPosition(distance=100, azimuth=30, elevation=30)
# w.setCameraPosition(distance=100, azimuth=0, elevation=0)

grid_size = QtGui.QVector3D(100, 100, 100)

gx = gl.GLGridItem(size=grid_size)
gy = gl.GLGridItem(size=grid_size)
gz = gl.GLGridItem(size=grid_size, color=(13.3, 54.5, 13.3, 255))
gx.rotate(90, 0, 1, 0)
gy.rotate(90, 1, 0, 0)
gx.translate(-grid_size.x() / 2, 0, grid_size.y() / 2)
gy.translate(0, -grid_size.y() / 2, grid_size.y() / 2)
gz.translate(0, 0, 0)

w.addItem(gx)
w.addItem(gy)
w.addItem(gz)

pos = np.empty((10, 3))  # Create an empty array to store the positions of the points
size = np.empty((10))  # Create an empty array to store the sizes of the points
color = np.empty((10, 4))  # Create an empty array to store the colors of the points
pos[0] = (1, 0, 0)  # Set the position of the first point
size[0] = 1  # Set the size of the first point
color[0] = (1.0, 1.0, 1.0, 1)  # Set the color of the first point to white

pos[1] = (0, 0, 0)
size[1] = 5.0
color[1] = (0.0, 0.0, 1.0, 1)  # Set the color of the second point to blue

pos[2] = (0, 0, 0)
size[2] = 5.0
color[2] = (1.0, 0.0, 0.0, 1)  # Set the color of the second point to red


sp1 = gl.GLScatterPlotItem(
    pos=pos, size=size, color=color, pxMode=False
)  # Create a scatter plot item with the specified positions, sizes, and colors
# sp1.translate(0, 0, 0)  # Translate the scatter plot item
w.addItem(sp1)  # Add the scatter plot item to the view widget

index = 0
i = 0
r = 10


def update():  # Define a function to update the plots
    ## update volume colors
    global pos, sp1, index, i, r, w
    x = np.cos(index) * r
    y = np.sin(index) * r

    pos[0] = (x, y, 0)
    pos[1] = (0, y, booster_length * vehicle_scale)
    pos[2] = (0, y, 0)

    viewport.update_mesh(
        mesh_inst, mesh1, [0, y / vehicle_scale, booster_length, 0, 0, 0]
    )
    viewport.update_mesh(mesh_inst2, mesh2, [0, y / vehicle_scale, 0, 0, 0, 0])

    sp1.setData(pos=pos)

    index += 0.1
    i += 1


t = QtCore.QTimer()  # Create a QTimer
t.timeout.connect(update)  # Connect the update function to the timeout signal
t.start(50)  # Start the timer with a timeout of 50 milliseconds


if __name__ == "__main__":  # Check if the script is being run as the main program
    dpg.start_dearpygui()
    dpg.destroy_context()

    pg.exec()  # Start the Qt event loop
