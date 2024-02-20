#pragma once

#include <lib/glm/glm.hpp>

#include "VertexArray.h"


class RendererAPI
{
public:
    enum class API
    {
        None = 0,
        OpenGL = 1
    };

public:
    virtual void SetClearColor(const glm::vec4 &color) = 0;
    virtual void SetViewport(int x_0, int y_0, int x_1, int y_1) = 0;

    virtual void Clear() = 0;

    virtual void DrawIndexed(const VertexArray &vertexArray) = 0;

    inline static API GetAPI() { return s_API; }

private:
    static API s_API;
};
