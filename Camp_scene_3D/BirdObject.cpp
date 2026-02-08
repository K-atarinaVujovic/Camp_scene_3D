#include "BirdObject.h"

float JumpVelocity = 0.0f;
float Gravity = -80.0f;
float GroundY = 0.0f;
float JumpStrength = 20.0f;

float blinkTimer = 0.0f;
float blinkDuration = 0.08f;


BirdObject::BirdObject(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Model& model, float velocity)
    : SceneObject(pos, size, rotation, model, velocity) {
    /*LegFrames.push_back(ResourceManager::GetTexture("walking_leg"));
    LegFrames.push_back(ResourceManager::GetTexture("standing_leg"));*/
}

//glm::vec2 BirdObject::MoveUp(float dt, std::vector<SceneObject*>& obstacles) {
//    glm::vec2 newPos = this->Position;
//    newPos.y += this->Velocity * dt;
//
//    if (newPos.y + 20.0f > WalkingArea.MaxY) newPos.y = WalkingArea.MaxY - 20.0f;
//
//    for (auto& obj : obstacles) {
//        if (checkCollision(*obj, newPos)) {
//            return this->Position;
//        }
//    }
//
//    this->Position = newPos;
//    return this->Position;
//}
//
//glm::vec2 BirdObject::MoveDown(float dt, std::vector<SceneObject*>& obstacles) {
//    glm::vec2 newPos = this->Position;
//    newPos.y -= this->Velocity * dt;
//
//    if (newPos.y < WalkingArea.MinY) newPos.y = WalkingArea.MinY;
//
//    for (auto& obj : obstacles) {
//        if (checkCollision(*obj, newPos)) {
//            return this->Position;
//        }
//    }
//
//    this->Position = newPos;
//    return this->Position;
//}
//
//glm::vec2 BirdObject::MoveLeft(float dt, std::vector<SceneObject*>& obstacles) {
//    FacingRight = false;
//    glm::vec2 newPos = this->Position;
//    newPos.x -= this->Velocity * dt;
//
//    if (newPos.x < WalkingArea.MinX) newPos.x = WalkingArea.MinX;
//
//
//    for (auto& obj : obstacles) {
//        if (checkCollision(*obj, newPos)) {
//            return this->Position;
//        }
//    }
//
//    this->Position = newPos;
//    return this->Position;
//}
//
//glm::vec2 BirdObject::MoveRight(float dt, std::vector<SceneObject*>& obstacles) {
//    FacingRight = true;
//    glm::vec2 newPos = this->Position;
//    newPos.x += this->Velocity * dt;
//
//    if (newPos.x + Size.x > WalkingArea.MaxX) newPos.x = WalkingArea.MaxX - Size.x;
//
//    for (auto& obj : obstacles) {
//        if (checkCollision(*obj, newPos)) {
//            return this->Position;
//        }
//    }
//
//    this->Position = newPos;
//    return this->Position;
//}

void BirdObject::Update(float dt, std::vector<SceneObject*>& obstacles, bool Keys[]) {
    // ----- MOVEMENT
    glm::vec3 direction(0.0f);
    glm::vec3 rotation(0.0f);

    if (Keys[GLFW_KEY_UP]) {
        direction.z -= 1.0f; // forward

    }
    if (Keys[GLFW_KEY_DOWN]) {
        direction.z += 1.0f; // backward
    }
    if (Keys[GLFW_KEY_LEFT]) {
        direction.x -= 1.0f; // left
    }
    if (Keys[GLFW_KEY_RIGHT]) {
        direction.x += 1.0f; // right
    }

    if (glm::length(direction) > 0.0f) {
        direction = glm::normalize(direction);

        float angleY = atan2(direction.x, direction.z);
        Rotation = glm::vec3(0.0f, glm::degrees(angleY), 0.0f);
    }


    glm::vec3 proposedPos = Position + direction * Velocity * dt;

    // stop moving if bird collision
    for (auto& obj : obstacles) {
        if (checkCollision(*obj, proposedPos)) {
            proposedPos = Position;
            break;
        }
    }

    Position = proposedPos;

    if (Keys[GLFW_KEY_SPACE] && !IsJumping) {
        Jump();
    }

    if (IsJumping) {
        Position.y += JumpVelocity * dt;
        JumpVelocity += Gravity * dt;

        if (Position.y <= GroundY) {
            Position.y = GroundY;
            IsJumping = false;
            JumpVelocity = 0.0f;
            GroundY = 0.0f;
        }
    }



    /*if (IsBlinking) {
        blinkTimer += dt;
        if (blinkTimer >= blinkDuration) {
            IsBlinking = false;
        }
    }

    if (IsWalking) {
        legTimer += dt;
        if (legTimer >= legInterval) {
            legTimer = 0.0f;
            currentLeg = (currentLeg + 1) % LegFrames.size();
        }
    }
    else {
        currentLeg = 1;
    }*/
}

void BirdObject::Jump() {
    IsJumping = true;
    JumpVelocity = JumpStrength;
    GroundY = this->Position.y;
}

//void BirdObject::Blink() {
//    IsBlinking = true;
//    blinkTimer = 0.0f;
//}

//void BirdObject::Draw(SpriteRenderer& renderer) {
//    Texture bodyTex = ResourceManager::GetTexture("bird");
//    Texture openEyeTex = ResourceManager::GetTexture("open_eye");
//    Texture closedEyeTex = ResourceManager::GetTexture("closed_eye");
//
//    glm::vec2 flipScale = FacingRight ? glm::vec2(-1.0f, 1.0f)
//        : glm::vec2(1.0f, 1.0f);
//
//    glm::vec2 drawPos = this->Position;
//    if (FacingRight)
//        drawPos.x += this->Size.x;
//
//    renderer.DrawSprite(LegFrames[currentLeg], drawPos, this->Size, 0.0f, glm::vec4(1.0f),
//        false, false, flipScale);
//
//    renderer.DrawSprite(bodyTex, drawPos, this->Size, 0.0f, glm::vec4(1.0f),
//        false, false, flipScale);
//
//    if (IsBlinking) {
//        renderer.DrawSprite(closedEyeTex, drawPos, this->Size, 0.0f, glm::vec4(1.0f),
//            false, false, flipScale);
//    }
//    else {
//        renderer.DrawSprite(openEyeTex, drawPos, this->Size, 0.0f, glm::vec4(1.0f),
//            false, false, flipScale);
//    }
//}

bool BirdObject::checkCollision(SceneObject& obj, glm::vec3 pos) {
    bool collisionX = pos.x + this->Size.x >= obj.Position.x && obj.Position.x + obj.Size.x >= pos.x;
    bool collisionY = pos.y + this->Size.y >= obj.Position.y && obj.Position.y + obj.Size.y >= pos.y;
    bool collisionZ = pos.z + this->Size.z >= obj.Position.z && obj.Position.z + obj.Size.z >= pos.z;

    return collisionX && collisionY && collisionZ;
}