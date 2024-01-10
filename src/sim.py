import esper as ecs
import trimesh
from components import *
from systems import *

from ui_params import ParameterUI
from ui_viewport import ViewportUI


class Simulator(object):
    def __init__(self, view: ViewportUI, params: ParameterUI):
        print("sim constructor")
        self.viewport = view
        self.params = params

        self.entities = {}
        self.initialize()

    def initialize(self):
        # Create Entities
        self.entities["rocket0"] = ecs.create_entity(
            RenderObject(
                mesh=trimesh.load(self.params["Assets"]["rocket0"]),
                scale=(0.1, 0.1, 0.1),
                view=self.viewport.view,
            ),
            RigidBody(velocity=np.array([0, 5, 50])),
        )
        # self.entities["rocket1"] = ecs.create_entity(
        #     Velocity(0, 5, 0),
        #     Position(5, 50, 0),
        #     RenderObject(
        #         mesh=trimesh.load(self.params["Assets"]["rocket1"]),
        #         scale=(0.1, 0.1, 0.1),
        #     ),
        # )
        print(f"[INFO] entities: {self.entities}")

        # Iterate over all RenderObjects and add to viewport scene
        for ent, (rend, body) in ecs.get_components(RenderObject, RigidBody):
            if rend.mesh:
                rend.instance = rend.view.add_mesh(
                    rend.mesh,
                    rend.color,
                    pos=[0, 0, 0],
                )
                rend.view.update_mesh(
                    rend.instance,
                    rend.mesh,
                    [
                        body.position[0] / rend.scale[0],
                        body.position[1] / rend.scale[1],
                        body.position[2] / rend.scale[2],
                        0,
                        0,
                        0,
                    ],
                )

                rend.instance.scale(rend.scale[0], rend.scale[1], rend.scale[2])
                print(
                    f"[INFO] entity: {ent}, bounding_box: {rend.mesh.bounding_box.extents}"
                )

        # Create Systems
        ecs.add_processor(RigidBodySystem())
        ecs.add_processor(RenderSystem())

    def process(self, timeElapsedS):
        ecs.process(timeElapsedS)
