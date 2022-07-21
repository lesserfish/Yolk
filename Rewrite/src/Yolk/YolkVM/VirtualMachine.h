#pragma once


#include "../Memory/Memory.h"
#include "../Core/Core.h"
#include "OVO.h"

namespace Yolk
{
    namespace VM
    {
        enum class Status : uint8_t {
            RUNNING,
            HALTED,
            ERROR
        };

        class VirtualMachine 
        {
            public:
                friend class Instruction;
                Wrapper& SelectRegister(uint64_t);
                MethodWrapper& SelectMethodRegister() {return regm;}
                WrapperArgument& SelectArgumentRegister() {return regarg;}
                WrapperArgument& SelectStack() {return stack;}
                bool& SelectCmpRegister() {return regcmp; }
                std::string SelectText(uint64_t);
                inline Memory::MemoryInterface* GetInterface() {return currentInterface; }
                void UpdateInterface(Memory::MemoryInterface* );
                void ResetInterface();
                void Halt();
                Memory::DynamicMemory& GetMemory() {return memory;};
                void Jump(uint64_t);
                uint64_t GetPosition() const;
            private:
                Memory::DynamicMemory& memory;
                
                Memory::MemoryInterface* currentInterface;
                Memory::MemoryInterface* baseInterface;
                Ovo ovo;

                Wrapper rega;
                Wrapper regb;
                Wrapper regc;
                Wrapper regd;
                Wrapper regout;
                MethodWrapper regm;
                bool regcmp;
                WrapperArgument regarg;
                WrapperArgument stack;
                std::vector<Ovo::Code>::iterator ip;
        };
        
    }
}
