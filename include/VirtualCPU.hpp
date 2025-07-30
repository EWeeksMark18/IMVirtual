#pragma once
#include <array>
#include <vector>
#include <cstdint>
#include <cstring>
#include <string>


#include "Commands.hpp"

#define IMVCPU_MEMORY_MAX 0x400

struct IMVCPUMemorySegment
{
    uint16_t start;
    uint16_t end;
};

struct IMVCPUProgramLayout
{
    IMVCPUMemorySegment dataSegment;
    IMVCPUMemorySegment codeSegment;
};

class IMVCPU
{
public:
    void Init();
    void Reset();

    void Run();
    void LoadCommands(std::vector<uint8_t> commands);

    void SaveCurrentProgramToFile(const std::string& filePath);
    void ReadProgramFromFileToMemory(const std::string& filePath);

    std::array<uint8_t, IMVCPU_MEMORY_MAX> GetMemory();
    uint8_t GetRegisterA();
    uint8_t GetRegisterB();
private:
    std::array<uint8_t, IMVCPU_MEMORY_MAX> m_Memory; 
    std::vector<uint8_t> m_CommandStack;

    IMVCPUProgramLayout m_ProgramLayout;

    uint8_t m_RegisterA;
    uint8_t m_RegisterB;

    uint16_t m_ProgramCounter;

    void WriteRegisterA(uint8_t value);
    void WriteRegisterB(uint8_t value);

    void WriteData(uint16_t address, uint8_t value);

    void WriteMemory(uint16_t address, uint8_t value);
    uint8_t ReadMemory(uint16_t address);

    void LoadCommandStackIntoMemory();
    void ExecuteCode();
};