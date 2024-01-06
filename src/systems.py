import esper as ecs
from components import *

##########################
######### Systems ########
##########################


class RigidBodySystem(ecs.Processor):
    def process(self, dt):
        for ent, body in ecs.get_component(RigidBody):
            body.position += body.velocity * dt
            # print(body.position.tolist())


class RenderSystem(ecs.Processor):
    def process(self, dt):
        for ent, (rend, body) in ecs.get_components(RenderObject, RigidBody):
            rend.view.update_mesh(
                rend.instance,
                rend.mesh,
                [body.position[0], body.position[1], body.position[2], 0, 0, 0],
            )
            pass
