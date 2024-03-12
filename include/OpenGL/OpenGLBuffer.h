#pragma once

#include "Utils.h"

class OpenGLVertexBuffer
{
public:
    OpenGLVertexBuffer(float *vertices, uint32_t size);
    ~OpenGLVertexBuffer();

    void Bind();
    void Unbind();

    const BufferLayout &GetLayout() const { return m_Layout; }
    void SetLayout(const BufferLayout &layout) { m_Layout = layout; }

private:
    uint32_t m_RendererID;
    BufferLayout m_Layout;
};

class OpenGLIndexBuffer
{
public:
    OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
    ~OpenGLIndexBuffer();

    void Bind();
    void Unbind();

    uint32_t GetCount() const { return m_Count; }

private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};