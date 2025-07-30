#include "include/Assembler.hpp"
#include <map>
#include <iostream>
#include <regex>

static std::map<std::string, uint8_t> translationTable;

void IMXAssembler::LoadTranslationTable()
{
    translationTable["START"] = VASM_START;
    translationTable["END"] = VASM_END;
    translationTable["LDA"] = VASM_LDA;
    translationTable["LDB"] = VASM_LDB;
    translationTable["STA"] = VASM_STA;
    translationTable["STB"] = VASM_STB;
    translationTable["DB"] = VASM_DB;
}

std::vector<uint8_t> IMXAssembler::Assemble(std::vector<std::string> codeLines)
{
    LoadTranslationTable();

    std::string fullCode;
    for (auto& codeLine : codeLines)
        fullCode.append(codeLine + " ");
    
    std::cout << fullCode << "\n";

    std::regex re(R"(\b([A-Za-z]+|\d+)\b)");
    auto codeBegin = std::sregex_iterator(fullCode.begin(), fullCode.end(), re);
    auto codeEnd = std::sregex_iterator();

    std::vector<uint8_t> commandBuffer;

    for (std::sregex_iterator i = codeBegin; i != codeEnd; ++i)
    {
        try {
            commandBuffer.emplace_back(std::stoi(i->str()));
        } catch (std::invalid_argument) {
            commandBuffer.emplace_back(translationTable[i->str()]);
        }
        std::cout << i->str() << "\n";
    }

    return commandBuffer;
}