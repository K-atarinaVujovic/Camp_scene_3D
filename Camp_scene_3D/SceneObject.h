#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "model.h"

class SceneObject
{
public:
    glm::vec3 Position, Size;
    float Velocity; // technically just speed :D
    glm::vec3 Rotation;
    bool IsSolid;
    bool Destroyed;
    Model& ObjectModel;
    //SceneObject();
    SceneObject(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Model& m, float velocity = 0);
    virtual void Draw(Shader& shader);

    /*glm::vec2 Position, Size;
    float Velocity;
    glm::vec4 Color;
    float Rotation;
    bool IsSolid;
    bool Destroyed;
    Texture Sprite;
    SceneObject();
    SceneObject(glm::vec2 pos, glm::vec2 size, Texture sprite, float velocity = 0, glm::vec4 color = glm::vec4(1.0f));
    virtual void Draw(SpriteRenderer& renderer);*/
};

#endif