cmake_minimum_required(VERSION 4.0)
project(Engine)

set(CMAKE_CXX_STANDARD 26)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/assetManager
        ${CMAKE_SOURCE_DIR}/src/core
        ${CMAKE_SOURCE_DIR}/src/core/entityComponent
)

set(ENGINE_MODULES
        core
        math
        render
        assetManager
        reflection
        log
        utils
)

function(get_module_sources module_name output_var)
    file(GLOB_RECURSE MODULE_SRCS
            "src/${module_name}/*.cpp"
            "src/${module_name}/*.h"
    )
    set(${output_var} ${MODULE_SRCS} PARENT_SCOPE)
endfunction()

set(ALL_SRCS src/main.cpp)
foreach (module IN LISTS ENGINE_MODULES)
    get_module_sources(${module} MODULE_SRCS)
    list(APPEND ALL_SRCS ${MODULE_SRCS})
endforeach ()

add_executable(Engine ${ALL_SRCS})

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
endif ()

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
