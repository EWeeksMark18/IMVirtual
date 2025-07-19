#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


/*
IMVirtual


Interpretive Machine Virtual

- Fictional/Virtual CPU
- Pixel graphics
- Interpretive Language (similar to 6502 assembly but alos similar to scripting languages like Lua)
- File loading
- Memory architecture

- OpenGL
- GLFW
- ImGui
- Multithreading
- C++ fstream


*/

struct IMXWindowData 
{
    int width, height;
    const char* title;
};
static IMXWindowData imxWindowData = {400, 400, "IMLEmulator"};

int main()
{
    std::cout << "Hello IMVirtual!\n";


    if (!glfwInit())
        std::cerr << "Could not initialize GLFW\n";

    GLFWwindow* window = glfwCreateWindow(imxWindowData.width, imxWindowData.height, imxWindowData.title, NULL, NULL);

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}