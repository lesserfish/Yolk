#include "OVO.h"
#include "Instruction.h"
#include "../Exceptions.h"
#include <algorithm>
#include <cstdint>
#include <string>

namespace Yolk
{
    namespace VM
    {
        OPCode OPFromString(std::string input)
        {
            std::transform(input.begin(), input.end(), input.begin(), ::toupper);
            for(auto it = AllOPCodes.begin(); it != AllOPCodes.end(); it++)
            {
                auto instruction = Instruction::Select(*it);
                std::string asstring = instruction->to_string();

                if(input.compare(asstring) == 0)
                {
                    return *it;
                }
            }
            throw Exceptions::Exception("Could not find instruction with name " + input);
        }
        RegisterType RegisterTypeFromString(std::string input)
        {
            std::transform(input.begin(), input.end(), input.begin(), ::toupper);
            if(input.compare("REGA") == 0) { return RegisterType::REGA; }
            else if(input.compare("REGB") == 0) { return RegisterType::REGB; }
            else if(input.compare("REGC") == 0) { return RegisterType::REGC; }
            else if(input.compare("REGD") == 0) { return RegisterType::REGD; }
            else if(input.compare("REGOUT") == 0) { return RegisterType::REGOUT; }
            else if(input.compare("REGM") == 0) { return RegisterType::REGM; }
            else if(input.compare("RECMP") == 0) { return RegisterType::RECMP; }
            throw Yolk::Exceptions::Exception(input + " is not a valid Register.");
        }
        std::string RegisterTypeToString(RegisterType type) {
            switch(type)
            {
                case RegisterType::REGA: { return "REGA"; }
                case RegisterType::REGB: { return "REGB"; }
                case RegisterType::REGC: { return "REGC"; }
                case RegisterType::REGD: { return "REGD"; }
                case RegisterType::REGOUT: { return "REGOUT"; }
                case RegisterType::REGM: { return "REGM"; }
                case RegisterType::RECMP: { return "RECMP"; }
            }
        }
        std::string ArgumentValueToString(ArgType type, uint64_t value)
        {
            switch(type) {
                case VM::ArgType::ELEMENTARY: {
                                                  return ElementaryToString(static_cast<EType>(value));
                                              }
                case VM::ArgType::REGISTER: {
                                                return RegisterTypeToString(static_cast<RegisterType>(value));
                                            }
                case VM::ArgType::NAME: {
                                            return std::to_string(value);
                                        }
                case VM::ArgType::NONE: {
                                            return std::to_string(0);
                                        }
                case VM::ArgType::CHAR: {
                                            char ascast;
                                            std::memcpy(&ascast, &value, sizeof(char));
                                            return std::to_string(ascast);
                                            return std::to_string(static_cast<char>(value));
                                        }
                case VM::ArgType::DOUBLE: {
                                              double ascast;
                                              std::memcpy(&ascast, &value, sizeof(double));
                                              return std::to_string(ascast);
                                          }
                case VM::ArgType::FLOAT: {
                                             float ascast;
                                             std::memcpy(&ascast, &value, sizeof(float));
                                             return std::to_string(ascast);
                                         }
                case VM::ArgType::INT32: {
                                             int32_t ascast;
                                             std::memcpy(&ascast, &value, sizeof(int32_t));
                                             return std::to_string(ascast);
                                         }
                case VM::ArgType::INT64:{ 
                                            int64_t ascast;
                                            std::memcpy(&ascast, &value, sizeof(int64_t));
                                            return std::to_string(ascast);
                                        }
                case VM::ArgType::UINT32:{  
                                             uint32_t ascast;
                                             std::memcpy(&ascast, &value, sizeof(uint32_t));
                                             return std::to_string(ascast);
                                         }
                case VM::ArgType::UINT64:{   
                                             uint64_t ascast;
                                             std::memcpy(&ascast, &value, sizeof(uint64_t));
                                             return std::to_string(ascast);
                                         }
                case VM::ArgType::VOID:  {
                                             return std::to_string(0);
                                         }
                case VM::ArgType::STRING:{
                                             return std::to_string(value);
                                         }
            }
        }
        std::string ElementaryToString(EType type)
        {
            switch(type){
                case VM::EType::INT32: { return "INT32"; }
                case VM::EType::UINT32: { return "UINT32"; }
                case VM::EType::INT64: { return "INT64"; }
                case VM::EType::UINT64: { return "UINT64"; }
                case VM::EType::FLOAT: { return "FLOAT"; }
                case VM::EType::DOUBLE: { return "DOUBLE"; }
                case VM::EType::CHAR: { return "CHAR"; }
                case VM::EType::STRING: { return "STRING"; }
                case VM::EType::VOID: { return "VOID"; }
            }
        }
        EType ElementaryFromString(std::string input)
        {
            std::transform(input.begin(), input.end(), input.begin(), ::toupper);
            if(input.compare("INT32") == 0) { return EType::INT32; }
            else if(input.compare("UINT32") == 0) { return EType::UINT32; }
            else if(input.compare("INT64") == 0) { return EType::INT64; }
            else if(input.compare("UINT64") == 0) { return EType::UINT64; }
            else if(input.compare("FLOAT") == 0) { return EType::FLOAT; }
            else if(input.compare("DOUBLE") == 0) { return EType::DOUBLE; }
            else if(input.compare("CHAR") == 0) { return EType::CHAR; }
            else if(input.compare("STRING") == 0) { return EType::STRING; }
            else if(input.compare("VOID") == 0) { return EType::VOID; }
            return EType::FLOAT;
        }
        std::string ArgTypeToString(ArgType atype)
        {
            switch(atype) {
                case ArgType::REGISTER: { return "REGISTER"; }
                case ArgType::NAME: { return "NAME"; }
                case ArgType::INT32: { return "INT32"; }
                case ArgType::INT64: { return "INT64"; }
                case ArgType::UINT32: { return "UINT32"; }
                case ArgType::UINT64: { return "UINT64"; }
                case ArgType::FLOAT: { return "FLOAT"; }
                case ArgType::DOUBLE: { return "DOUBLE"; }
                case ArgType::CHAR: { return "CHAR"; }
                case ArgType::STRING: { return "STRING"; }
                case ArgType::VOID: { return "VOID"; }
                case ArgType::ELEMENTARY: { return "ELEMENTARY"; }
                case ArgType::NONE: { return "NONE"; }
            }
        }
        std::string OPToString(OPCode op){
            switch(op)
            {
                case OPCode::MOV: { return "MOV"; }
                case OPCode::COPY: { return "COPY"; }
                case OPCode::CLONE: { return "CLONE"; }
                case OPCode::NEW: { return "NEW"; }
                case OPCode::MOVM: { return "MOVM"; }
                case OPCode::CALLM: { return "CALLM"; }
                case OPCode::PUSHAR: { return "PUSHAR"; }
                case OPCode::POPAR: { return "POPAR"; }
                case OPCode::CLRAR: { return "CLRAR"; }
                case OPCode::PUSH: { return "PUSH"; }
                case OPCode::POP: { return "POP"; }
                case OPCode::CLEAR: { return "CLEAR"; }
                case OPCode::CMP: { return "CMP"; }
                case OPCode::CMPEQ: { return "CMPEQ"; }
                case OPCode::CMPNEQ: { return "CMPNEQ"; }
                case OPCode::CMPLS: { return "CMPLS"; }
                case OPCode::CMPGT: { return "CMPGT"; }
                case OPCode::CMPLSEQ: { return "CMPLSEQ"; }
                case OPCode::CMPGTEQ: { return "CMPGTEQ"; }
                case OPCode::JNTRUE: { return "JNTRUE"; }
                case OPCode::JNFALSE: { return "JNFALSE"; }
                case OPCode::JMP: { return "JMP"; }
                case OPCode::CALL: { return "CALL"; }
                case OPCode::RET: { return "RET"; }
                case OPCode::ADD: { return "ADD"; }
                case OPCode::SUB: { return "SUB"; }
                case OPCode::MUL: { return "MUL"; }
                case OPCode::DIV: { return "DIV"; }
                case OPCode::MOD: { return "MOD"; }
                case OPCode::AND: { return "AND"; }
                case OPCode::OR: { return "OR"; }
                case OPCode::CAST: { return "CAST"; }
                case OPCode::NAME: { return "NAME"; }
                case OPCode::NAMEG: { return "NAMEG"; }
                case OPCode::BRUP: { return "BRUP"; }
                case OPCode::BRDW: { return "BRDW"; }
                case OPCode::BRHZ: { return "BRHZ"; }
                case OPCode::RSBR: { return "RSBR"; }
                case OPCode::ZERO: { return "ZERO"; }
                case OPCode::HALT: { return "HALT"; }
            };

        }
    }
}
