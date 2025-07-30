#include "include/GUI.hpp"

#include <cstring>
#include <sstream>
#include <iomanip>

#include "include/Assembler.hpp"


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

    ImGui::InputText("##", imGUIData.codeLineTXTBF, sizeof(imGUIData.codeLineTXTBF));
    ImGui::Text("%s", imGUIData.codeLineTXTBF);

    imGUIData.bAddLineButtonPressed = ImGui::Button("Add line");
    if (imGUIData.bAddLineButtonPressed)
        imGUIData.codeLines.emplace_back(std::string(imGUIData.codeLineTXTBF));

    for (std::string& codeLine : imGUIData.codeLines)
        ImGui::Text("%s", codeLine.c_str());

    imGUIData.bAssembleCodeButtonPressed = ImGui::Button("Assemble Code");
    if (imGUIData.bAssembleCodeButtonPressed)
    {
        imGUIData.assembledCode = IMXAssembler::Assemble(imGUIData.codeLines);
    }
    imGUIData.bWipeCodeButtonPressed = ImGui::Button("Wipe Code");
    if (imGUIData.bWipeCodeButtonPressed)
    {
        imGUIData.assembledCode.clear();
        imGUIData.codeLines.clear();
        //std::memset(imGUIData.assembledCode.data(), 0, sizeof(uint8_t) * imGUIData.assembledCode.size());
        //std::memset(imGUIData.codeLines.data(), 0, sizeof(std::string) * imGUIData.codeLines.size());
    }

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
        imGUIData.memoryDisplayTXTOUT.append(ss.str());
        rowIndex++;
        if (rowIndex > rowLength)
        {
            rowIndex = 0;
            imGUIData.memoryDisplayTXTOUT.append("\n");
        }
    }

    ImGui::Text("%s", imGUIData.memoryDisplayTXTOUT.c_str());
    imGUIData.memoryDisplayTXTOUT.clear();

    ImGui::Text("A: %02X", _cpu.GetRegisterA());
    ImGui::Text("B: %02X", _cpu.GetRegisterB());

    ImGui::InputText("Program name", imGUIData.programNameTXTBF, sizeof(imGUIData.programNameTXTBF));

    imGUIData.bRunCPUButtonPressed = ImGui::Button("Run CPU");
    if (imGUIData.bRunCPUButtonPressed)
    {
        //_cpu.ReadProgramFromFileToMemory(std::string(imGUIData.programNameTXTBF));
        _cpu.LoadCommands(imGUIData.assembledCode);
        _cpu.Run();
    }
    imGUIData.bClearMemoryButtonPressed = ImGui::Button("Clear memory");
    if (imGUIData.bClearMemoryButtonPressed)
    {
        _cpu.Reset();
    }
    imGUIData.bSaveProgramPressed = ImGui::Button("Save Program");
    if (imGUIData.bSaveProgramPressed)
    {
        _cpu.SaveCurrentProgramToFile(std::string(imGUIData.programNameTXTBF));
    }

    ImGui::End();
}