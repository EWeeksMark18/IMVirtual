#pragma once
#include <vector>
#include <string>
#include <cstdint>

#define VASM_START 0x11
#define VASM_END 0xFF

#define VASM_LDA 0x30
#define VASM_LDB 0x31 

#define VASM_STA 0x40
#define VASM_STB 0x41

#define VASM_DB 0x60


class IMXAssembler 
{
public:
    static void LoadTranslationTable();

    static std::vector<uint8_t> Assemble(std::vector<std::string> codeLines);
};