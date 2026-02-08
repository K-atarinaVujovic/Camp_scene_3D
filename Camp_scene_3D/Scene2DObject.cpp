#include "Scene2DObject.h"

Scene2DObject::Scene2DObject()
    : Position(0.0f, 0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) {
}

Scene2DObject::Scene2DObject(glm::vec3 pos, glm::vec2 size, BasicTexture sprite, float velocity, glm::vec4 color)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) {
    std::cout << "Object created!" << std::endl;
}

void Scene2DObject::Draw(SpriteRenderer& renderer)
{
    /*renderer.DrawSprite(
        Sprite,
        camera.GetViewMatrix(),
        camera.GetProjectionMatrix(),
        flame->Position,
        flame->Size,
        flame->Rotation,
        flame->Color
    );*/
    //renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
