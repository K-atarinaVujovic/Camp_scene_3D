#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "shader.hpp"
#include "BasicTexture.h"

class Skybox {
public:
    Skybox();
    ~Skybox();

    void Init(const std::vector<std::string>& textures);
    void Draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

private:
    struct Face {
        GLuint VAO;
        GLuint VBO;
        GLuint textureID;
    };

    Face faces[6]; // right, left, top, bottom, front, back

    //GLuint loadTexture(const char* path);
    void setupFace(Face& face, const std::vector<float>& vertices, const char* texPath);
};

#endif
