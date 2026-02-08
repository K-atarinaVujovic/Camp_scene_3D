#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Camera.h"
#include "shader.hpp"
#include "model.h"
#include "SceneObject.h"
#include "BirdObject.h"
#include "Texture.h"
#include "Skybox.h"
#include "ResourceManager.h"
#include "Scene2DObject.h"
#include "SpriteRenderer.h"

enum SceneState {
};

class Scene
{
public:
    bool IsStorming = false;
    bool IsRaining = false;

    bool IsFlashing = false;
    float FlashTimer = 0.0f;
    int FlashCount = 0;
    const int MaxFlashes = 8;
    float StormDelay = 3.0f;
    float StormTimer = 0.0f;

    const float FireSquishFactor = 0.0f;
    const float FireSquishSpeed = 0.01f;

    const float cameraSpeed = 5.0f;

    bool* Keys;
    unsigned int Width, Height;

    float bottom = -4.0f;


    Scene(unsigned int width, unsigned int height, bool keys[]);
    ~Scene();


    void Init();
    void ProcessInput(float dt);
    void Update(float dt, bool Keys[]);
    void Render();
    void OnMouseClick(int button, int action, int mods);

    /*std::vector<SceneObject*> Obstacles;
    bool* Keys;
    unsigned int Width, Height;
    Scene(unsigned int width, unsigned int height, bool keys[]);
    ~Scene();
    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void DoCollisions();
    void OnMouseClick(int button, int action, int mods);
    void StormCutscene();*/
private:
    Shader unifiedShader;
    Shader skyboxShader;
    Skybox skybox;
    Camera camera;
    BirdObject* bird;
    SceneObject* tent;
    SceneObject* tree;
    SceneObject* log;
    SceneObject* flame;

    //2D
   /* Scene2DObject* flame;
    SpriteRenderer* renderer;*/

    vector<SceneObject*> Objects;
    vector<SceneObject*> Obstacles;
    vector<Model*> Models; // just to delete dangling pointers

    glm::mat4 transformModel(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size);
    void initShaders();
    void initObjects();
    /*void initTextures();
    void init2DObjects();*/
    glm::vec2 getNormalizedSizeWidth(const BasicTexture& tex, float scale);
    glm::vec2 getNormalizedSizeHeight(const BasicTexture& tex, float scale);
    bool checkCollision(SceneObject& bird, SceneObject& so);


    /*void initShaders();
    void initTextures();
    void initObjects();
    void initParticles();
    void drawBackgrounds();
    bool checkCollision(SceneObject& bird, SceneObject& so);
    glm::vec2 getNormalizedSizeWidth(const Texture& tex, float scale);
    glm::vec2 getNormalizedSizeHeight(const Texture& tex, float scale);*/
};

#endif