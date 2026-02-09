#ifndef RAINGENERATOR_H
#define RAINGENERATOR_H
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "SceneObject.h"
#include "ParticleGenerator.h"

class RainGenerator : public ParticleGenerator
{
public:
    float Life = 5.0f;
    glm::vec3 Velocity = glm::vec3(0.0f, 3.0f, 0.0f);
    glm::vec3 ParticleSize = glm::vec3(0.5f);

    RainGenerator(Shader shader, Model model, unsigned int amount, glm::vec3 size = glm::vec3(0.09));
    void Update(float dt, glm::vec3 areaSize);
    void UpdateParticle(Particle& p, float dt);;
    void RespawnParticle(Particle& p, glm::vec3 areaSize);
private:
    float spawnTimer = 0.0f;
    float spawnInterval = 0.1f;
};

#endif