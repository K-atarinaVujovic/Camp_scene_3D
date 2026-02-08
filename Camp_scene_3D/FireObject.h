#ifndef FIREOBJECT_H
#define FIREOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <map>
#include <vector>

#include "SceneObject.h"

class FireObject : public SceneObject
{
public:
    glm::vec3 FlameSize;
    bool SendingSmoke = false;

    FireObject();
    FireObject(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Model& model);
    void Update(float dt);
    void SendSmoke();
};

#endif