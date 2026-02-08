#ifndef SCENE2DOBJECT_H
#define SCENE2DOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "BasicTexture.h"
#include "SpriteRenderer.h"


class Scene2DObject
{
public:
    glm::vec3 Position;
    glm::vec2 Size;
    float Velocity;
    glm::vec4 Color;
    float Rotation;
    bool IsSolid;
    bool Destroyed;
    BasicTexture Sprite;
    Scene2DObject();
    Scene2DObject(glm::vec3 pos, glm::vec2 size, BasicTexture sprite, float velocity = 0, glm::vec4 color = glm::vec4(1.0f));
    virtual void Draw(SpriteRenderer& renderer);
};

#endif