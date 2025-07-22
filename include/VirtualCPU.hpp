#pragma once
#include <array>
#include <vector>
#include <cstdint>
#include <cstring>

#include "Commands.hpp"

#define IMVCPU_MEMORY_MAX 1024

struct IMVCPUMemorySegment
{
    uint16_t start;
    uint16_t end;
};

struct IMVCPUMemoryLayout
{
    IMVCPUMemorySegment codeSegment;
    IMVCPUMemorySegment dataSegment;
    IMVCPUMemorySegment heapSegment;
    IMVCPUMemorySegment stackSegment;
};

class IMVVirtualCPU
{
public:
    void Init();
    void Reset();

    void Run();

    void LoadCommands(std::vector<uint8_t> commands);

    std::array<uint8_t, IMVCPU_MEMORY_MAX> GetMemory();
private:
    std::array<uint8_t, IMVCPU_MEMORY_MAX> m_Memory; 
    std::vector<uint8_t> m_CommandStack;

    uint8_t m_RegisterA;
    uint8_t m_RegisterB;

    void LoadCommandStackIntoMemory();
};