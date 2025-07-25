cmake_minimum_required(VERSION 3.20)

project(IMVCORE)

include(FetchContent)

FetchContent_Declare(
    glfw 
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(glfw)

include(FetchContent)

FetchContent_Declare(
    glew 
    GIT_REPOSITORY https://github.com/nigels-com/glew
    GIT_TAG        glew-2.2.0
)
FetchContent_MakeAvailable(glew)

file(GLOB IMV_SOURCES "src/*.cpp")
file(GLOB IMGUI_SOURCES "include/imgui/*.cpp")

include_directories(IMVCORE ./)

add_executable(IMVCORE ${IMV_SOURCES} ${IMGUI_SOURCES})

target_link_libraries(IMVCORE PRIVATE glfw GLEW GL)
