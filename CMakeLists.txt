cmake_minimum_required(VERSION 4.0.0)

project(VulkanTest VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(VulkanTest
	src/main.cpp
)

target_include_directories(VulkanTest
	PRIVATE
	dependencies
)

target_link_libraries(VulkanTest
    glfw
	Vulkan::Vulkan
)
