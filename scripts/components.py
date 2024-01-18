from dataclasses import dataclass as component
import numpy as np
import numpy.typing as nt
import trimesh

from ui_viewport import Viewport
from imgui_bundle import hello_imgui, icons_fontawesome, imgui, immapp
from imgui_bundle.demos_python import demo_utils


###################################
######### Entity Components ########
###################################
class MeshRenderer:
    pass


class MeshFilter:
    def __init__(self, mesh: trimesh.base.Trimesh):
        self.mesh = mesh


class Transform:
    def __init__(
        self,
        position_xyz: list = np.zeros((3)),
        rotation_xyz: list = np.zeros((3)),
        scale_xyz: list = np.zeros((3)),
    ):
        self.position_xyz = position_xyz
        self.rotation_xyz = rotation_xyz
        self.scale_xyz = scale_xyz


class RigidBody:
    def __init__(
        self,
        collisions: bool = False,
        has_collided: bool = False,
        mass: float = 10,
        position: list = np.zeros((3)),
        velocity: list = np.zeros((3)),
        rotation: list = np.zeros((3)),
    ):
        self.collisions = collisions
        self.has_collided = has_collided
        self.mass = mass
        self.position = position
        self.velocity = velocity
        self.rotation = rotation


class RenderObject:
    def __init__(
        self,
        image: float = None,
        text: str = None,
        mesh: trimesh.base.Trimesh = None,
        instance: any = None,
        view: Viewport = None,
        color: tuple = (192, 192, 192, 255),
        scale: tuple = (1, 1, 1),
    ):
        self.image = image
        self.text = text
        self.mesh = mesh
        self.instance = instance
        self.view = view
        self.color = color
        self.scale = scale


###################################
######### UI Components ########
###################################


class ParameterSettings:
    # Initial Conditions
    init_sim_duration_sec: int = 100
    init_sim_steptime_sec: float = 0.01
    init_sim_pos_start_xyz: list = np.zeros((3))
    init_sim_pos_end_xyz: list = np.zeros((3))
    init_rocket_drymass_kg: float = 1000
    init_rocket_propmass_kg: float = 500


class ParameterUIState:
    is_solving: bool
    is_running: bool
    is_paused: bool
    is_stopped: bool
    loading_progress: float
    status_message: str
    settings: ParameterSettings

    def __init__(self):
        self.is_running = True
        self.is_solving = False
        self.is_paused = False
        self.is_stopped = False
        self.loading_progress = 0.0
        self.status_message = "[]"
        self.settings = ParameterSettings()


class InspectorSettings:
    transform: 1


class HierarchySettings:
    pass


class ParameterSettings:
    pass


class ChartSettings:
    pass
