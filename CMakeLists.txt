cmake_minimum_required(VERSION 3.30.9)
project(GameEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)
add_subdirectory(GameEngine)
add_subdirectory(Sandbox)
add_subdirectory(ThirdParty/glfw-3.4)
add_subdirectory(ThirdParty/glad)
add_subdirectory(ThirdParty/glm)
add_subdirectory(ThirdParty/imgui)

target_link_libraries(GameEngine PRIVATE glfw glad OpenGL::GL imgui glm)
