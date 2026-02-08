#ifndef BASICTEXTURE_H
#define BASICTEXTURE_H

#include <GL/glew.h>
#include <stdlib.h>
#include <iostream>
#include "stb_image.h"
#include<string>
#include<vector>


class BasicTexture
{
public:
    unsigned int ID;
    int TextureWidth;
    int TextureHeight;

    BasicTexture();
    void Generate(const char* filePath);
    void GenerateCube(const std::vector<std::string>& faces);
    void Bind() const;
private:
    void loadImageToTexture(const char* filePath);
};

#endif