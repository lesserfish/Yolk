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
                VirtualMachine(Memory::MemoryAllocator& mem, Memory::MemoryInterface* meminterface);
                Wrapper& SelectRegister(uint64_t);
                virtual std::string SelectText(uint64_t);

                // Inline Methods
                MethodWrapper& SelectMethodRegister() {return regm;}
                Memory::MemoryAllocator& GetAllocator() {return allocator;};
                Memory::MemoryInterface* GetInterface() {return currentInterface; }
                WrapperArgument& SelectArgumentRegister() {return regarg;}
                WrapperArgument& SelectStack() {return stack;}
                bool& SelectCmpRegister() {return regcmp; }
                uint64_t GetPosition() const {return ip;}
                void UpdateInterface(Memory::MemoryInterface* interface) {currentInterface = interface;}
                void ResetInterface() {currentInterface = baseInterface;}
                void Jump(uint64_t position) {ip = position;}
                void Halt() {status = Status::HALTED;}
            protected:
                Memory::MemoryAllocator& allocator;
                
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
