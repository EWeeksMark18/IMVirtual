#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imgui/imgui_impl_glfw.h"

#include <vector>

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

struct IMXEditorData
{
    char userCodeLineBuffer[512];
    std::vector<std::string> codeLines;

    bool bAddLineButtonPressed;
};
static IMXEditorData imxEditorData;

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
        
        ImGui::InputText("##", imxEditorData.userCodeLineBuffer, sizeof(imxEditorData.userCodeLineBuffer));
        ImGui::Text("%s", imxEditorData.userCodeLineBuffer);

        imxEditorData.bAddLineButtonPressed = ImGui::Button("Add line");
        if (imxEditorData.bAddLineButtonPressed)
            imxEditorData.codeLines.emplace_back(std::string(imxEditorData.userCodeLineBuffer));

        for (std::string& codeLine : imxEditorData.codeLines)
            ImGui::Text("%s", codeLine.c_str());

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