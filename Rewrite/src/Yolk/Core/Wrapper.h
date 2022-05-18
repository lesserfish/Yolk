#pragma once

#include "../Common.h"
#include <typeindex>
#include <memory>

namespace Yolk
{
    namespace Memory
    {
        class MemoryManager;
    }
    
    enum class WrapperType
    {
        FieldWrapper,
        MethodWrapper
    };

    class Wrapper
    {
    protected:

    public:
        using Pointer = std::shared_ptr<Wrapper>;
        
        virtual ~Wrapper();
        Wrapper(const Wrapper &copy);
        Wrapper(Identifier _ID, TypedField::Pointer _field, Memory::MemoryManager &manager, WrapperType _wtype = WrapperType::FieldWrapper);
        Wrapper &operator=(const Wrapper &copy);

        Identifier ID;
        TypedField::Pointer field;
        Memory::MemoryManager& manager;
        WrapperType wType;

    protected:
        void LookAway();

    private:
        Wrapper(Memory::MemoryManager &_manager) : manager(_manager){}
    };
}
