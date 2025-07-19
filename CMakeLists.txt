cmake_minimum_required(VERSION 3.20)

project(IMVCORE)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(IMVCORE ${SOURCES})

target_link_libraries(IMVCORE OpenGL::OpenGL glfw GLEW::GLEW)
