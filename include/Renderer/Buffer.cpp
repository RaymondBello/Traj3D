#include "Buffer.h"
#include "Renderer.h"

#include "OpenGL/OpenGLBuffer.h"

VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
        HelloImGui::Log(HelloImGui::LogLevel::Error, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
    }

    HelloImGui::Log(HelloImGui::LogLevel::Error, "Unknown RendererAPI!");
    return nullptr;
}

IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
        HelloImGui::Log(HelloImGui::LogLevel::Error, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return new OpenGLIndexBuffer(indices, size);
    }

    HelloImGui::Log(HelloImGui::LogLevel::Error, "Unknown RendererAPI!");

    return nullptr;
}
