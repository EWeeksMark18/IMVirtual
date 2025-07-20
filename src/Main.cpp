#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imgui/imgui_impl_glfw.h"

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

    if (glewInit() != GLEW_OK)
        std::cerr << "Could not initialize GLEW\n";


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Editor");
        ImGui::Text("Hello.");
        ImGui::End();

        ImGui::EndFrame();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}