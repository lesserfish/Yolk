#pragma once

#include "OVO.h"
#include "Operators.h"
#include "../Wrapper/Wrapper.h"
#include "../Wrapper/MethodWrapper.h"
#include "../Wrapper/ArgumentWrapper.h"
#include "../Memory/Memory/MemoryBlock.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include "Operators.h"
#include <unordered_map>
#include <string>

namespace Yolk
{
    namespace VM
    {
        class YVM
        {
        public:
            // Structrs

            enum class Status
            {
                RUNNING,
                HALTED,
                ERROR,
                COMPLETED
            };
            struct DataOutput
            {
                OVO::Data data;
                bool ok;
            };

        public:
            
            // Functions:

            // Constructor

            YVM(Memory::MemoryManager &_manager, Memory::WrapperTable &_wrapperTable);
            
            // Instructions

            void I_MOV(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_COPY(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_CLONE(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_MOVM(OVO::Instruction::ARG arg1);
            void I_CALLM();
            void I_PUSHAR(OVO::Instruction::ARG arg1);
            void I_POPAR(OVO::Instruction::ARG arg1);
            void I_CLRAR();
            void I_CMP(OVO::Instruction::ARG arg1);
            void I_CMPEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_CMPNEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_CMPLS(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_CMPGT(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_CMPLSEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_CMPGTEQ(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_JNTRUE(OVO::Instruction::ARG arg1);
            void I_JNFALSE(OVO::Instruction::ARG arg1);
            void I_JMP(OVO::Instruction::ARG arg1);
            void I_ADD(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_SUB(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_MUL(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_DIV(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_MOD(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_AND(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_OR(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_CAST(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_RECAST(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_NAMEL(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_NAMEG(OVO::Instruction::ARG arg1, OVO::Instruction::ARG arg2);
            void I_BRUP();
            void I_BRDW();
            void I_BRHR(OVO::Instruction::ARG arg1);
            void I_RSBR();
            void I_ZERO();
            void I_HALT();

            // API

            


            
            // Helper Functions
            
            void Debug();
            void ThrowException(int status, std::string Message);
            DataOutput RetrieveData(OVO::Instruction::CHUNK id);
            bool SelectRegister(OVO::Instruction::CHUNK chunk, Wrapper *&ref);
            bool ValidInstruction(OVO::Usize position);
            void JumpToInstruction(OVO::Usize position);

            // Data:
            
            // Internal Data
            
            bool Running;
            Status status;
            std::string Message;           

            // API Data

            OVO ovo;                         // Algorithm we are going to be running
            Memory::SymbolTable *symTable;   // Symbol Table of the object requesting the algorithm to be run.
            Memory::SymbolTable *workingSymTable; // 
            
            // Memory
            Memory::MemoryManager &manager;     // Needed so we can create new wrappers
            Memory::WrapperTable &wrapperTable; // Needed so we can register and delete wrappers
            Operator opHandler;                 // Needed so we can perform operations between elementary types.

            // Registers
            Wrapper rega;           // Wrapper Register A
            Wrapper regb;           // Wrapper Register B
            Wrapper regc;           // Wrapper Register C
            Wrapper regd;           // Wrapper Register D
            Wrapper regout;         // Wrapper Register for Method Output
            MethodWrapper mreg;     // Method Wrapper Register
            bool cmpreg;            // Comparison Register
            ArgumentWrapper argreg; // Argument Wrapper Register
            std::deque<OVO::Instruction>::iterator instructionPointer; // InstructionPointer
        };
    }
}