#pragma once

#include "OVO.h"
#include "../Wrapper/Wrapper.h"
#include "../Wrapper/MethodWrapper.h"
#include "../Wrapper/ArgumentWrapper.h"
#include "../Memory/Memory/MemoryBlock.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include "Operators.h"
#include <unordered_map>

namespace Yolk
{
    namespace VM
    {
        class YVM
        {
            public:
            YVM(Memory::MemoryManager& _manager);

            public:

            // Memory Manager
            Memory::MemoryManager& manager;
            
            // Memory Block
            Memory::MemoryBlock stackMemory; // <- Stores scoped variables

            // Registers
            Wrapper rega;               // Wrapper Register A
            Wrapper regb;               // Wrapper Register B
            Wrapper regc;               // Wrapper Register C
            Wrapper regd;               // Wrapper Register D
            Wrapper regout;             // Wrapper Register for Method Output
            MethodWrapper mreg;         // Method Wrapper Register
            ArgumentWrapper argreg;     // Argument Wrapper Register
            bool compreg;               // Comparison Register
            
        };

        inline YVM::YVM(Memory::MemoryManager& _manager) : 
                manager(_manager), 
                stackMemory(manager, "YVM"),
                rega(manager.GenerateVoidWrapper()),
                regb(manager.GenerateVoidWrapper()),
                regc(manager.GenerateVoidWrapper()),
                regd(manager.GenerateVoidWrapper()),
                regout(manager.GenerateVoidWrapper()),
                mreg(manager.GenerateVoidWrapper()),
                argreg(),
                compreg(false)
        {}
    }
}