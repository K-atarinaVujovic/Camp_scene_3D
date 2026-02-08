#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    // Vectors
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler angles
    float Yaw;
    float Pitch;

    // Settings
    float Fov;
    float Aspect;
    float Near;
    float Far;
    float MouseSensitivity;

    Camera() {}

    Camera(glm::vec3 position, float aspect)
        : Position(position),
        Front(0.0f, 0.0f, -1.0f),
        WorldUp(0.0f, 1.0f, 0.0f),
        Yaw(-90.0f),
        Pitch(-20.0f),
        Fov(45.0f),
        Aspect(aspect),
        Near(0.1f),
        Far(100.0f),
        MouseSensitivity(0.1f)
    {
        updateVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 GetProjectionMatrix()
    {
        return glm::perspective(glm::radians(Fov), Aspect, Near, Far);
    }

    // Keyboard movement
    void MoveForward(float speed)
    {
        Position += Front * speed;
    }

    void MoveRight(float speed)
    {
        Position += Right * speed;
    }

    // Mouse movement
    void ProcessMouse(float xOffset, float yOffset)
    {
        xOffset *= MouseSensitivity;
        yOffset *= MouseSensitivity;

        Yaw += xOffset;
        Pitch += yOffset;

        // Prevent flipping
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;

        updateVectors();
    }

private:
    void updateVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif
