cmake_minimum_required(VERSION 3.21)

# set the project name and version
project(scop)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(scop srcs/main.cpp libs/glad.c srcs/App.cpp srcs/render/GlfwHandler.cpp srcs/render/Shader.cpp srcs/libmath/Vector4.cpp srcs/libmath/Vector4.hpp srcs/libmath/Matrix.cpp srcs/libmath/Matrix.hpp srcs/utils.cpp srcs/utils.hpp srcs/render/Camera.cpp srcs/render/Camera.hpp srcs/render/Obj.cpp srcs/render/Obj.hpp srcs/render/Obj.hpp srcs/libmath/Vector3.cpp srcs/libmath/Vector3.hpp srcs/libmath/Vector2.cpp srcs/libmath/Vector2.hpp)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} includes)

target_link_libraries(scop ${OPENGL_LIBRARIES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.3.6)
target_link_libraries(scop glfw)