from dataclasses import dataclass as component
import numpy as np
import numpy.typing as nt
import trimesh

from ui_viewport import Viewport


#############################
######### Components ########
#############################


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
