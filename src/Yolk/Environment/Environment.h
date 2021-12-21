#pragma once

#include "../Memory/MemoryManager/MemoryManager.h"
#include "../Object/Object.h"
#include <string>

namespace Yolk
{
    class EnvironmentComponent
    {
        protected:
        Memory::MemoryManager MemoryManager;
    };
    class Environment : public EnvironmentComponent, public Object
    {
        public:
        Environment(std::string Name = "Environment") : Object(Name, MemoryManager) {}
        ~Environment() {}
    };
}