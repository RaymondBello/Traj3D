#pragma once

struct CameraComponent
{
    // Constants (make const?)
    float ROTATION_SPEED  = 2.0f;
    const glm::vec3 RIGHT       = {1.0f, 0.0f, 0.0f};
    const glm::vec3 UP          = {0.0f, 1.0f, 0.0f};
    const glm::vec3 FORWARD     = {0.0f, 0.0f, -1.0f};

    // Camera Attributes
    float m_aspect;
    float m_fov;
    float m_near;
    float m_far;
    float m_distance = 5.0f;
    glm::vec3 mFocus = {0.0f, 0.0f, 0.0f};

    // Orientation
    float m_pitch = 0.0f;
    float m_yaw = 0.0f;

    // World position and mouse screen coords
    glm::mat4 m_view_mat;
    glm::mat4 m_proj_mat = glm::mat4{1.0f};
    glm::vec3 m_position = {0.0f, 0.0f, 0.0f};

    // Mouse 2d screen coords
    glm::vec2 m_curr_mouse;

};
