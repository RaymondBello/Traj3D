#include "VertexArray.h"
#include "Renderer.h"

#include "OpenGL/OpenGLVertexArray.h"

VertexArray *VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
        HelloImGui::Log(HelloImGui::LogLevel::Error, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return new OpenGLVertexArray();
    }

    HelloImGui::Log(HelloImGui::LogLevel::Error, "Unknown RendererAPI!");
    return nullptr;
}
