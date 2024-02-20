#pragma once

#include "Renderer/RendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
    virtual void SetClearColor(const glm::vec4 &color) override;
    virtual void SetViewport(int x_0, int y_0, int x_1, int y_1) override;
    virtual void Clear() override;

    virtual void DrawIndexed(const VertexArray &vertexArray) override;
};