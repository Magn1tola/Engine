cmake_minimum_required(VERSION 4.0)
project(Engine)

set(CMAKE_CXX_STANDARD 26)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/core
        ${CMAKE_SOURCE_DIR}/src/core/ec
)

add_executable(Engine src/main.cpp
        src/core/ec/Entity.cpp
        src/core/ec/Entity.h
        src/core/ec/EntityComponent.cpp
        src/core/ec/EntityComponent.h
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
        src/core/ec/components/QuadMeshComponent.cpp
        src/core/ec/components/QuadMeshComponent.h
        src/core/ec/entities/QuadMeshEntity.cpp
        src/core/ec/entities/QuadMeshEntity.h
        src/math/Quaternion.cpp
        src/math/Quaternion.h
        src/math/Matrix4x4.cpp
        src/math/Matrix4x4.h
        src/render/Shader.cpp
        src/render/Shader.h
        src/core/ec/components/CameraComponent.cpp
        src/core/ec/components/CameraComponent.h
        src/core/ec/entities/CameraEntity.cpp
        src/core/ec/entities/CameraEntity.h
        src/core/ec/WorldComponent.cpp
        src/core/ec/WorldComponent.h
        src/core/fs/AssetManager.cpp
        src/core/fs/AssetManager.h
        src/core/fs/Asset.cpp
        src/core/fs/Asset.h
        src/core/fs/AssetLoader.cpp
        src/core/fs/AssetLoader.h
        src/core/fs/ShaderAssetLoader.cpp
        src/core/fs/ShaderAssetLoader.h
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if (WIN32)
    find_package(GLEW REQUIRED)
    target_link_libraries(Engine PRIVATE
            OpenGL::GL
            glfw
            ${GLEW_LIBRARIES}
    )
elseif (UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLEW REQUIRED glew)
    target_link_libraries(Engine PRIVATE
            OpenGL::GL
            glfw
            ${GLEW_LIBRARIES}
            GLU
            dl
            pthread
            X11
    )
endif()

target_include_directories(Engine PRIVATE
        ${GLEW_INCLUDE_DIRS}
)

add_custom_target(PostBuild ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Copying assets"
)

add_dependencies(Engine PostBuild)
