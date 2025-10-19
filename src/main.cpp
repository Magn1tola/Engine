#define GLEW_STATIC

#include "Application.h"


int main() {
    Application app{};
    if (!app.initialization()) {
        return -1;
    }

    app.loop();
    return 0;
}