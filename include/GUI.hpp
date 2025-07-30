#pragma once

#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include "include/imgui/imgui_impl_glfw.h"

#include "include/VirtualCPU.hpp"

#include <vector>
#include <string>

struct IMGUIData
{
    char codeLineTXTBF[512];
    std::vector<std::string> codeLines;

    std::string memoryDisplayTXTOUT;

    char programNameTXTBF[128];

    bool bAddLineButtonPressed;
    bool bRunCPUButtonPressed;
    bool bClearMemoryButtonPressed;
    bool bSaveProgramPressed;
};
static IMGUIData imxGUIData;

class IMGUIManager
{
public:
    static void Init(GLFWwindow* window);
    static void Close();

    static void LoadFrame();
    static void RenderFrame();

    static void DisplayCodeEditor();
    static void DisplayMemoryViewer(IMVCPU& _cpu);
};

