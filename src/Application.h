//
// Created by Magnitola on 19.10.2025.
//

#pragma once
#include <memory>
#include <GL/glew.h> //glew must be included before glfw
#include <GLFW/glfw3.h>


class World;

class Application {
public:
    Application();

    ~Application();

    bool initialization();

    void loop() const;

private:
    GLFWwindow *window_ = nullptr;
    std::shared_ptr<World> world_;

    bool initGlfw();

    bool initGlew() const;

    static bool initRegisters();
};
