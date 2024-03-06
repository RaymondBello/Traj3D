#pragma once

#include <lib/glm/glm.hpp>
#include <lib/glm/gtc/matrix_transform.hpp>

struct TagComponent
{
    TagComponent() : tag{std::string()} 
    {
    };
    
    TagComponent(std::string &tag) : tag{tag} 
    {
    };

    std::string tag;
};


struct TransformComponent
{
    // Default constructor which initializes all members to zero.
    TransformComponent() : position{0.0f, 0.0f, 0.0f}, // initial position
                           rotation{0.0f, 0.0f, 0.0f}, // initial rotation in degrees
                           scale{1.0f, 1.0f, 1.0f}     // initial scale
    {
    }

    // Constructor that allows to set all members.
    TransformComponent(const glm::vec3 &position,
                       const glm::vec3 &rotation,
                       const glm::vec3 &scale) : position{position}, // entity's position
                                                 rotation{rotation}, // entity's rotation in degrees
                                                 scale{scale}        // entity's scale
    {
    }

    // Get the transformation matrix
    glm::mat4 getMatrix()
    {
        auto transformMatrix = glm::mat4(1.0f);
        transformMatrix = glm::translate(transformMatrix, position);
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transformMatrix = glm::scale(transformMatrix, scale);

        return transformMatrix;
    }

    // Position of the entity in 3D space.
    glm::vec3 position;

    // Rotation of the entity in 3D space around each axis in degrees.
    glm::vec3 rotation;

    // Scale of the entity in 3D space.
    glm::vec3 scale;
};



struct CameraComponent
{
    // Constants (make const?)
    float ROTATION_SPEED = 2.0f;
    const glm::vec3 RIGHT = {1.0f, 0.0f, 0.0f};
    const glm::vec3 UP = {0.0f, 1.0f, 0.0f};
    const glm::vec3 FORWARD = {0.0f, 0.0f, -1.0f};

    // Camera Attributes
    float fov = 90.0f;
    float aspect;
    float near;
    float far;
    float distance = 5.0f;
    glm::vec3 mFocus = {0.0f, 0.0f, 0.0f};

    // Orientation
    float pitch = 0.0f;
    float yaw = 0.0f;

    // World position and mouse screen coords
    glm::mat4 view_mat;
    glm::mat4 proj_mat = glm::mat4{1.0f};
    glm::vec3 position = {0.0f, 0.0f, 0.0f};

    // Mouse 2d screen coords
    glm::vec2 curr_mouse;
};

