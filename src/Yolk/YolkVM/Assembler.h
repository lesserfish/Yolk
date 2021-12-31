#pragma once

#include "OVO.h"
#include "YVM.h"
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>
#include <regex>

namespace Yolk
{
    namespace VM
    {
        class Assembler
        {
            public:
            struct Symbol
            {
                int position;
                std::string Name;
            };

            static OVO Assemble(std::string source);
            static OVO::Instruction::INSTRUCTION InstructionFromString(std::string input);
            static std::vector<std::string> CreateSymbolTable(std::vector<std::string>& Lines, std::vector<Symbol>& Table);
            static void SplitLine(std::string Line, std::string &Instruction, std::string& arg1, std::string& arg2);
            static void HandleInput(std::string ins, std::string arg1, std::string arg2, OVO& ovo);
            static OVO::Instruction::ARG HandleArg(std::string , OVO& ovo);
            static void RenderArg(std::string& arg, std::vector<Symbol>& Table);
            static int RegisterFromString(std::string);
            static int TypeFromString(std::string);
            static int PushData(std::string, OVO& );
            static OVO::Instruction::ARG::MODE GetMode(std::string);
        };

        std::vector<std::string> Assembler::CreateSymbolTable(std::vector<std::string>& Lines, std::vector<Symbol>& Table)
        {
            std::vector<std::string> UpdatedLines;
            for(auto Line : Lines)
            {
                char last_character = Line[Line.length() - 1];
                if(last_character == ':')
                {
                    std::string symbol_name = Line.substr(0, Line.length() - 1);
                    int position = UpdatedLines.size();
                    Symbol new_symbol {position, symbol_name};
                    Table.push_back(new_symbol);
                }
                else
                {
                    UpdatedLines.push_back(Line);
                }
            }

            return UpdatedLines;
        }
        void Assembler::SplitLine(std::string Line, std::string &Instruction, std::string& arg1, std::string& arg2)
        {
            int status = 0;

            bool previous_char_was_space = false;
            bool currently_in_parenthesis = false;
            for(auto it = Line.begin(); it != Line.end(); it++)
            {
                if((*it == ' ' || *it == ',') && !currently_in_parenthesis)
                {
                    if(previous_char_was_space)
                        continue;
                    status++;
                    previous_char_was_space = true;
                }
                else
                {
                    if(*it == '\"')
                        currently_in_parenthesis = !currently_in_parenthesis;
                    
                    switch(status)
                    {
                        case 0: Instruction.insert(Instruction.end(), *it); break;
                        case 1: arg1.insert(arg1.end(), *it); break;
                        case 2: arg2.insert(arg2.end(), *it); break;
                    }
                    previous_char_was_space = false;
                }
            }
        }
        void Debug(std::vector<std::string>& Lines, std::vector<Assembler::Symbol>& symbols)
        {
            std::cout << "Lines: \n";
            int i = 0;
            for(auto L : Lines)
            {
                std::cout << i << ": " << L << std::endl;
                i++;
            }

            std::cout << "\nSymbols: \n";

            for(auto s : symbols)
            {
                std::cout << s.position << " - " << s.Name << std::endl;
            }

            std::cout << std::endl;
        }
        OVO Assembler::Assemble(std::string source)
        {
            Memory::MemoryManager manager;

            OVO ovo;
            std::vector<std::string> Lines;

            std::stringstream ss(source);
            std::string to = "";
            while(std::getline(ss, to, '\n'))
            {
                Lines.push_back(to);
            }

            std::vector<Symbol> SymbolTable;
            Lines = CreateSymbolTable(Lines, SymbolTable);

            for(auto Line : Lines)
            {
                //std::cout << "Handling line: " << Line << std::endl;
                std::string lins;
                std::string ar1;
                std::string ar2;
                
                SplitLine(Line, lins, ar1, ar2);
                
                RenderArg(ar1, SymbolTable);
                RenderArg(ar2, SymbolTable);
                
                HandleInput(lins, ar1, ar2, ovo);
            }

            /*std::cout << "Data: \n";
            int i = 0;
            for(auto d : ovo.DataSet)
            {
                std::cout << ".  " << i << ": " <<OVO::Data::ToWrapper(d, manager).field->Print() << std::endl;
                i++;
            }*/
            return ovo;
        }
        OVO::Instruction::ARG::MODE Assembler::GetMode(std::string in)
        {
            int check_reg = RegisterFromString(in);
            if(check_reg >= 0)
                return OVO::Instruction::ARG::MODE::REG;
            
            for(auto it = in.begin(); it != in.end(); it++)
            {
                if(*it == ':')
                {
                    return OVO::Instruction::ARG::MODE::DATA;
                }
            }
            return OVO::Instruction::ARG::MODE::SYMBOL;
        }
        void Assembler::RenderArg(std::string& arg, std::vector<Symbol>& Table)
        {
            for(auto entry : Table)
            {
                if(entry.Name == arg)
                {
                    arg = std::to_string(entry.position);
                    return;
                }
            }
        }
        int Assembler::RegisterFromString(std::string ar)
        {
            std::string arupper = ar;
            std::transform(arupper.begin(), arupper.end(), arupper.begin(), ::toupper);

            if(arupper == "REGA") return 0x0;
            if(arupper == "REGB") return 0x1;
            if(arupper == "REGC") return 0x2;
            if(arupper == "REGD") return 0x3;
            if(arupper == "REGOUT") return 0x4;

            return -1;
        }
        int Assembler::TypeFromString(std::string ar)
        {
            std::string arupper = ar;
            std::transform(arupper.begin(), arupper.end(), arupper.begin(), ::toupper);

            if(arupper == "VOID") return 0x0;
            if(arupper == "I32") return 0x1;
            if(arupper == "U32") return 0x2;
            if(arupper == "I64") return 0x3;
            if(arupper == "U64") return 0x4;
            if(arupper == "FLT") return 0x5;
            if(arupper == "DBL") return 0x6;
            if(arupper == "BOOL") return 0x7;
            if(arupper == "CHAR") return 0x8;
            if(arupper == "UCHAR") return 0x9;
            if(arupper == "STR") return 0xa;

            return -1;
        }
        int Assembler::PushData(std::string in, OVO& ovo)
        {
            std::string type = "";
            auto it = in.begin();
            for(; it != in.end(); it++)
            {
                if(*it == ':')
                {
                    it++;
                    break;
                }
                type.insert(type.end(), *it);
            }
            std::string content = in.substr(it - in.begin(), in.end() - it);

            if(type == "i32")
            {
                int value = std::atoi(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            else if(type == "u32")
            {
                unsigned int value = std::atoi(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            else if(type == "i64")
            {
                long value = std::atol(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            else if(type == "u64")
            {

                unsigned long value = std::atol(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            else if(type == "flt")
            {

                float value = std::atof(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            else if(type == "dbl")
            {
                double value = std::atof(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;

            }
            else if(type == "chr")
            {
                char value =(char) std::atoi(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            else if(type == "uchr")
            {

                unsigned char value =(unsigned char) std::atoi(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            else if(type == "bool")
            {
                
                bool value = (bool) std::atoi(content.c_str());
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;

            }
            else if(type == "str")
            {
                std::string value = content;
                int output = ovo.DataSet.size();
                ovo.DataSet.push_back(OVO::Data::GenerateData(value));
                return output;
            }
            return 0;
        }
        OVO::Instruction::ARG Assembler::HandleArg(std::string ar, OVO& ovo)
        {
            if(ar == "")
            {
                return OVO::Instruction::ARG { OVO::Instruction::ARG::MODE::NONE, 0};
            }
            OVO::Instruction::ARG argout;
            auto mode1 = GetMode(ar);
            
            if(mode1 == OVO::Instruction::ARG::MODE::REG)
            {
                int reg = RegisterFromString(ar);
                argout.mode = mode1;
                argout.value = reg;
            }
            else if(mode1 == OVO::Instruction::ARG::MODE::DATA)
            {
                int data = PushData(ar, ovo);
                argout.mode = mode1;
                argout.value = data;
            }
            else if(mode1 == OVO::Instruction::ARG::MODE::SYMBOL)
            {
                int sym = TypeFromString(ar);
                if(sym < 0)
                {
                    sym = std::atoi(ar.c_str());
                }

                argout.mode = mode1;
                argout.value = sym;

            }

            return argout;
        }
        void Assembler::HandleInput(std::string ins, std::string ar1, std::string ar2, OVO& ovo)
        {
            OVO::Instruction new_instruction;

            new_instruction.instruction = InstructionFromString(ins);
            new_instruction.arg1 = HandleArg(ar1, ovo);
            new_instruction.arg2 = HandleArg(ar2, ovo);

            /*std::cout << ".  Instruction: " <<YVM::GetInstructionName(new_instruction.instruction) << std::endl;
            std::cout << ".  Arg1: " << new_instruction.arg1.mode << " : " << new_instruction.arg1.value << std::endl;
            std::cout << ".  Arg2: " << new_instruction.arg2.mode << " : " << new_instruction.arg2.value << std::endl;
            std::cout << std::endl;*/
            ovo.InstructionSet.push_back(new_instruction);

        }
        OVO::Instruction::INSTRUCTION Assembler::InstructionFromString(std::string input)
        {
            std::transform(input.begin(), input.end(), input.begin(), ::toupper);
            if (input == "MOV")
            {
                return OVO::Instruction::INSTRUCTION::MOV;
            }
            if (input == "CLONE")
            {
                return OVO::Instruction::INSTRUCTION::CLONE;
            }
            if (input == "MOVM")
            {
                return OVO::Instruction::INSTRUCTION::MOVM;
            }
            if (input == "CALLM")
            {
                return OVO::Instruction::INSTRUCTION::CALLM;
            }
            if (input == "PUSHAR")
            {
                return OVO::Instruction::INSTRUCTION::PUSHAR;
            }
            if (input == "POPAR")
            {
                return OVO::Instruction::INSTRUCTION::POPAR;
            }
            if (input == "CLRAR")
            {
                return OVO::Instruction::INSTRUCTION::CLRAR;
            }
            if (input == "PUSH")
            {
                return OVO::Instruction::INSTRUCTION::PUSH;
            }
            if (input == "POP")
            {
                return OVO::Instruction::INSTRUCTION::POP;
            }
            if (input == "CLEAR")
            {
                return OVO::Instruction::INSTRUCTION::CLEAR;
            }
            if (input == "CMP")
            {
                return OVO::Instruction::INSTRUCTION::CMP;
            }
            if (input == "CMPEQ")
            {
                return OVO::Instruction::INSTRUCTION::CMPEQ;
            }
            if (input == "CMPNEQ")
            {
                return OVO::Instruction::INSTRUCTION::CMPNEQ;
            }
            if (input == "CMPLS")
            {
                return OVO::Instruction::INSTRUCTION::CMPLS;
            }
            if (input == "CMPGT")
            {
                return OVO::Instruction::INSTRUCTION::CMPGT;
            }
            if (input == "CMPLSEQ")
            {
                return OVO::Instruction::INSTRUCTION::CMPLSEQ;
            }
            if (input == "CMPGTEQ")
            {
                return OVO::Instruction::INSTRUCTION::CMPGTEQ;
            }
            if (input == "JNTRUE")
            {
                return OVO::Instruction::INSTRUCTION::JNTRUE;
            }
            if (input == "JNFALSE")
            {
                return OVO::Instruction::INSTRUCTION::JNFALSE;
            }
            if (input == "JMP")
            {
                return OVO::Instruction::INSTRUCTION::JMP;
            }
            if (input == "CALL")
            {
                return OVO::Instruction::INSTRUCTION::CALL;
            }
            if (input == "RET")
            {
                return OVO::Instruction::INSTRUCTION::RET;
            }
            if (input == "ADD")
            {
                return OVO::Instruction::INSTRUCTION::ADD;
            }
            if (input == "SUB")
            {
                return OVO::Instruction::INSTRUCTION::SUB;
            }
            if (input == "MUL")
            {
                return OVO::Instruction::INSTRUCTION::MUL;
            }
            if (input == "DIV")
            {
                return OVO::Instruction::INSTRUCTION::DIV;
            }
            if (input == "MOD")
            {
                return OVO::Instruction::INSTRUCTION::MOD;
            }
            if (input == "AND")
            {
                return OVO::Instruction::INSTRUCTION::AND;
            }
            if (input == "OR")
            {
                return OVO::Instruction::INSTRUCTION::OR;
            }
            if (input == "CAST")
            {
                return OVO::Instruction::INSTRUCTION::CAST;
            }
            if (input == "COPY")
            {
                return OVO::Instruction::INSTRUCTION::COPY;
            }
            if (input == "NAMEL")
            {
                return OVO::Instruction::INSTRUCTION::NAMEL;
            }
            if (input == "NAMEG")
            {
                return OVO::Instruction::INSTRUCTION::NAMEG;
            }
            if (input == "BRUP")
            {
                return OVO::Instruction::INSTRUCTION::BRUP;
            }
            if (input == "BRDW")
            {
                return OVO::Instruction::INSTRUCTION::BRDW;
            }
            if (input == "BRHZ")
            {
                return OVO::Instruction::INSTRUCTION::BRHZ;
            }
            if (input == "RSBR")
            {
                return OVO::Instruction::INSTRUCTION::RSBR;
            }
            if (input == "ZERO")
            {
                return OVO::Instruction::INSTRUCTION::ZERO;
            }
            if (input == "HALT")
            {
                return OVO::Instruction::INSTRUCTION::HALT;
            }
            if (input == "NEW")
            {
                return OVO::Instruction::INSTRUCTION::NEW;
            }
            return OVO::Instruction::INSTRUCTION::ZERO;
        }
    }
}
