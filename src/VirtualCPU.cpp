#include <include/VirtualCPU.hpp>
#include <iostream>

void IMVVirtualCPU::Init()
{
    Reset();
    LoadCommandStackIntoMemory();
    std::cout << "M:" << (int)m_Memory[0] << " " << (int)m_Memory[1] << "\n";
}

void IMVVirtualCPU::Reset()
{
    m_RegisterA = 0x00;
    m_RegisterB = 0x00;
    std::memset(m_Memory.data(), 0x00, m_Memory.size() * sizeof(uint8_t));
}

void IMVVirtualCPU::Run()
{

}

void IMVVirtualCPU::LoadCommands(std::vector<uint8_t> commands)
{
    for (auto& command : commands)
        m_CommandStack.emplace_back(command);
}

void IMVVirtualCPU::LoadCommandStackIntoMemory()
{
    uint16_t memoryIndex;
    for (auto& command : m_CommandStack)
    {
        if (memoryIndex < IMVCPU_MEMORY_MAX)
        {
            m_Memory[memoryIndex] = command;
            memoryIndex++;
        }
    }
}