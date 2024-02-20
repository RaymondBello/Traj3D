#pragma once

#include "Renderer/Shader.h"
#include <lib/glm/glm.hpp>

#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "hello_imgui/internal/whereami/whereami_cpp.h"
#include "hello_imgui/hello_imgui_include_opengl.h"

class OpenGLShader : public Shader
{
public:
    OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
    virtual ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    void UploadUniformInt(const std::string &name, int value);

    void UploadUniformFloat(const std::string &name, float value);
    void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);
    void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);
    void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

    void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
    void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

private:
    uint32_t m_RendererID;
};