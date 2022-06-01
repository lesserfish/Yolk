#pragma once

#include "../Core/Core.h"

namespace Yolk
{
    namespace Memory
    {

        class MemoryInterface
        {

        public:
            bool RegisterWrapper(Wrapper wrapper, std::string Name);
            bool RegisterMethodWrapper(MethodWrapper wrapper, std::string Name);
            bool RegisterMemoryPointer(MemoryInterface*, std::string);

            void Delete(std::string Name);
            void UnlinkMemoryPointer(MemoryInterface*);

            WrapperOut GetWrapper(std::string);
            MethodWrapperOut GetMethodWrapper(std::string);
            MemoryPointerOut GetMemoryPointer(std::string);
            SymbolValue::Type GetType(std::string);

            SymbolTableInterface& GetSymbolTableInterface();
            MemoryTable& GetMemoryTable();

            MemoryInterface(DynamicMemory& _memory);
            ~MemoryInterface();

        private:
            DynamicMemory& memory;
            MemoryTable memoryTable;
            SymbolTableInterface symbolTableInterface;
        };
    }
}
