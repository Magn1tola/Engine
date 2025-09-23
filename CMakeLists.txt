cmake_minimum_required(VERSION 4.0)
project(Engine)

set(CMAKE_CXX_STANDARD 26)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/core
        ${CMAKE_SOURCE_DIR}/src/core/ec
)

add_executable(Engine src/main.cpp
        src/core/fs/ShaderLoader.cpp
        src/core/fs/ShaderLoader.h
        src/core/EC/Entity.cpp
        src/core/EC/Entity.h
        src/core/EC/EntityComponent.cpp
        src/core/EC/EntityComponent.h
        src/core/EngineObject.cpp
        src/core/EngineObject.h
        src/math/Vector3.cpp
        src/math/Vector3.h
        src/math/Transform.cpp
        src/math/Transform.h
        src/core/World.cpp
        src/core/World.h
        src/render/Render.cpp
        src/render/Render.h
        src/render/Model.cpp
        src/render/Model.h
        src/core/ec/components/MeshComponent.cpp
        src/core/ec/components/MeshComponent.h
        src/core/ec/components/quadMeshComponent.cpp
        src/core/ec/components/quadMeshComponent.h
        src/core/ec/entities/QuadMeshEntity.cpp
        src/core/ec/entities/QuadMeshEntity.h
        src/math/Quaternion.cpp
        src/math/Quaternion.h
        src/math/Matrix4x4.cpp
        src/math/Matrix4x4.h
        src/render/Material.cpp
        src/render/Material.h
        src/render/Shader.cpp
        src/render/Shader.h
        src/core/ec/components/CameraComponent.cpp
        src/core/ec/components/CameraComponent.h
        src/core/ec/entities/CameraEntity.cpp
        src/core/ec/entities/CameraEntity.h
        src/core/ec/WorldComponent.cpp
        src/core/ec/WorldComponent.h
)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

target_include_directories(Engine PRIVATE
        ${GLEW_INCLUDE_DIRS}
        ${glfw3_INCLUDE_DIRS}
)

target_link_libraries(Engine PRIVATE
        ${GLEW_LIBRARIES}
        glfw
)

if (WIN32)
    target_link_libraries(Engine PRIVATE opengl32)
endif ()

add_dependencies(Engine PostBuild)
add_custom_target(PostBuild
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)