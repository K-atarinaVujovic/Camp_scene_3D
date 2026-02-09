//Opis: Primjer ucitavanja modela upotrebom ASSIMP biblioteke
//Preuzeto sa learnOpenGL

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include "Scene.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//const unsigned int wWidth = 800;
//const unsigned int wHeight = 600;

bool Keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Keys[key] = false;
    }
}

int main()
{
    // Window init
    if(!glfwInit())
    {
        std::cout << "GLFW fail!\n" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int screenWidth = 800;
    int screenHeight = 800;

    // Fullscreen info
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    screenWidth = mode->width;
    screenHeight = mode->height;

    // Create window
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Camp_scene_3D", monitor, NULL);
    if (window == NULL)
    {
        std::cout << "Window fail!\n" << std::endl;
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);

    // Callbacks
    glfwSetKeyCallback(window, key_callback);


    if (glewInit() !=GLEW_OK)
    {
        std::cout << "GLEW fail! :(\n" << std::endl;
        return -3;
    }

    // Scene
    Scene scene(screenWidth, screenHeight, Keys);
    scene.Init();


    glfwSetWindowUserPointer(window, &scene);

    // Set GLFW mouse callback
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            // Retrieve your scene pointer stored as user pointer
            Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
            if (scene) scene->OnMouseClick(button, action, mods);
        });

    // model setup
    //Model lija("res/low-poly-fox.obj");
    //Shader unifiedShader("basic.vert", "basic.frag");

    // podesavanje osnovnog shadera
    /*unifiedShader.use();
    unifiedShader.setVec3("uLightPos", 0, 1, 3);
    unifiedShader.setVec3("uViewPos", 0, 0, 5);
    unifiedShader.setVec3("uLightColor", 1, 1, 1);*/

    // camera
    /*glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)wWidth / (float)wHeight, 0.1f, 100.0f);
    unifiedShader.setMat4("uP", projection);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    unifiedShader.setMat4("uV", view);*/
    /*Camera camera(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        (float)wWidth / wHeight
    );

    unifiedShader.setMat4("uP", camera.GetProjectionMatrix());
    unifiedShader.setMat4("uV", camera.GetViewMatrix());*/


    // model
    //glm::mat4 model = glm::mat4(1.0f);

    // podesavanje light shadera?

    float lastTime = -1;

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        double initFrameTime = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentTime = glfwGetTime();
        float dt;
        if (currentTime > lastTime) {
            dt = currentTime - lastTime;
        }
        else {
            dt = 0;
        }
        lastTime = currentTime;

        //model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
        /*unifiedShader.setMat4("uM", model);
        lija.Draw(unifiedShader);*/
        scene.Update(dt, Keys);
        scene.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        while (glfwGetTime() - initFrameTime < 1 / 75.0) {}
    }

    glfwTerminate();
    return 0;
}


