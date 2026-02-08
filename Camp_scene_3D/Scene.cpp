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
	initObjects();

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
    unifiedShader.setVec3("uLightPos", 0, 1, 3);
    unifiedShader.setVec3("uViewPos", 0, 0, 5);
    unifiedShader.setVec3("uLightColor", 1, 1, 1);

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

    glm::vec3 birdSize = glm::vec3(0.4f);
    glm::vec3 tentSize = glm::vec3(0.02f);
    glm::vec3 treeSize = glm::vec3(0.01f);
    glm::vec3 logSize = glm::vec3(0.06f);

    // bird
    Model* birdModel = new Model("res/bird.obj");
    Models.push_back(birdModel);
    //bird = new BirdObject(birdPos, birdSize, glm::vec3(-90.0f, 0.0f, 0.0f), *birdModel);
    bird = new BirdObject(birdPos, birdSize, glm::vec3(0.0f, 0.0f, 0.0f), *birdModel);

    // Tent
    Model* tentModel = new Model("res/tent.obj");
    Models.push_back(tentModel);
    //tent = new SceneObject(tentPos, tentSize, glm::vec3(-90.0f, 0.0f, -60.0f), *tentModel);
    tent = new SceneObject(tentPos, tentSize, glm::vec3(0.0f, -60.0f, 0.0f), *tentModel);
    Objects.push_back(tent);    

    // Tree
    Model* treeModel = new Model("res/tree.obj");
    Models.push_back(treeModel);
    //tree = new SceneObject(treePos, treeSize, glm::vec3(-90.0f, 0.0f, 0.0f), *treeModel);
    tree = new SceneObject(treePos, treeSize, glm::vec3(0.0f, 0.0f, 0.0f), * treeModel);
    Objects.push_back(tree);


    // Log
    Model* logModel = new Model("res/log.obj");
    Models.push_back(logModel);
    //log = new SceneObject(logPos, logSize, glm::vec3(-90.0f, 0.0f, 0.0f), *logModel);
    log = new SceneObject(logPos, logSize, glm::vec3(0.0f, 0.0f, 0.0f), *logModel);
    Objects.push_back(log);



    //Model* foxModel = new Model("res/low-poly-fox.obj");
    //Models.push_back(foxModel);
    //Objects.push_back(new SceneObject(glm::vec3(0.0f, 0.0f, 0.0f),  // position
    //    glm::vec3(1.0f, 1.0f, 1.0f),  // size
    //    *foxModel));                   // reference to model


}

void Scene::Update(float dt, bool Keys[]) {
    ProcessInput(dt);
    bird->Update(dt, Objects, Keys);
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
    glm::mat4 model = transformModel(bird->Position, bird->Rotation, bird->Size);
    unifiedShader.setMat4("uM", model);
    bird->Draw(unifiedShader);

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

    // skybox
    glDisable(GL_CULL_FACE);   // optional if only room uses special culling
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