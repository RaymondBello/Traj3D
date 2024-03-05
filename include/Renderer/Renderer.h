#pragma once

#include "RenderCommand.h"

// #include "PerspectiveCamera.h"
#include "OrthographicCamera.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer(RendererAPI::API api) : s_SceneData(new SceneData()), s_API(api) {}
    Renderer() : s_SceneData(new SceneData()), s_API(RendererAPI::API::OpenGL) {}
    ~Renderer() { delete s_SceneData; }

    void BeginScene();
    void BeginScene(OrthographicCamera &camera);
    void EndScene();
    void Submit(const Shader &shader, const VertexArray &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    SceneData *s_SceneData;
    RendererAPI::API s_API;
};