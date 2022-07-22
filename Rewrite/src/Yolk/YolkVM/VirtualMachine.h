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
            OUTOFBOUNDS,
            ERROR
        };

        class VirtualMachine 
        {
            public:
                VirtualMachine(Memory::DynamicMemory& mem, Memory::MemoryInterface* meminterface);
                friend class Instruction;
                Wrapper& SelectRegister(uint64_t);
                MethodWrapper& SelectMethodRegister() {return regm;}
                Memory::DynamicMemory& GetMemory() {return memory;};
                Memory::MemoryInterface* GetInterface() {return currentInterface; }
                WrapperArgument& SelectArgumentRegister() {return regarg;}
                WrapperArgument& SelectStack() {return stack;}
                bool& SelectCmpRegister() {return regcmp; }
                void UpdateInterface(Memory::MemoryInterface* interface) {currentInterface = interface;}
                void ResetInterface() {currentInterface = baseInterface;}
                void Jump(uint64_t position) {ip = position;}
                uint64_t GetPosition() {return ip;}
                void Halt() {status = Status::HALTED;}
                virtual std::string SelectText(uint64_t);
            protected:
                Memory::DynamicMemory& memory;
                
                Memory::MemoryInterface* baseInterface;
                Memory::MemoryInterface* currentInterface;
                Ovo ovo;

                Status status;

                Wrapper rega;
                Wrapper regb;
                Wrapper regc;
                Wrapper regd;
                Wrapper regout;
                MethodWrapper regm;
                bool regcmp;
                WrapperArgument regarg;
                WrapperArgument stack;
                uint64_t ip;
        };
        
    }
}
