#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "World.h"
#include "entities/CameraEntity.h"
#include "entities/QuadMeshEntity.h"
#include "fs/ShaderLoader.h"
#include "math/Transform.h"
#include "math/Vector3.h"
#include "render/Render.h"


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
    return true;
}

int main() {
    GLFWwindow *window = initGlfw();
    if (window == nullptr) return -1;

    if (!initGlew(window)) return -1;

    const GLuint shader = ShaderLoader::createShaderProgram("shader", "assets/shaders/");
    glUseProgram(shader);

    glEnable(GL_DEPTH_TEST);

    GLuint vp_uniform = glGetUniformLocation(shader, "vp"); // 1
    GLuint model_uniform = glGetUniformLocation(shader, "model"); // 0

    auto *world = new World();
    Render *render = world->getRender();
    auto camera = world->spawnEntity<CameraEntity>();
    auto entity = world->spawnEntity<QuadMeshEntity>();
    entity->transform->position->z = -2;

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
        render->rendering();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
