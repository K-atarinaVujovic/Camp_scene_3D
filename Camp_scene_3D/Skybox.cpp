#include "Skybox.h"
#include "stb_image.h"
#include <iostream>

Skybox::Skybox() {
    
}

Skybox::~Skybox() {
    for (int i = 0; i < 6; ++i) {
        glDeleteVertexArrays(1, &faces[i].VAO);
        glDeleteBuffers(1, &faces[i].VBO);
        glDeleteTextures(1, &faces[i].textureID);
    }
}

void Skybox::Init(const std::vector<std::string>& textures) {
    if (textures.size() != 6) {
        std::cerr << "Skybox needs 6 textures!" << std::endl;
        return;
    }

    // Each face is a square with positions, normals, UVs
    // Normals point **inwards** so lighting works
    // Vertices: x, y, z, nx, ny, nz, u, v
    std::vector<std::vector<float>> faceVerts(6);
    for (int i = 0; i < 6; i++) {
        faces[i] = Face();
    }

    float s = 8.0f;  // half-size in X/Z
    float h = 4.0f;  // half-height in Y

    // Right (+X)
    faceVerts[0] = {
        s, -h, -s, -1,0,0, 0,0,
        s,  h, -s, -1,0,0, 0,1,
        s,  h,  s, -1,0,0, 1,1,
        s,  h,  s, -1,0,0, 1,1,
        s, -h,  s, -1,0,0, 1,0,
        s, -h, -s, -1,0,0, 0,0
    };

    // Left (-X)
    faceVerts[1] = {
       -s, -h,  s, 1,0,0, 0,0,
        -s,  h,  s, 1,0,0, 0,1,
        -s,  h, -s, 1,0,0, 1,1,
        -s,  h, -s, 1,0,0, 1,1,
        -s, -h, -s, 1,0,0, 1,0,
        -s, -h,  s, 1,0,0, 0,0
    };

    // Top (+Y)
    faceVerts[2] = {
       -s, h, -s, 0,-1,0, 0,0,
        -s, h,  s, 0,-1,0, 0,1,
         s, h,  s, 0,-1,0, 1,1,
         s, h,  s, 0,-1,0, 1,1,
         s, h, -s, 0,-1,0, 1,0,
       -s, h, -s, 0,-1,0, 0,0
    };

    // Bottom (-Y)
    faceVerts[3] = {
       -s, -h,  s, 0,1,0, 0,0,
       -s, -h, -s, 0,1,0, 0,1,
        s, -h, -s, 0,1,0, 1,1,
        s, -h, -s, 0,1,0, 1,1,
        s, -h,  s, 0,1,0, 1,0,
       -s, -h,  s, 0,1,0, 0,0
    };

    // Front (+Z)
    faceVerts[4] = {
       -s, -h, s, 0,0,-1, 0,0,
        s, -h, s, 0,0,-1, 1,0,
        s,  h, s, 0,0,-1, 1,1,
        s,  h, s, 0,0,-1, 1,1,
       -s,  h, s, 0,0,-1, 0,1,
       -s, -h, s, 0,0,-1, 0,0
    };

    // Back (-Z)
    faceVerts[5] = {
        s, -h, -s, 0,0,1, 0,0,
       -s, -h, -s, 0,0,1, 1,0,
       -s,  h, -s, 0,0,1, 1,1,
       -s,  h, -s, 0,0,1, 1,1,
        s,  h, -s, 0,0,1, 0,1,
        s, -h, -s, 0,0,1, 0,0
    };


    for (int i = 0; i < 6; ++i) {
        setupFace(faces[i], faceVerts[i], textures[i].c_str());
    }
}

void Skybox::Draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    for (int i = 0; i < 6; ++i) {
        shader.use();

        glm::mat4 model = glm::mat4(1.0f); // identity; box centered at origin
        shader.setMat4("uM", model);
        shader.setMat4("uV", view);
        shader.setMat4("uP", projection);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, faces[i].textureID);
        glBindVertexArray(faces[i].VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);
}

//GLuint Skybox::loadTexture(const std::string& path) {
//    GLuint textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//
//    int w, h, n;
//    unsigned char* data = stbi_load(path.c_str(), &w, &h, &n, 0);
//    if (!data) {
//        std::cerr << "Failed to load texture: " << path << std::endl;
//        return 0;
//    }
//
//    GLenum format = (n == 4) ? GL_RGBA : GL_RGB;
//    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
//    stbi_image_free(data);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//    return textureID;
//}

void Skybox::setupFace(Face& face, const std::vector<float>& vertices, const char* texPath) {
    glGenVertexArrays(1, &face.VAO);
    glGenBuffers(1, &face.VBO);

    glBindVertexArray(face.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, face.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    BasicTexture tex;
    tex.Generate(texPath);

    //face.textureID = loadTexture(texPath);
    /*glActiveTexture(GL_TEXTURE0);
    tex.Bind();*/
    face.textureID = tex.ID;

    glBindVertexArray(0);
}
