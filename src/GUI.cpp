#include "include/GUI.hpp"

#include <cstring>
#include <sstream>
#include <iomanip>


void IMXGUIManager::Init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void IMXGUIManager::Close()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void IMXGUIManager::LoadFrame()
{
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}
    
void IMXGUIManager::RenderFrame()
{
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IMXGUIManager::DisplayCodeEditor()
{
    ImGui::Begin("Editor");

    ImGui::InputText("##", imxGUIData.userCodeLineBuffer, sizeof(imxGUIData.userCodeLineBuffer));
    ImGui::Text("%s", imxGUIData.userCodeLineBuffer);

    imxGUIData.bAddLineButtonPressed = ImGui::Button("Add line");
    if (imxGUIData.bAddLineButtonPressed)
        imxGUIData.codeLines.emplace_back(std::string(imxGUIData.userCodeLineBuffer));

    for (std::string& codeLine : imxGUIData.codeLines)
        ImGui::Text("%s", codeLine.c_str());

    ImGui::End();
}

void IMXGUIManager::DisplayMemoryViewer(IMVVirtualCPU& _cpu)
{
    ImGui::Begin("Memory");

    int rowIndex = 0;
    const int rowLength = 32;
    for (int i = 0; i < 512; i++)
    {
        std::stringstream ss;
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)_cpu.GetMemory()[i];
        imxGUIData.memoryText.append(ss.str());
        rowIndex++;
        if (rowIndex > rowLength)
        {
            rowIndex = 0;
            imxGUIData.memoryText.append("\n");
        }
    }

    ImGui::Text("%s", imxGUIData.memoryText.c_str());
    imxGUIData.memoryText.clear();

    imxGUIData.bRunCPUButtonPressed = ImGui::Button("Run CPU");
    if (imxGUIData.bRunCPUButtonPressed)
    {
        // At some point, I want to read whatever program the user wants from disk.
        _cpu.LoadCommands(
            {
                VASM_START,

                VASM_DB, 0xFF,
                VASM_DB, 0x05,

                VASM_END
            }
        );
        _cpu.Run();
    }
    imxGUIData.bClearMemoryButtonPressed = ImGui::Button("Clear memory");
    if (imxGUIData.bClearMemoryButtonPressed)
    {
        _cpu.Reset();
    }

    ImGui::End();
}