#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "SceneObject.h"

struct Particle {
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Velocity;
    glm::vec4 Color;
    float     Life;
    glm::vec3 Size;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f), Size(1.0f) {}
};

class ParticleGenerator
{
public:
    ParticleGenerator(Shader shader, Model model, unsigned int amount, glm::vec3 particleSize); // need
    void Draw(); // need or do i?
    glm::vec3 particleSize; // need
    std::vector<Particle> particles; // need
    unsigned int amount; // need
    unsigned int firstUnusedParticle(); // need
private:
    Shader shader;
    Model drop;
    void init();
    glm::mat4 transformModel(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size);
    //void respawnParticle(Particle& particle, SceneObject& object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif