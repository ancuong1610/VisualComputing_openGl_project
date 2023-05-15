cmake_minimum_required(VERSION 3.0)
project(OpenGL_Praktikum)

set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" src/Game/Cube.h)
set(INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src")

##-------------------------------add your source files here-------------------------------------------------------------
##        new source paths must be added to the include list, if contained headers are used elsewhere!
## Framework/Assets
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/AssetManager.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/AssetManager.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/ShaderProgram.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets/ShaderProgram.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Assets")

## Framework/Rendering
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering/Primitives.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering/Primitives.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/Rendering")
## Framework/SceneElements
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Transform.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements/Transform.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Framework/SceneElements")
## Window
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Window.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Window.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Scene.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game/Scene.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/src/Game")

##---------------------------------framework files----------------------------------------------------------------------
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/CommonTypes.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/fw_config.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/OpenGLWindow.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/OpenGLWindow.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/glerror.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/glerror.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/Input.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/Input.cpp")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/libheaders.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/OBJLoader.h")
list(APPEND SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/framework/OBJLoader.cpp")
# add that directory to include list:
list(APPEND INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/framework")

##--------------------------------external dependencies-----------------------------------------------------------------
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs")

##--------------------------------executable target---------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL_Praktikum ${SOURCES})
target_include_directories(
        OpenGL_Praktikum
        PRIVATE ${INCLUDES}
)

target_link_libraries(OpenGL_Praktikum PUBLIC cga2fw_external_dependencies)

##-------------------------------copy assets to output------------------------------------------------------------------

file(COPY "assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")