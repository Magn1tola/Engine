//
// Created by Magnitola on 19.10.2025.
//

#include "Application.h"

#include "AssetManager.h"
#include "World.h"
#include "entities/CameraEntity.h"
#include "entities/QuadMeshEntity.h"
#include "loaders/ModelAssetLoader.h"
#include "loaders/ShaderAssetLoader.h"
#include "log/Log.h"
#include "log/loggers/ConsoleLogger.h"
#include "log/loggers/FileLogger.h"
#include "math/Transform.h"
#include "render/Render.h"


Application::Application() {
    window_ = nullptr;
    world_ = std::make_shared<World>();
}

Application::~Application() = default;

bool Application::initialization() {
    return initGlfw() &&
           initGlew() &&
           initRegisters();
}

void Application::loop() const {
    // test level data
    const auto camera = world_->spawnEntity<CameraEntity>();
    camera->transform->translate(Vector3(0, 0, -8));

    const auto entity = world_->spawnEntity<QuadMeshEntity>();

    const auto entity2 = world_->spawnEntity<QuadMeshEntity>();
    entity2->transform->translate(Vector3(0, 0, -3));
    entity2->transform->rotate(Vector3(35, 0, 20));
    entity2->transform->setScale(Vector3(0.5f));

    const auto entity3 = world_->spawnEntity<QuadMeshEntity>();
    entity3->transform->translate(Vector3(0, 0, -3));
    entity3->transform->setScale(Vector3(0.5f));

    entity2->transform->attachTo(entity->transform);
    entity3->transform->attachTo(entity2->transform);

    float lastTime = 0;
    float currentTime = 0;
    float deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window_)) {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        if (lastTime == 0)
            deltaTime = 0;
        world_->update(deltaTime);
        lastTime = currentTime;
        Render::getInstance().rendering();
        glfwPollEvents();
        glfwSwapBuffers(window_);
    }

    glfwTerminate();
}

bool Application::initGlfw() {
    if (!glfwInit()) {
        LOGE("Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);
    if (!window_) {
        LOGE("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);
    return true;
}

bool Application::initGlew() const {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        LOGE("Failed to initialize GLEW");
        glfwTerminate();
        return false;
    }

    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.2, 0.3, 1);

    return true;
}

bool Application::initRegisters() {
    ASSET_MANAGER.registerAssetLoader<Shader>(std::make_unique<ShaderAssetLoader>());
    ASSET_MANAGER.registerAssetLoader<Model>(std::make_unique<ModelAssetLoader>());

    Log::getInstance().registerLogger(std::make_unique<ConsoleLogger>());
    Log::getInstance().registerLogger(std::make_unique<FileLogger>());

    return true;
}
