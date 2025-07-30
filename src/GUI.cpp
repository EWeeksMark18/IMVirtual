#include "include/GUI.hpp"

#include <cstring>
#include <sstream>
#include <iomanip>


void IMGUIManager::Init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void IMGUIManager::Close()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void IMGUIManager::LoadFrame()
{
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}
    
void IMGUIManager::RenderFrame()
{
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IMGUIManager::DisplayCodeEditor()
{
    ImGui::Begin("Editor");

    ImGui::InputText("##", imxGUIData.codeLineTXTBF, sizeof(imxGUIData.codeLineTXTBF));
    ImGui::Text("%s", imxGUIData.codeLineTXTBF);

    imxGUIData.bAddLineButtonPressed = ImGui::Button("Add line");
    if (imxGUIData.bAddLineButtonPressed)
        imxGUIData.codeLines.emplace_back(std::string(imxGUIData.codeLineTXTBF));

    for (std::string& codeLine : imxGUIData.codeLines)
        ImGui::Text("%s", codeLine.c_str());

    ImGui::End();
}

void IMGUIManager::DisplayMemoryViewer(IMVCPU& _cpu)
{
    ImGui::Begin("Memory");

    int rowIndex = 0;
    const int rowLength = 32;
    for (int i = 0; i < 512; i++)
    {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)_cpu.GetMemory()[i];
        imxGUIData.memoryDisplayTXTOUT.append(ss.str());
        rowIndex++;
        if (rowIndex > rowLength)
        {
            rowIndex = 0;
            imxGUIData.memoryDisplayTXTOUT.append("\n");
        }
    }

    ImGui::Text("%s", imxGUIData.memoryDisplayTXTOUT.c_str());
    imxGUIData.memoryDisplayTXTOUT.clear();

    ImGui::Text("A: %02X", _cpu.GetRegisterA());
    ImGui::Text("B: %02X", _cpu.GetRegisterB());

    ImGui::InputText("Program name", imxGUIData.programNameTXTBF, sizeof(imxGUIData.programNameTXTBF));

    imxGUIData.bRunCPUButtonPressed = ImGui::Button("Run CPU");
    if (imxGUIData.bRunCPUButtonPressed)
    {
        _cpu.ReadProgramFromFileToMemory(std::string(imxGUIData.programNameTXTBF));
        _cpu.Run();
    }
    imxGUIData.bClearMemoryButtonPressed = ImGui::Button("Clear memory");
    if (imxGUIData.bClearMemoryButtonPressed)
    {
        _cpu.Reset();
    }
    imxGUIData.bSaveProgramPressed = ImGui::Button("Save Program");
    if (imxGUIData.bSaveProgramPressed)
    {
        _cpu.SaveCurrentProgramToFile(std::string(imxGUIData.programNameTXTBF));
    }

    ImGui::End();
}