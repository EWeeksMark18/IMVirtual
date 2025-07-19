cmake_minimum_required(VERSION 3.20)

project(IMLCORE)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(IMLCORE ${SOURCES})

target_link_libraries(IMLCORE OpenGL::OpenGL glfw GLEW::GLEW)
