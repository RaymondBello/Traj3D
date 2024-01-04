import numpy as np
import pyqtgraph as pg
import pyqtgraph.opengl as gl
import trimesh

from pyqtgraph import functions as fn
from pyqtgraph.Qt import QtCore, QtGui
from PyQt5 import QtWidgets, QtCore, QtGui


class Viewport(object):
    def __init__(self):
        """Create a GL View Widget"""
        self.viewer = gl.GLViewWidget()

    def set_bg_color(self, color: tuple = (0, 0, 0, 1)):
        self.viewer.setBackgroundColor(
            QtGui.QColor(
                int(color[0] * 255),
                int(color[1] * 255),
                int(color[2] * 255),
                int(color[3] * 255),
            )
        )

    def add_text(
        self,
        text: str = None,
        pos: list = None,
        color: tuple = (255, 255, 255, 255),
        font: QtGui.QFont = QtGui.QFont("Helvetica", 14),
    ):
        """Add text to viewer

        Args:
            text (str): string to be displayed
            pos (list, optional): position of text icon in x, y, z axis (unit is meters). Defaults to None.
            color (tuple, optional): color in terms of RGB or RGBA. Defaults to (255,255,255,255).
            font (QtGui.QFont, optional): font style and size. Defaults to QtGui.QFont('Helvetica', 14).

        Returns:
            gl.GLTextItem: GLTextItem Instance
        """

        text = gl.GLTextItem(text=text, color=color, font=font)
        self.viewer.addItem(text)
        if pos is not None:
            text.setData(pos=pos)
        return text

    def clear_text(self, text: gl.GLTextItem):
        self.viewer.removeItem(text)

    def add_mesh(
        self,
        mesh: trimesh.base.Trimesh,
        color: tuple = (255, 255, 255, 255),
        pos: list = None,
    ):
        """_summary_

        Args:
            mesh (trimesh.base.Trimesh): trimesh object
            color (tuple, optional): color in terms of RGB or RGBA. Defaults to (255,255,255,255).
            pos (list, optional): position of mesh in x, y, z axis (unit is meters). Defaults to None.

        Returns:
            gl.GLMeshItem: GLMeshItem Instance
        """
        mesh_item = gl.GLMeshItem(
            vertexes=mesh.vertices,
            faces=mesh.faces,
            smooth=False,
            drawEdges=False,
            edgeColor=(0, 0, 0, 1),
            color=color,
            pos=pos,
        )
        # mesh_item.setShader("edgeHilight")
        mesh_item.setShader("shaded")

        self.viewer.addItem(mesh_item)

        return mesh_item

    def clear_mesh(self, mesh: gl.GLMeshItem):
        """Remove mesh from viewer

        Args:
            mesh (gl.GLMeshItem): mesh to be removed
        """
        self.viewer.removeItem(mesh)

    def update_mesh(
        self, mesh_item: gl.GLMeshItem, mesh: trimesh.base.Trimesh, pos: list = None
    ):
        """Update mesh location

        Args:
            mesh_item (gl.GLMeshItem): mesh to be updated
            mesh (trimesh.base.Trimesh): new mesh/or the mesh to apply transformation
            pos (list, optional): new location of mesh in x, y, z, r, p, y axis (unit is meters). Defaults to None.

        """

        def compute_transformation_matrix(vertices, location: list):
            T = np.eye(4)
            T[:3, 3] = location[:3]
            T[:3, :3] = trimesh.transformations.euler_matrix(
                location[3], location[4], location[5]
            )[:3, :3]
            transformed_vertices = np.dot(
                T, np.hstack((vertices, np.ones((vertices.shape[0], 1)))).T
            ).T[:, :3]
            return transformed_vertices

        mesh_item.setMeshData(
            vertexes=compute_transformation_matrix(mesh.vertices, pos), faces=mesh.faces
        )

    def add_image(self, image: np.ndarray, pos: list = None):
        """Add image to viewer

        Args:
            image (np.ndarray): image array
            pos (list, optional): position of image in x, y, z axis (unit is meters). Defaults to None.

        Returns:
            gl.GLImageItem: GLImageItem Instance
        """
        image_item = gl.GLImageItem(image=image)
        self.viewer.addItem(image_item)
        if pos is not None:
            image_item.setData(pos=pos)
        return image_item

    def clear_image(self, image: gl.GLImageItem):
        """Remove image from viewer

        Args:
            image (gl.GLImageItem): image to be removed
        """
        self.viewer.removeItem(image)

    def set_camera_angle(self, distance=2, elevation=0, azimuth=0):
        """Set camera angle to view the scene"""

        self.viewer.setCameraPosition(
            distance=distance, elevation=elevation, azimuth=azimuth
        )


class ViewportUI(object):
    def __init__(self, opts, params=None):
        print("ui_viewport constructor")
        self.opts = opts
        self.params = params
        self.view = None
        self.initialize()

    def initialize(self):
        app = pg.mkQApp(self.opts["title"])
        self.view = Viewport()
        self.view.viewer.setFixedWidth(int(self.opts["v_width"]))
        self.view.viewer.setFixedHeight(int(self.opts["v_height"]))
        self.view.viewer.show()
        self.view.viewer.setWindowTitle(self.opts["title"])
        self.view.viewer.setCameraPosition(distance=100, azimuth=30, elevation=30)

        # Initialize grid
        grid_size = QtGui.QVector3D(100, 100, 100)

        gx = gl.GLGridItem(size=grid_size)
        gy = gl.GLGridItem(size=grid_size)
        gz = gl.GLGridItem(size=grid_size, color=(13.3, 54.5, 13.3, 255))
        gx.rotate(90, 0, 1, 0)
        gy.rotate(90, 1, 0, 0)
        gx.translate(-grid_size.x() / 2, 0, grid_size.y() / 2)
        gy.translate(0, -grid_size.y() / 2, grid_size.y() / 2)
        gz.translate(0, 0, 0)

        self.view.viewer.addItem(gx)
        self.view.viewer.addItem(gy)
        self.view.viewer.addItem(gz)

    def add_mesh(self, path: str, color: tuple, pos: list):
        mesh = trimesh.load(path)
        self.params["assets"][path] = {}
        self.params["assets"][path]["mesh"] = mesh
        self.params["assets"][path]["mesh_inst"] = self.viewer.add_mesh(
            mesh, color, pos
        )

    def update_mesh(self):
        pass

    def update_ui(self):
        pass
