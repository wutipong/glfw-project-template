cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

# set the project name
project(glfw-project-template)

# add the executable
add_executable(main 
	"main.cpp"
	"scene.hpp" "scene.cpp" 
	"io_util.hpp"
    "shader.hpp" "shader.cpp")

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(main PRIVATE 
    imgui::imgui 
    glfw 
    GLEW::GLEW 
    spdlog::spdlog 
    spdlog::spdlog_header_only)

target_compile_features(main PRIVATE cxx_std_20)
set_property(TARGET main PROPERTY CXX_STANDARD 20)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "shaders/*.frag"
    "shaders/*.vert"
)

add_custom_target(SHADER_COMPILE 
    SOURCES ${GLSL_SOURCE_FILES} 
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/shaders/"
    COMMAND ${CMAKE_COMMAND} -E copy ${GLSL_SOURCE_FILES} "${CMAKE_CURRENT_BINARY_DIR}/shaders/"
)

add_dependencies(main SHADER_COMPILE)