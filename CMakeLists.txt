cmake_minimum_required(VERSION 3.20)

project(IMVCORE)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB IMV_SOURCES "src/*.cpp")
file(GLOB IMGUI_SOURCES "include/imgui/*.cpp")

include_directories(IMVCORE ./)

add_executable(IMVCORE ${IMV_SOURCES} ${IMGUI_SOURCES})

target_link_libraries(IMVCORE OpenGL::GL glfw GLEW::GLEW)
