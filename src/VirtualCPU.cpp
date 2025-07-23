#include <include/VirtualCPU.hpp>
#include <iostream>

void IMVVirtualCPU::Init()
{
    Reset();

    // Save on disk
    m_MemoryLayout.dataSegment.start =      0x0000;
    m_MemoryLayout.dataSegment.end =        0x0040;
    m_MemoryLayout.codeSegment.start =      0x0040;
    m_MemoryLayout.codeSegment.end =        0x0080;

    // Do not save on disk
    m_MemoryLayout.heapSegment.start =      0x0080;
    m_MemoryLayout.heapSegment.end =        0x0160;
    m_MemoryLayout.stackSegment.start =      0x0160;
    m_MemoryLayout.stackSegment.end =        0x0200;
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
    ExecuteCode();
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

uint8_t IMVVirtualCPU::GetRegisterA()
{
    return m_RegisterA;
}

uint8_t IMVVirtualCPU::GetRegisterB()
{
    return m_RegisterB;
}

void IMVVirtualCPU::WriteRegisterA(uint8_t value)
{
    m_RegisterA = value;
}
    
void IMVVirtualCPU::WriteRegisterB(uint8_t value)
{
    m_RegisterB = value;
}


void IMVVirtualCPU::WriteData(uint16_t address, uint8_t value)
{
    if (address >= m_MemoryLayout.dataSegment.start && address <= m_MemoryLayout.dataSegment.end)
    {
        m_Memory[address] = value;
    }
    else 
    {
        std::cerr << "IMVError: attempt to write data outside of data segment bounds. Segmentation fault.\n";
    }
}

void IMVVirtualCPU::LoadCommandStackIntoMemory()
{
    uint16_t memoryIndex = m_MemoryLayout.codeSegment.start;
    for (auto& command : m_CommandStack)
    {
        if (memoryIndex < m_MemoryLayout.codeSegment.end)
        {
            m_Memory[memoryIndex] = command;
            memoryIndex++;
        }
    }
}

void IMVVirtualCPU::ExecuteCode()
{
    // It's bit strange that I'm writing the data at run time rather than on disk. 
    // Though I need to read more about the data segment anyway.
    uint16_t dataWriteIndex = m_MemoryLayout.dataSegment.start;

    // At some point, I'm probably going to want to make the program counter more global. But this is just to get something up and running ;)
    for (uint16_t programCounter = m_MemoryLayout.codeSegment.start; programCounter < m_MemoryLayout.codeSegment.end; programCounter++)
    {
        uint8_t commandByte = m_Memory[programCounter];
        switch (commandByte)
        {
            // Find a way to better encapsulate these. There's a lot of repeated code, and I don't like that.
            case VASM_LDA:
            {
                uint8_t value = m_Memory[programCounter+1];
                WriteRegisterA(value);
                programCounter += 1;
            } break;
            case VASM_LDB:
            {
                uint8_t value = m_Memory[programCounter+1];
                WriteRegisterB(value);
                programCounter += 1;
            } break;
            case VASM_DB:
            {
                uint8_t value = m_Memory[programCounter+1];

                WriteData(dataWriteIndex, value);

                dataWriteIndex++;
                programCounter += 1;
            } break;
        }
    }
}