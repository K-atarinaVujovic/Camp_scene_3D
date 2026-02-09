#include "Scene.h"

Scene::Scene(unsigned int width, unsigned int height, bool keys[]) : Keys(keys), Width(width), Height(height), camera(
    glm::vec3(0.0f, 5.0f, 20.0f),
    (float)width / height
), unifiedShader("basic.vert", "basic.frag"), skyboxShader("skybox.vert", "skybox.frag"), skybox() {

}

Scene::~Scene() {
    for (auto obj : Objects)
        delete obj;
    for (auto model : Models)
        delete model;
    delete bird;
 }

void Scene::Init() {
    initShaders();
    //renderer = new SpriteRenderer(unifiedShader);
	initObjects();
    //initTextures();
    //init2DObjects();
    Model drop = Model("res/drop.obj");
    rainGenerator = new RainGenerator(unifiedShader, drop, 200);

    skybox.Init({
        "res/sides.png",
        "res/sides.png",
        "res/top.png",
        "res/bottom.png",
        "res/sides.png",
        "res/sides.png"
        });
}


void Scene::initShaders() {
    // unified shader
    unifiedShader.use();
    //unifiedShader.setVec3("uLightPos", 0, 1, 4);
    unifiedShader.setVec3("uViewPos", 0, 0, 5);
    unifiedShader.setVec3("uLightColor", 1, 1, 1);

    unifiedShader.setVec3("light.ambient", glm::vec3(0.1f));
    unifiedShader.setVec3("light.diffuse", glm::vec3(0.5f));
    unifiedShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);

    // camera
    unifiedShader.setMat4("uP", camera.GetProjectionMatrix());
    unifiedShader.setMat4("uV", camera.GetViewMatrix());

    // skybox shader
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);
}

void Scene::initObjects() {
    float bottomOffset = 0.5f;

    glm::vec3 birdPos = glm::vec3(4.0f, bottom + bottomOffset, 3.0f);
    glm::vec3 tentPos = glm::vec3(-3.8f, bottom + bottomOffset, -1.0f);
    glm::vec3 treePos = glm::vec3(4.0f, bottom + bottomOffset, -4.0f);
    glm::vec3 logPos = glm::vec3(0.0f, bottom + bottomOffset, 3.0f);
    glm::vec3 flamePos = glm::vec3(logPos.x, logPos.y + 0.5f, logPos.z);
    glm::vec3 brellaPos = birdPos + brellaOffset;

    glm::vec3 birdSize = glm::vec3(0.4f);
    glm::vec3 tentSize = glm::vec3(0.02f);
    glm::vec3 treeSize = glm::vec3(0.01f);
    glm::vec3 logSize = glm::vec3(0.06f);
    glm::vec3 flameSize = glm::vec3(0.025f);

    // bird
    Model* birdModel = new Model("res/bird.obj");
    Models.push_back(birdModel);
    //bird = new BirdObject(birdPos, birdSize, glm::vec3(-90.0f, 0.0f, 0.0f), *birdModel);
    bird = new BirdObject(birdPos, birdSize, glm::vec3(0.0f, 0.0f, 0.0f), *birdModel);

    // brella
    Model* brellaModel = new Model("res/brella.obj");
    Models.push_back(brellaModel);
    brella = new SceneObject(brellaPos, brellaSize, glm::vec3(0.0f), *brellaModel);

    // Tent
    Model* tentModel = new Model("res/tent.obj");
    Models.push_back(tentModel);
    //tent = new SceneObject(tentPos, tentSize, glm::vec3(-90.0f, 0.0f, -60.0f), *tentModel);
    tent = new SceneObject(tentPos, tentSize, glm::vec3(0.0f, -60.0f, 0.0f), *tentModel);
    Objects.push_back(tent);    
    Obstacles.push_back(tent);

    // Tree
    Model* treeModel = new Model("res/tree.obj");
    Models.push_back(treeModel);
    //tree = new SceneObject(treePos, treeSize, glm::vec3(-90.0f, 0.0f, 0.0f), *treeModel);
    tree = new SceneObject(treePos, treeSize, glm::vec3(0.0f, 0.0f, 0.0f), * treeModel);
    Objects.push_back(tree);
    Obstacles.push_back(tree);


    // Log
    Model* logModel = new Model("res/log.obj");
    Models.push_back(logModel);
    //log = new SceneObject(logPos, logSize, glm::vec3(-90.0f, 0.0f, 0.0f), *logModel);
    log = new SceneObject(logPos, logSize, glm::vec3(0.0f, 0.0f, 0.0f), *logModel);
    Objects.push_back(log);
    Obstacles.push_back(log);


    // Flame
    Model* flameModel = new Model("res/flame.obj");
    Models.push_back(flameModel);
    flame = new SceneObject(flamePos, flameSize, glm::vec3(0.0f, 0.0f, 0.0f), *flameModel);
    Objects.push_back(flame);



    //Model* foxModel = new Model("res/low-poly-fox.obj");
    //Models.push_back(foxModel);
    //Objects.push_back(new SceneObject(glm::vec3(0.0f, 0.0f, 0.0f),  // position
    //    glm::vec3(1.0f, 1.0f, 1.0f),  // size
    //    *foxModel));                   // reference to model


}

void Scene::Update(float dt, bool Keys[]) {
    ProcessInput(dt);
    bird->Update(dt, Obstacles, Keys);
    brella->Position = bird->Position + brellaOffset;

    if (IsFlashing) {
        FlashTimer += dt;
        if (FlashTimer >= 0.2f) { // flash every 0.2s
            FlashTimer = 0.0f;
            FlashCount++;
            if (FlashCount >= MaxFlashes) {
                IsFlashing = false;
                StormTimer = 0.0f; // start storm delay
                IsStorming = true;
            }
        }
    }
    else if (IsStorming) {
        StormTimer += dt;
        if (StormTimer >= StormDelay) {
            // Start rain
            IsRaining = true;
        }
    }

    // Go in tent
    if (IsRaining && !bird->IsInTent) {
        if (checkCollision(*bird, *tent)) {
            bird->IsInTent = true;
        }
    }

    if (IsRaining) {
        rainGenerator->Update(dt, glm::vec3(8.0f, 4.0f, 8.0f));
        Obstacles.erase(std::remove(Obstacles.begin(), Obstacles.end(), tent), Obstacles.end());
        if (flame->Size.y > 0.010f) {
            flame->Size.y -= FireSquishSpeed * dt;
            if (flame->Size.y < 0.010f) {
                flame->Size.y = 0.0f;
            }
        }
    }
}

void Scene::ProcessInput(float dt) {
    float speed = cameraSpeed * dt;

    if (Keys[GLFW_KEY_W])
        camera.MoveForward(speed);
    if (Keys[GLFW_KEY_S])
        camera.MoveForward(-speed);
    if (Keys[GLFW_KEY_A])
        camera.MoveRight(-speed);
    if (Keys[GLFW_KEY_D])
        camera.MoveRight(speed);
}

void Scene::Render() {
    // scene objects
    unifiedShader.use();

    // flash
    bool flashNow = IsFlashing && (FlashCount % 2 == 1);
    if (flashNow) {
        unifiedShader.setVec3("light.ambient", glm::vec3(0.8f));
    }
    else {
        unifiedShader.setVec3("light.ambient", glm::vec3(0.1f));
    }

    for (auto obj : Objects) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, obj->Position);
        model = glm::rotate(model, glm::radians(obj->Rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(obj->Rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(obj->Rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, obj->Size);

        unifiedShader.setMat4("uM", model);
        obj->Draw(unifiedShader);
    }

    // bird
    if (!bird->IsInTent) {
        glm::mat4 model = transformModel(bird->Position, bird->Rotation, bird->Size);
        unifiedShader.setMat4("uM", model);
        bird->Draw(unifiedShader);
    }
    

    // tent
    glm::mat4 model2 = transformModel(tent->Position, tent->Rotation, tent->Size);
    unifiedShader.setMat4("uM", model2);
    tent->Draw(unifiedShader);

    // tree
    glm::mat4 model3 = transformModel(tree->Position, tree->Rotation, tree->Size);
    unifiedShader.setMat4("uM", model3);
    tree->Draw(unifiedShader);

    // log
    glm::mat4 model4 = transformModel(log->Position, log->Rotation, log->Size);
    unifiedShader.setMat4("uM", model4);
    log->Draw(unifiedShader);

    // flame
    glm::mat4 model5 = transformModel(flame->Position, flame->Rotation, flame->Size);
    unifiedShader.setMat4("uM", model5);
    flame->Draw(unifiedShader);

    

    // rain
    if (IsRaining) {
        rainGenerator->Draw();
        glm::mat4 model6 = transformModel(brella->Position, brella->Rotation, brella->Size);
        unifiedShader.setMat4("uM", model6);
        brella->Draw(unifiedShader);
    }
        

    // 2D
    //flame->Draw(*renderer);
    /*renderer->DrawSprite(
        flame->Sprite,
        camera.GetViewMatrix(),
        camera.GetProjectionMatrix(),
        flame->Position,
        flame->Size,
        flame->Rotation,
        flame->Color
    );*/

    // skybox
    glDisable(GL_CULL_FACE); 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 proj = camera.GetProjectionMatrix();
    skybox.Draw(unifiedShader, view, proj);

    glCullFace(GL_BACK);
}

glm::mat4 Scene::transformModel(glm::vec3 pos, glm::vec3 rotation, glm::vec3 size) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, size);

    return model;
}

//void Scene::initTextures() {
//    // flame
//    ResourceManager::LoadTexture("res/flame1.png", true, "flame1");
//    ResourceManager::LoadTexture("res/flame2.png", true, "flame2");
//    ResourceManager::LoadTexture("res/flame3.png", true, "flame3");
//    ResourceManager::LoadTexture("res/smoke.png", true, "smoke");
//
//    // drop
//    ResourceManager::LoadTexture("res/drop.png", true, "drop");
//
//}

//void Scene::init2DObjects() {
//    // fire
//    /*std::vector<BasicTexture> flameTextures;
//    flameTextures.push_back(ResourceManager::GetTexture("flame1"));
//    flameTextures.push_back(ResourceManager::GetTexture("flame2"));
//    flameTextures.push_back(ResourceManager::GetTexture("flame3"));
//    glm::vec2 fireSize = getNormalizedSizeWidth(flameTextures[0], 0.12f);*/
//    BasicTexture flameTextures = ResourceManager::GetTexture("flame1");
//    //glm::vec2 fireSize = getNormalizedSizeWidth(flameTextures, 0.12f);
//    glm::vec2 fireSize = glm::vec2(50.0f);
//    glm::vec3 firePos = glm::vec3(0.0f, 0.0f, 0.0f);
//    flame = new Scene2DObject(firePos, fireSize, flameTextures);
//
//}

glm::vec2 Scene::getNormalizedSizeWidth(const BasicTexture& tex, float scale)
{
    float targetWidth = Width * scale;

    float aspect = (float)tex.TextureHeight / (float)tex.TextureWidth;
    float targetHeight = targetWidth * aspect;

    return glm::vec2(targetWidth, targetHeight);
}

glm::vec2 Scene::getNormalizedSizeHeight(const BasicTexture& tex, float scale)
{
    float targetHeight = Height * scale;

    float aspect = (float)tex.TextureHeight / (float)tex.TextureWidth;
    float targetWidth = targetHeight / aspect;

    return glm::vec2(targetWidth, targetHeight);
}

void Scene::OnMouseClick(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (!IsStorming && !IsFlashing) {
            IsFlashing = true;
            FlashTimer = 0.0f;
            FlashCount = 0;
            bird->Jump();
        }
    }
}

bool Scene::checkCollision(SceneObject& one, SceneObject& two) {
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x && two.Position.x + two.Size.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y && two.Position.y + two.Size.y >= one.Position.y;
    bool collisionZ = one.Position.z + one.Size.z >= two.Position.z && two.Position.z + two.Size.z >= one.Position.z;

    return collisionX && collisionY && collisionZ;
}