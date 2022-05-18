#pragma once

namespace Yolk
{
    inline Wrapper::Wrapper(Identifier _id, TypedField::Pointer _field, Memory::MemMap &_manager, WrapperType _wtype)
        : ID(_id), field(_field), manager(_manager), wType(_wtype)
    {
    }
    inline Wrapper::Wrapper(const Wrapper &cpy)
        : ID(cpy.ID), field(std::make_shared<TypedField>(*cpy.field)), manager(cpy.manager), wType(cpy.wType)
    {
        manager.UpdateViewersCount(ID, +1);
    }
    inline void Wrapper::LookAway()
    {
        manager.UpdateViewersCount(ID, -1);
    }
    inline Wrapper::~Wrapper()
    {
        LookAway();
    }
    inline Wrapper &Wrapper::operator=(const Wrapper &cpy)
    {
        LookAway();
        ID = cpy.ID;
        field = std::make_shared<TypedField>(*cpy.field);
        wType = cpy.wType;
        manager.UpdateViewersCount(ID, +1);
        return *this;
    }
}