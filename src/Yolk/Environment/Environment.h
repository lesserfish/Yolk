#pragma once

#include "../Memory/MemoryManager/MemoryManager.h"
#include "../Object/NewObject.h"
#include <string>

namespace Yolk
{
    class EnvironmentComponent
    {
        public:
        EnvironmentComponent() : MemoryManager(), WrapperTable(MemoryManager) {} 
        protected:
        Memory::MemoryManager MemoryManager;
        Memory::WrapperTable WrapperTable;

    };
    class Environment : public EnvironmentComponent, public Object
    {
        public:
        Environment(std::string Name = "Environment") : Object(Name, MemoryManager, WrapperTable) {}
        ~Environment() {}
    };
}