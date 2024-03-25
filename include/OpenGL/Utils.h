#pragma once
#include <fstream>

#include "hello_imgui/hello_imgui.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "hello_imgui/internal/whereami/whereami_cpp.h"
#include "hello_imgui/hello_imgui_include_opengl.h"

enum class ObjectType
{
    NONE = 0,
    // Cameras
    PERSPECTIVE_CAMERA,
    ORTHOGRAPHIC_CAMERA,
    // Light
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT,
    POINT_LIGHT,
    // Model
    MODEL,
    // Geometry
    CUBE,
    SPHERE,
    CUBE_MAP,
    // Simulation
    SIMULATION
};

const std::unordered_map<ObjectType, std::string> ObjectTypeStringMap = {
    {ObjectType::PERSPECTIVE_CAMERA, "Perspective Camera"},
    {ObjectType::ORTHOGRAPHIC_CAMERA, "Orthographic Camera"},
    {ObjectType::DIRECTIONAL_LIGHT, "Directional Light"},
    {ObjectType::SPOT_LIGHT, "Spot Light"},
    {ObjectType::POINT_LIGHT, "Point Light"},
    {ObjectType::MODEL, "Model"},
    {ObjectType::CUBE, "Cube"},
    {ObjectType::SPHERE, "Sphere"},
    {ObjectType::CUBE_MAP, "Cube Map"},
    {ObjectType::SIMULATION, "Simulation"}
};


enum class ShaderDataType
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4 * 4;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    case ShaderDataType::Bool:
        return 1;
    case ShaderDataType::None:
        return -1;
    }

    return 0;
}

struct BufferElement
{
    std::string Name;
    ShaderDataType Type;
    uint32_t Size;
    uint32_t Offset;
    bool Normalized;

    BufferElement() {}

    BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
        : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
    {
    }

    uint32_t GetComponentCount() const
    {
        switch (Type)
        {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Mat3:
            return 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4;
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Bool:
            return 1;
        case ShaderDataType::None:
            return -1;
        }

        return 0;
    }
};

class BufferLayout
{
public:
    BufferLayout() {}

    BufferLayout(const std::initializer_list<BufferElement> &elements)
        : m_Elements(elements)
    {
        CalculateOffsetsAndStride();
    }

    inline uint32_t GetStride() const { return m_Stride; }
    inline const std::vector<BufferElement> &GetElements() const { return m_Elements; }

    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
    void CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto &element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

private:
    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride = 0;
};

static std::string getAssetsFolder() 
{
#ifndef __EMSCRIPTEN__
    return "assets/";
#else
    return "/";
#endif
}

static std::string getShaderSrc(std::string file)
{
    // Open a file and read the content into a char *
    std::string content;
    std::ifstream fileStream(file, std::ios::in);

    if (!fileStream.is_open())
    {
        HelloImGui::Log(HelloImGui::LogLevel::Error, "Could not read file: %s\n", file.c_str());
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();

    std::string filename = file.substr(file.find_last_of("/") + 1);
    HelloImGui::Log(HelloImGui::LogLevel::Debug, "Loaded shader: %s\n", filename.c_str());

    return content;
}

#define vShdrSrc(name) getShaderSrc(getAssetsFolder() + "shaders/" #name ".vert")
#define fShdrSrc(name) getShaderSrc(getAssetsFolder() + "shaders/" #name ".frag")
