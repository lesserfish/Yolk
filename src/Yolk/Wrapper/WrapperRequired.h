#pragma once

#include "../Memory/MemoryManager/MemoryManager.h"

namespace Yolk
{
    inline Wrapper::Wrapper(Wrapper::Identifier _id, TypedField::Pointer _field, Memory::MemoryManager &_manager, WrapperType _wtype)
        : ID(_id), field(_field), manager(_manager), wType(_wtype)
    {
    }
    inline Wrapper::Wrapper(const Wrapper &cpy)
        : ID(cpy.ID), field(std::make_shared<TypedField>(*cpy.field)), manager(cpy.manager), wType(cpy.wType)
    {
            manager.ChangeAudience(ID, +1);
    }
    inline void Wrapper::LookAway()
    {
        manager.ChangeAudience(ID, -1);
    }
    inline Wrapper::~Wrapper()
    {
        /*if(field)
            field->Free();*/
        LookAway();
    }
    inline Wrapper &Wrapper::operator=(const Wrapper &cpy)
    {
        if(cpy.manager.Name() == manager.Name())
        {
            LookAway();
            ID = cpy.ID;
            field = std::make_shared<TypedField>(*cpy.field);
            wType = cpy.wType;
            manager.ChangeAudience(ID, +1);
            return *this;
        }
        return *this;
    }
}