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
                std::string SelectText(uint64_t);
                inline Memory::MemoryInterface* GetInterface() {return memoryInterface; }
                Memory::DynamicMemory& GetMemory() {return memory;};
            private:
                Memory::DynamicMemory& memory;
                
                Memory::MemoryInterface* memoryInterface;
                Ovo ovo;

                Wrapper rega;
                Wrapper regb;
                Wrapper regc;
                Wrapper regd;
                Wrapper regout;
                MethodWrapper regm;
                bool regcmp;
                WrapperArgument regarg;
                std::deque<Wrapper> stack;
                std::vector<Ovo::Code>::iterator ip;
        };
        
    }
}
