#pragma once

#include "RendererAPI.h"

class RenderCommand
{
public:
    inline static void SetClearColor(const glm::vec4 &color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    inline static void SetViewport(int x_0, int y_0, int x_1, int y_1)
    {
        s_RendererAPI->SetViewport(x_0, y_0, (GLsizei)x_1, (GLsizei)y_1);
    }

    inline static void Clear()
    {
        s_RendererAPI->Clear();
    }

    inline static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
    {
        s_RendererAPI->DrawIndexed(vertexArray);
    }

private:
    static RendererAPI *s_RendererAPI;
};