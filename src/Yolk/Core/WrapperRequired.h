#pragma once

namespace Yolk
{
    inline Wrapper::Wrapper(Identifier _id, TypedField::Pointer _field, Memory::MemoryAllocator &_allocator, WrapperType _wtype)
        : ID(_id), field(_field), allocator(_allocator), wType(_wtype)
    {
    }
    inline Wrapper::Wrapper(const Wrapper &cpy)
        : ID(cpy.ID), field(std::make_shared<TypedField>(*cpy.field)), allocator(cpy.allocator), wType(cpy.wType)
    {
        allocator.UpdateViewersCount(ID, +1);
    }
    inline void Wrapper::LookAway()
    {
        allocator.UpdateViewersCount(ID, -1);
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
        allocator.UpdateViewersCount(ID, +1);
        return *this;
    }
}

