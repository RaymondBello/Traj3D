#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "hello_imgui/hello_imgui_include_opengl.h"

#include "Scene.h"
#include "Entity.h"

Scene::Scene(/* args */)
{
    HelloImGui::Log(HelloImGui::LogLevel::Info, "Scene created");
}

Scene::~Scene()
{
}

Entity Scene::CreateEntity(std::string name)
{
    // Create entity
    Entity entity = {m_Registry.create(), this};

    // Add mandatory components
    entity.AddComponent<TagComponent>(name);
    entity.AddComponent<TransformComponent>();

    return entity;
}

Entity Scene::AddObject(ObjectType type)
{
    Entity newEntity;

    switch (type)
    {
        case ObjectType::CUBE:
        {
            newEntity = CreateEntity("New Cube");
            auto shader = Shader{
                "Default Shader",
                new OpenGLShader(vShdrSrc(default), fShdrSrc(default))};
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float3, "a_Color"}};
            auto meshComponent = MeshComponent(shader, cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices), layout);

            newEntity.AddComponent<MeshComponent>(meshComponent);
            
            break;
        }

        default:
            HelloImGui::Log(HelloImGui::LogLevel::Error, "Could not create object");
            break;
    }

    return newEntity;
}

void Scene::BeginScene()
{
    // Create entities
    auto entity = CreateEntity("Cube");
    auto shader = Shader{
        "Default Shader",
        new OpenGLShader(vShdrSrc(default), fShdrSrc(default))};
    BufferLayout layout = {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float3, "a_Color"}};
    auto meshComponent = MeshComponent(shader, cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices), layout);

    entity.AddComponent<MeshComponent>(meshComponent);
    entity.GetComponent<TransformComponent>().position = {0.5f, 0.5f, 0.5f};
}
