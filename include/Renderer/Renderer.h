#pragma once

#include "RenderCommand.h"

// #include "PerspectiveCamera.h"
#include "OrthographicCamera.h"
#include "Shader.h"


class Renderer
{
public:
    static void BeginScene();
    static void BeginScene(OrthographicCamera &camera);
    // static void BeginScene(PerspectiveCamera &camera);

    static void EndScene();

    // static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));
    static void Submit(const Shader &shader, const VertexArray &vertexArray, const glm::mat4 &transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData *s_SceneData;
};