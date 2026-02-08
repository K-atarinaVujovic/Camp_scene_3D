#ifndef BIRDOBJECT_H
#define BIRDOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <map>

#include <GLFW/glfw3.h>

#include "SceneObject.h"

struct Bounds {
    float MinX, MaxX;
    float MinY, MaxY;
};

class BirdObject : public SceneObject
{
public:
    //Bounds WalkingArea;

    bool IsJumping = false;
    bool IsBlinking = false;
    bool IsWalking = false;
    bool IsInTent = false;

    //bool FacingRight = false;

    /*std::vector<Texture> LegFrames;
    float legTimer = 0.0f;
    float legInterval = 0.4f;
    int currentLeg = 0;*/

    BirdObject(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Model& model, float velocity = 3.0f);
    /*glm::vec2 MoveUp(float dt, std::vector<SceneObject*>& obstacles);
    glm::vec2 MoveDown(float dt, std::vector<SceneObject*>& obstacles);
    glm::vec2 MoveLeft(float dt, std::vector<SceneObject*>& obstacles);
    glm::vec2 MoveRight(float dt, std::vector<SceneObject*>& obstacles);*/
    void Jump();
    void Update(float dt, std::vector<SceneObject*>& obstacles, bool Keys[]);
    //void Draw(SpriteRenderer& renderer) override;
    //void Blink(); // todo ig

private:
    bool checkCollision(SceneObject& obj, glm::vec3 pos);
};

#endif