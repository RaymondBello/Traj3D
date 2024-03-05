
#include "Renderer.h"

#include "OpenGL/OpenGLShader.h"


void Renderer::BeginScene(OrthographicCamera &camera)
{
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

// void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform)
void Renderer::Submit(const Shader &shader, const VertexArray &vertexArray, const glm::mat4 &transform)
{
    shader.Bind();

    // std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    ((OpenGLShader *)&shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

    // std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
    ((OpenGLShader *)&shader)->UploadUniformMat4("u_Transform", transform);

    vertexArray.Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
