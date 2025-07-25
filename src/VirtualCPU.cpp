#include <include/VirtualCPU.hpp>
#include <iostream>

void IMVCPU::Init()
{
    Reset();

    // Save on disk
    m_ProcessLayout.programLayout.dataSegment.start =       0x0000;
    m_ProcessLayout.programLayout.dataSegment.end =         0x0040;
    m_ProcessLayout.programLayout.codeSegment.start =       0x0040;
    m_ProcessLayout.programLayout.codeSegment.end =         0x0080;

    // Do not save on disk
    m_ProcessLayout.heapSegment.start =                     0x0080;
    m_ProcessLayout.heapSegment.end =                       0x0160;
    m_ProcessLayout.stackSegment.start =                    0x0160;
    m_ProcessLayout.stackSegment.end =                      0x0200;
}

void IMVCPU::Reset()
{
    m_RegisterA = 0x00;
    m_RegisterB = 0x00;
    m_ProgramCounter = 0x00;
    std::memset(m_Memory.data(), 0x00, m_Memory.size() * sizeof(uint8_t));
    m_CommandStack.clear();
}

void IMVCPU::Run()
{
    LoadCommandStackIntoMemory();
    ExecuteCode();
}

void IMVCPU::LoadCommands(std::vector<uint8_t> commands)
{
    for (auto& command : commands)
        m_CommandStack.emplace_back(command);
}

std::array<uint8_t, IMVCPU_MEMORY_MAX> IMVCPU::GetMemory()
{
    return m_Memory;
}

uint8_t IMVCPU::GetRegisterA()
{
    return m_RegisterA;
}

uint8_t IMVCPU::GetRegisterB()
{
    return m_RegisterB;
}

void IMVCPU::WriteRegisterA(uint8_t value)
{
    m_RegisterA = value;
}
    
void IMVCPU::WriteRegisterB(uint8_t value)
{
    m_RegisterB = value;
}


void IMVCPU::WriteData(uint16_t address, uint8_t value)
{
    if (address >= m_ProcessLayout.programLayout.dataSegment.start && address <= m_ProcessLayout.programLayout.dataSegment.end)
    {
        WriteMemory(address, value);
    }
    else 
    {
        std::cerr << "IMVError: attempt to write data outside of data segment bounds. Segmentation fault.\n";
    }
}

void IMVCPU::WriteMemory(uint16_t address, uint8_t value)
{
    m_Memory[address] = value;
}

uint8_t IMVCPU::ReadMemory(uint16_t address)
{
    return m_Memory[address];
}

void IMVCPU::LoadCommandStackIntoMemory()
{
    uint16_t memoryIndex = m_ProcessLayout.programLayout.codeSegment.start;
    for (auto& command : m_CommandStack)
    {
        if (memoryIndex < m_ProcessLayout.programLayout.codeSegment.end)
        {
            m_Memory[memoryIndex] = command;
            memoryIndex++;
        }
    }
}

void IMVCPU::ExecuteCode()
{
    // It's bit strange that I'm writing the data at run time rather than on disk. 
    // Though I need to read more about the data segment anyway.
    uint16_t dataWriteIndex = m_ProcessLayout.programLayout.dataSegment.start;

    // Start the program at 0x0000 in virtual memory
    m_ProgramCounter = m_ProcessLayout.programLayout.codeSegment.start;

    while (m_ProgramCounter <= m_ProcessLayout.programLayout.codeSegment.end)
    {
        /* [COMMANDBYTE] [VALUEBYTE0] [VALUEBYTE1] */
        uint8_t commandByte =   ReadMemory(m_ProgramCounter);
        uint8_t valueByte0 =    ReadMemory(m_ProgramCounter+1);
        uint8_t valueByte1 =    ReadMemory(m_ProgramCounter+2);

        // Create 16 bit address from two 8 bit operands
        uint16_t valueAddress = (uint16_t)(valueByte0 << 8)+(uint16_t)(valueByte1);

        switch (commandByte)
        {
            // Find a way to better encapsulate these. There's a lot of repeated code, and I don't like that.
            case VASM_LDA:
            {
                WriteRegisterA(valueByte0);
                m_ProgramCounter++;
            } break;
            case VASM_LDB:
            {
                WriteRegisterB(valueByte0);
                m_ProgramCounter++;
            } break;
            case VASM_STA:
            {
                WriteMemory(valueAddress, GetRegisterA());
                m_ProgramCounter += 2;
            } break;
            case VASM_STB:
            {
                WriteMemory(valueAddress, GetRegisterB());
                m_ProgramCounter += 2;
            } break;
            case VASM_DB:
            {
                WriteData(dataWriteIndex, valueByte0);
                dataWriteIndex++;
                m_ProgramCounter++;
            } break;
        }
        m_ProgramCounter++;
    }
}