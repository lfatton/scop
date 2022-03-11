cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(scop)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(scop srcs/main.cpp)

set(VULKAN_PATH "C:/VulkanSDK/1.3.204.1")
set(ENV{VULKAN_SDK} ${VULKAN_PATH})
find_package(Vulkan REQUIRED)
target_link_libraries(scop ${Vulkan_LIBRARIES})
target_include_directories(scop PUBLIC "${VULKAN_PATH}/Include")


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.3.6)
target_link_libraries(scop glfw)