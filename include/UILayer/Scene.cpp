#include "hello_imgui/hello_imgui.h"
#include "Scene.h"

Scene::Scene(/* args */)
{

    for (int i = 0; i < 3; i++)
    {
        auto entity = m_Registry.create();

        auto &tag = m_Registry.emplace<TagComponent>(entity);
        tag.tag = "Entity " + std::to_string(i);

        m_Registry.emplace<TransformComponent>(entity, glm::vec3(0.0f, 0.01f*i, -2.0f), glm::vec3(10.0f*i, 20.0f*i, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    }

}

Scene::~Scene()
{
}

entt::entity Scene::CreateEntity()
{
    return m_Registry.create();
}