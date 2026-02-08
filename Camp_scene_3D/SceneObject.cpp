#include "SceneObject.h"


SceneObject::SceneObject(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Model& model, float velocity)
    : Position(pos), Size(size), Velocity(velocity), Rotation(rotation), ObjectModel(model), IsSolid(false), Destroyed(false) {

}

void SceneObject::Draw(Shader& shader) {
    ObjectModel.Draw(shader);
}