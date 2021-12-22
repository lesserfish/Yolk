#pragma once

#include "../Wrapper/Wrapper.h"
#include "../Wrapper/MethodWrapper.h"
#include "../Wrapper/ArgumentWrapper.h"
#include "../Memory/Memory/MemoryBlock.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include <unordered_map>

namespace Yolk
{
    namespace VM
    {
        class OVO
        {
            public:
            struct Instruction
            {
                using DPOS = unsigned int;
                using IPOS = unsigned int;
            
                enum class INSTRUCTION
                {
                    MOVA,
                    MOVB,
                    MOVC,
                    MOVD,
                    PUSHARG,
                    CLEARARG,
                    MOVMET,
                    JMP,
                    CALL
                };
                struct ARG
                {
                    enum MODE
                    {
                        DATA,
                        REG
                    };
                    MODE mode;
                    DPOS arg;
                };
                INSTRUCTION i;
                ARG arg1;
                ARG arg2;
            };
            
            
            using DATA = std::unordered_map<DPOS, std::string>;
            using CODE = std::unordered_map<IPOS, Instruction>;


            DATA data;
            CODE code;
        };
        class YVM
        {
            using IPOS = OVO::IPOS;
            using DPOS = OVO::DPOS;

            public:
            YVM(Memory::MemoryManager& _manager) : manager(_manager), memoryBlock(manager, "YVM") {}

            public:

            bool Execute(OVO ovo);

            private:
/*
            bool ExecuteInstruction(OVO::Data& , OVO::Instruction instruction);
            // Instructions:
            Wrapper 
            Wrapper GETWRP(DPOS position, bool& result);
            MethodWrapper GETMET(DPOS position, bool& result);
            void MOVA(Wrapper wrapper); // Moves wrapper to Register A
            void MOVB(Wrapper wrapper); // Moves wrapper to Register B
            void MOVC(Wrapper wrapper); // Moves wrapper to Register C
            void MOVD(Wrapper wrapper); // Moves wrapper to Register D
            void PUSHARG(Wrapper wrapper); // Pushes wrapper to Argumentwrapper
            void CLEARARG(); // Clears argumentwrapper
            void MOVMET(MethodWrapper wrapper); // Moves method wrapper to Method wrapper register
            void CALL(); // Invokes the method wrapper with the Argument wrapper
            void JMP(IPOS position); // Jumps to instruction given by position
            void JMPEQA(Wrapper, IPOS position); // Jumps to instruction given by position if wrapper is equal to register A
            void JMPEQB(Wrapper, IPOS position); // Jumps to instruction given by position if wrapper is equal to register B
            void JMPEQC(Wrapper, IPOS position), // Jumps to instruction given by position if wrapper is equal to register C
            void JMPEQD(Wrapper, IPOS position); // Jumps to instruction given by position if wrapper is equal to register D
            void JMPLESSA(Wrapper, IPOS position); // Jumps to instruction given by position if wrapper is less than register A
            void JMPLESSB(Wrapper, IPOS position); // Jumps to instruction given by position if wrapper is less than register B
            void JMPLESSC(Wrapper, IPOS position); // Jumps to instruction given by position if wrapper is less than register C
            void JMPLESSD(Wrapper, IPOS position); // Jumps to instruction given by position if wrapper is less than register D
            // void JMPGRTA....
            void ADDA(Wrapper); // Adds Wrapper to Register A
            void ADDB(Wrapper); // Adds Wrapper to Register B
            void ADDC(Wrapper); // Adds Wrapper to Register C
            void ADDD(Wrapper); // Adds Wrapper to Register D
            void EXIT(); // Returns

            */
            private:

            // 
            // Memory Manager
            Memory::MemoryManager& manager;
            // Memory Block
            Memory::MemoryBlock stackMemory; // <- Stores scoped variables

            // Registers
            Wrapper rega;
            Wrapper regb;
            Wrapper regc;
            Wrapper regd;
            ArgumentWrapper argreg;
            MethodWrapper metrega;

        };
    }
}