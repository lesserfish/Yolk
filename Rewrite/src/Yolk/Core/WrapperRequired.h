#pragma once

namespace Yolk
{
    inline Wrapper::Wrapper(Identifier _id, TypedField::Pointer _field, Memory::DynamicMemory &_memory, WrapperType _wtype)
        : ID(_id), field(_field), memory(_memory), wType(_wtype)
    {
    }
    inline Wrapper::Wrapper(const Wrapper &cpy)
        : ID(cpy.ID), field(std::make_shared<TypedField>(*cpy.field)), memory(cpy.memory), wType(cpy.wType)
    {
        memory.UpdateViewersCount(ID, +1);
    }
    inline void Wrapper::LookAway()
    {
        memory.UpdateViewersCount(ID, -1);
    }
    inline Wrapper::~Wrapper()
    {
        LookAway();
    }
    inline Wrapper& Wrapper::operator=(const Wrapper &cpy)
    {
        LookAway();
        ID = cpy.ID;
        field = std::make_shared<TypedField>(*cpy.field);
        wType = cpy.wType;
        memory.UpdateViewersCount(ID, +1);
        return *this;
    }
}

