//#include "FireObject.h"
//
//float smokeTimer = 0.0f;
//float smokeInterval = 1.0f;
//float frameTimer = 0.0f;
//float frameInterval = 0.5f;
//int currentFlame = 0;
//
//FireObject::FireObject(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, Model& model)
//    : SceneObject(pos, size, rotation, model) {
//    FlameSize = size;
//}
//
//void FireObject::Update(float dt) {
//    
//}
//
//void FireObject::Draw(SpriteRenderer& renderer) {
//    Texture logsTex = ResourceManager::GetTexture("logs");
//
//    renderer.DrawSprite(logsTex, this->Position, this->Size);
//    renderer.DrawSprite(this->Sprite, this->Position, this->FlameSize);
//}
//
//void FireObject::SendSmoke() {
//
//}