#pragma once

#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imgui/imgui_impl_glfw.h"

#include "include/VirtualCPU.hpp"

#include <vector>
#include <string>

struct IMXGUIData
{
    char userCodeLineBuffer[512];
    std::vector<std::string> codeLines;
    std::string memoryText;

    bool bAddLineButtonPressed;
    bool bRunCPUButtonPressed;
    bool bClearMemoryButtonPressed;
};
static IMXGUIData imxGUIData;

class IMXGUIManager
{
public:
    static void Init(GLFWwindow* window);
    static void Close();

    static void LoadFrame();
    static void RenderFrame();

    static void DisplayCodeEditor();
    static void DisplayMemoryViewer(IMVVirtualCPU& _cpu);
};

