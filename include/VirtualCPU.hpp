#pragma once
#include <array>
#include <vector>
#include <cstdint>
#include <cstring>

#define IMVCPU_MEMORY_MAX 1024


class IMVVirtualCPU
{
public:
    void Init();
    void Reset();

    void Run();

    void LoadCommands(std::vector<uint8_t> commands);
private:
    std::array<uint8_t, IMVCPU_MEMORY_MAX> m_Memory; 
    std::vector<uint8_t> m_CommandStack;

    uint8_t m_RegisterA;
    uint8_t m_RegisterB;

    void LoadCommandStackIntoMemory();
};