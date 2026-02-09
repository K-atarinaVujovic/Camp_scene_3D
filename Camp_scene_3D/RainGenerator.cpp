#include "RainGenerator.h"

RainGenerator::RainGenerator(Shader shader, Model model, unsigned int amount, glm::vec3 size)
    : ParticleGenerator(shader, model, amount, size) {

}

void RainGenerator::UpdateParticle(Particle& p, float dt) {
    p.Position -= p.Velocity * dt;
}

void RainGenerator::Update(float dt, glm::vec3 areaSize)
{
    spawnTimer += dt;
    if (spawnTimer >= spawnInterval)
    {
        spawnTimer = 0.0f;
        int unusedParticle = this->firstUnusedParticle();
        this->RespawnParticle(this->particles[unusedParticle], areaSize);
    }

    for (unsigned int i = 0; i < this->amount; ++i)
    {
        Particle& p = this->particles[i];
        if (p.Life > 0.0f)
        {
            UpdateParticle(p, dt);

            // If raindrop goes below screen, mark it dead
            if (p.Position.y <= -4.0f) // change
                p.Life = 0.0f;
        }
    }
}

void RainGenerator::RespawnParticle(Particle& p, glm::vec3 areaSize) {
    float xPos = (static_cast<float>(rand()) / RAND_MAX) * (areaSize.x * 2.0f) - areaSize.x;
    float zPos = (static_cast<float>(rand()) / RAND_MAX) * (areaSize.z * 2.0f) - areaSize.z;
    float yPos = areaSize.y;
    p.Position = glm::vec3(xPos, yPos, zPos);
    p.Color = glm::vec4(1.0f);
    p.Life = Life;
    p.Velocity = Velocity;
    p.Size = this->particleSize;
}