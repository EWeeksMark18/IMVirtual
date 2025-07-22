#include <include/VirtualCPU.hpp>
#include <iostream>

void IMVVirtualCPU::Init()
{
    Reset();

    // Do some further initialization (for the future)
}

void IMVVirtualCPU::Reset()
{
    m_RegisterA = 0x00;
    m_RegisterB = 0x00;
    std::memset(m_Memory.data(), 0x00, m_Memory.size() * sizeof(uint8_t));
    m_CommandStack.clear();
}

void IMVVirtualCPU::Run()
{
    LoadCommandStackIntoMemory();
}

void IMVVirtualCPU::LoadCommands(std::vector<uint8_t> commands)
{
    for (auto& command : commands)
        m_CommandStack.emplace_back(command);
}

std::array<uint8_t, IMVCPU_MEMORY_MAX> IMVVirtualCPU::GetMemory()
{
    return m_Memory;
}

void IMVVirtualCPU::LoadCommandStackIntoMemory()
{
    uint16_t memoryIndex = 0;
    for (auto& command : m_CommandStack)
    {
        if (memoryIndex < IMVCPU_MEMORY_MAX)
        {
            m_Memory[memoryIndex] = command;
            memoryIndex++;
        }
    }
}