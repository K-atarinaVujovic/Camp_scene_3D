#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Model model, unsigned int amount, glm::vec3 particleSize)
    : shader(shader), drop(model), amount(amount), particleSize(particleSize)
{
    this->init();
}

//void ParticleGenerator::Update(float dt, SceneObject& object, unsigned int newParticles, glm::vec2 offset)
//{
//    for (unsigned int i = 0; i < newParticles; ++i)
//    {
//        int unusedParticle = this->firstUnusedParticle();
//        this->RespawnParticle(this->particles[unusedParticle], object, offset);
//    }
//    for (unsigned int i = 0; i < this->amount; ++i)
//    {
//        Particle& p = this->particles[i];
//        p.Life -= dt;
//        if (p.Life > 0.0f)
//        {
//            //p.Position -= p.Velocity * dt;
//            //p.Color.a -= dt * 2.5f;`
//            UpdateParticle(p, dt);
//        }
//    }
//}

void ParticleGenerator::Draw()
{
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    /*this->shader.Use();
    for (Particle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            this->shader.SetVector2f("offset", particle.Position);
            this->shader.SetVector4f("color", particle.Color);
            this->shader.SetVector2f("scale", particleSize);
            this->texture.Bind();
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
    for (Particle particle : this->particles) {
        if (particle.Life > 0.0f) {
            glm::mat4 model = transformModel(particle.Position, glm::vec3(0.0f), particle.Size);
            shader.setMat4("uM", model);
            drop.Draw(shader);
        }
    }

}

void ParticleGenerator::init()
{
    /*unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    for (unsigned int i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle());*/
    //drop = Model("res/drop.obj");

    for (unsigned int i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle());
}

unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
    for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
        if (this->particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (this->particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    lastUsedParticle = 0;
    return 0;
}

//void ParticleGenerator::respawnParticle(Particle& particle, SceneObject& object, glm::vec2 offset)
//{
//    float random = ((rand() % 100) - 50) / 10.0f;
//    float rColor = 0.5f + ((rand() % 100) / 100.0f);
//    particle.Position = object.Position + random + offset;
//    particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
//    particle.Life = 1.0f;
//    // Velocity :)))
//    //particle.Velocity = object.Velocity * 0.1f;
//}

glm::mat4 ParticleGenerator::transformModel(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, size);

    return model;
}