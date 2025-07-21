#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/VirtualCPU.hpp"

#include <vector>
#include <array>
#include <thread>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <iomanip>

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
static IMXWindowData imxWindowData = {800, 400, "IMLEmulator"};

struct IMXUIEditorData
{
    char userCodeLineBuffer[512];
    std::vector<std::string> codeLines;

    bool bAddLineButtonPressed;
};
static IMXUIEditorData imxEditorData;

struct IMXUIMemoryViewerData
{
    std::string memoryText;
};
static IMXUIMemoryViewerData imxuiMemoryViewerData;

struct IMVCPUMemorySegment
{
    uint16_t start;
    uint16_t end;
};

struct IMVCPUMemoryLayout
{
    IMVCPUMemorySegment codeSegment;
    IMVCPUMemorySegment dataSegment;
    IMVCPUMemorySegment heapSegment;
    IMVCPUMemorySegment stackSegment;
};



void IMXDisplayCodeEditor()
{
    ImGui::Begin("Editor");

    ImGui::InputText("##", imxEditorData.userCodeLineBuffer, sizeof(imxEditorData.userCodeLineBuffer));
    ImGui::Text("%s", imxEditorData.userCodeLineBuffer);

    imxEditorData.bAddLineButtonPressed = ImGui::Button("Add line");
    if (imxEditorData.bAddLineButtonPressed)
        imxEditorData.codeLines.emplace_back(std::string(imxEditorData.userCodeLineBuffer));

    for (std::string& codeLine : imxEditorData.codeLines)
        ImGui::Text("%s", codeLine.c_str());

    ImGui::End();
}

void IMXDisplayVCPUMemory()
{
    ImGui::Begin("Memory");

    int rowIndex = 0;
    const int rowLength = 32;
    for (int i = 0; i < 512; i++)
    {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << 0x00;
        imxuiMemoryViewerData.memoryText.append(ss.str());
        rowIndex++;
        if (rowIndex > rowLength)
        {
            rowIndex = 0;
            imxuiMemoryViewerData.memoryText.append("\n");
        }
    }

    ImGui::Text("%s", imxuiMemoryViewerData.memoryText.c_str());
    imxuiMemoryViewerData.memoryText.clear();

    ImGui::End();
}

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

    IMVVirtualCPU vCPU;
    vCPU.LoadCommands({0x88, 0xFF});
    vCPU.Init();


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        vCPU.Run();

        IMXDisplayCodeEditor();
        IMXDisplayVCPUMemory();

        ImGui::EndFrame();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    vCPU.Reset();


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}