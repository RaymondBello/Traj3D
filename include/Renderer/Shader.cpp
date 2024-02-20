
#include "Shader.h"

#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"

Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
        // HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return new OpenGLShader(vertexSrc, fragmentSrc);
    }

    HelloImGui::Log(HelloImGui::LogLevel::Error, "Unknown RendererAPI!");

    return nullptr;
}