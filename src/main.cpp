#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "World.h"
#include "entities/CameraEntity.h"
#include "entities/QuadMeshEntity.h"
#include "AssetManager.h"
#include "ShaderAssetLoader.h"
#include "math/Transform.h"
#include "math/Vector3.h"
#include "render/Render.h"
#include "render/Shader.h"


GLFWwindow *initGlfw() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    return window;
}

bool initGlew(GLFWwindow *window) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return false;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.2, 0.3, 1);

    return true;
}

int main() {
    GLFWwindow *window = initGlfw();
    if (window == nullptr) return -1;

    if (!initGlew(window)) return -1;

    auto world = std::make_shared<World>();

    ASSET_MANAGER.registerAssetLoader<Shader>(std::make_unique<ShaderAssetLoader>());

    // test level data --->
    auto camera = world->spawnEntity<CameraEntity>();
    camera->transform->translate(Vector3(0, 0, -8));

    auto entity = world->spawnEntity<QuadMeshEntity>();

    auto entity2 = world->spawnEntity<QuadMeshEntity>();
    entity2->transform->translate(Vector3(0, 0, -2));
    entity2->transform->rotate(Vector3(35, 0, 20));
    entity2->transform->setScale(Vector3(0.5f));

    auto entity3 = world->spawnEntity<QuadMeshEntity>();
    entity3->transform->translate(Vector3(0, 0, -2));
    entity3->transform->setScale(Vector3(0.5f));

    entity2->transform->attachTo(entity->transform);
    entity3->transform->attachTo(entity2->transform);
    // <---

    float lastTime = 0;
    float currentTime = 0;
    float deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        if (lastTime == 0)
            deltaTime = 0;
        world->update(deltaTime);
        lastTime = currentTime;
        Render::getInstance().rendering();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
