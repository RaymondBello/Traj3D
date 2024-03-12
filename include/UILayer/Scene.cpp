#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "hello_imgui/hello_imgui_include_opengl.h"


#include "Scene.h"

Scene::Scene(/* args */)
{
    // GLfloat cubeVertices[] = {
    //     // front
    //     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // 0 (red)
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f,  // 1 (orange)
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,   // 2 (yellow)
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // 3 (green)

    //     // top
    //     -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 4 (blue)
    //     0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // 5 (indigo)
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,   // 6 (violet)
    //     -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,  // 7 (gray)

    //     // left
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // 8 (cyan)
    //     -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.5f,  // 9 (pink)
    //     -0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 0.5f,   // 10 (light green)
    //     -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 1.0f,  // 11 (light blue)

    //     // right
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.5f, // 12 (dark pink)
    //     0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  // 13 (light yellow)
    //     0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // 14 (dark purple)
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.0f,  // 15 (orange yellow)

    //     // back
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 1.0f, // 16 (light blue)
    //     0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  // 17 (yellow green)
    //     0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 0.0f,   // 18 (dark green)
    //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.5f,  // 19 (dark pink)

    //     // bottom
    //     -0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f, // 20
    //     0.5f, -0.5f, 0.5f, 0.3f, 0.3f, 0.3f,  // 21
    //     0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f, // 22
    //     -0.5f, -0.5f, -0.5f, 0.3f, 0.3f, 0.3f // 23
    // };

    // GLuint cubeVertexIndices[] = {
    //     // front
    //     0, 1, 2, // first triangle
    //     2, 3, 0, // second triangle

    //     // top
    //     4, 5, 6, // first triangle
    //     6, 7, 4, // second triangle

    //     // left
    //     8, 9, 10,  // first triangle
    //     10, 11, 8, // second triangle

    //     // right
    //     14, 13, 12, // 12, 13, 14, // first triangle
    //     12, 15, 14, // 14, 15, 12, // second triangle

    //     // back
    //     18, 17, 16, // 16, 17, 18, // first triangle
    //     16, 19, 18, // 18, 19, 16, // second triangle

    //     // bottom
    //     20, 21, 22, // first triangle
    //     22, 23, 20  // second triangle
    // };

    for (int i = 0; i < 1; i++)
    {
        auto entity = m_Registry.create();

        auto &tag = m_Registry.emplace<TagComponent>(entity);
        tag.tag = "Entity " + std::to_string(i);

        m_Registry.emplace<TransformComponent>(entity, glm::vec3(0.0f, 0.01f*i, -2.0f), glm::vec3(10.0f*i, 20.0f*i, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    }

    // Create entities in the scene


}

Scene::~Scene()
{
}

entt::entity Scene::CreateEntity()
{
    return m_Registry.create();
}