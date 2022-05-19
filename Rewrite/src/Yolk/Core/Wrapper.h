#pragma once

#include "../Common.h"
#include <typeindex>
#include <memory>

namespace Yolk
{
    namespace Memory
    {
        class DynamicMemory;
    }
    
    enum class WrapperType
    {
        FieldWrapper,
        MethodWrapper
    };

    class Wrapper
    {
    public:
        using Pointer = std::shared_ptr<Wrapper>;
        
        virtual ~Wrapper();
        Wrapper(const Wrapper &copy);
        Wrapper(Identifier _ID, TypedField::Pointer _field, Memory::DynamicMemory &memory, WrapperType _wtype = WrapperType::FieldWrapper);
        Wrapper &operator=(const Wrapper &copy);

        Identifier ID;
        TypedField::Pointer field;
        Memory::DynamicMemory& memory;
        WrapperType wType;

    protected:
        void LookAway();

    private:
        Wrapper(Memory::DynamicMemory &_memory) : memory(_memory){}
    };
}
