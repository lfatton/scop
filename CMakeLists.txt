cmake_minimum_required(VERSION 3.21)

# set the project name and version
project(scop)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(scop srcs/main.cpp libs/glad.c srcs/Environment.cpp srcs/utils.cpp)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} includes)

target_link_libraries(scop ${OPENGL_LIBRARIES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.3.6)
target_link_libraries(scop glfw)