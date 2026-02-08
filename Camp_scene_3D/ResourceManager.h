#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "BasicTexture.h"
#include "shader.hpp"

class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, BasicTexture> Textures;
    static Shader& LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
    static Shader& GetShader(std::string name);
    static BasicTexture& LoadTexture(const char* file, bool alpha, std::string name);
    static BasicTexture& GetTexture(std::string name);
    static void Clear();
private:
    ResourceManager() {}
};

#endif