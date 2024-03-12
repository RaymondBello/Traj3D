#pragma once

#include <memory>
#include "OpenGLBuffer.h"

class OpenGLVertexArray
{
public:
    OpenGLVertexArray();
    ~OpenGLVertexArray();

    void Bind();
    void Unbind();

    void AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer> &vertexBuffer);
    void SetIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer> &indexBuffer);

    const std::vector<std::shared_ptr<OpenGLVertexBuffer>> &GetVertexBuffers() const { return m_VertexBuffers; }
    const std::shared_ptr<OpenGLIndexBuffer> &GetIndexBuffer() const { return m_IndexBuffer; }

private:
    uint32_t m_RendererID;
    std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_VertexBuffers;
    std::shared_ptr<OpenGLIndexBuffer> m_IndexBuffer;
};
