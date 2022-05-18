#pragma once

#include "../Common.h"
#include <unordered_map>

namespace Yolk
{
    namespace Memory
    {
        class MemMap {
            private:
            MemMap(const MemMap&) = delete;
            MemMap(MemMap&) = delete;
            public:

            struct AllocateOut {
                AllocateOut(bool o, Wrapper w) : ok(o), wrapper(w) {}
                bool ok;
                Wrapper wrapper;
            };

            MemMap();
            ~MemMap();

            template<typename T> AllocateOut AllocateMemory();
            template<typename T> AllocateOut AllocateMemory(T value);

            AllocateOut CreateCopy(Wrapper other);
            
            Viewers UpdateViewersCount(Identifier id, Viewers diff);
            Viewers ViewersCount(Identifier id);

            bool Exists(Identifier id);
            Wrapper Get(Identifier id);
            
            private:

            Wrapper VoidWrapper;
            std::unordered_map<Identifier, AbstractData::Pointer> AllocatedMemory;
        };
        MemMap::MemMap() : VoidWrapper(0, nullptr, *this){

        }
        MemMap::~MemMap(){

        }

        template<typename T> MemMap::AllocateOut MemMap::AllocateMemory(){
            constexpr bool canCreate = requires() {
                new DynamicData<T>();
            };
            constexpr bool canFree = requires(){
                free(new DynamicData<T>());
            };
            if constexpr(canCreate && canFree){
                AbstractData::Pointer dptr = std::make_shared<DynamicData<T>>();


                T& ref = dynamic_pointer_cast<DynamicData<T>>(dptr)->Get();
                TypedField::Pointer tfptr(ref);
                Identifier id = dptr->ID();

                AllocatedMemory.insert(std::pair(id, dptr));
                Wrapper wrapper(id, tfptr, *this);
                
                return AllocateOut(true, wrapper);
            }
            return AllocateOut(false, VoidWrapper);
        }
        template<typename T> MemMap::AllocateOut MemMap::AllocateMemory(T value){
            constexpr bool canCreate = requires() {
                new DynamicData<T>(value);
            };
            constexpr bool canFree = requires(){
                free(new DynamicData<T>(value));
            };
            if constexpr(canCreate && canFree){
                AbstractData::Pointer dptr = std::make_shared<DynamicData<T>>(value);


                T& ref = dynamic_pointer_cast<DynamicData<T>>(dptr)->Get();
                TypedField::Pointer tfptr(ref);
                Identifier id = dptr->ID();

                AllocatedMemory.insert(std::pair(id, dptr));
                Wrapper wrapper(id, tfptr, *this);
                
                return AllocateOut(true, wrapper);
            }
            return AllocateOut(false, VoidWrapper);
        }

        MemMap::AllocateOut MemMap::CreateCopy(Wrapper other){
            auto copyattempt = other.field->CopyByValue();
            if(!copyattempt.ok){
                return AllocateOut(false, VoidWrapper);
            }

            Identifier id = copyattempt.datapointer->ID();
            AllocatedMemory.insert(std::pair(id, copyattempt.datapointer));

            Wrapper wrapper(id, copyattempt.field, *this);
            return AllocateOut(true, wrapper); 
        }
        
        Viewers MemMap::UpdateViewersCount(Identifier , Viewers ){
            return 0;
        }
        Viewers MemMap::ViewersCount(Identifier ){
            return 0;
        }

        bool MemMap::Exists(Identifier ){
            return false;
        }
        Wrapper MemMap::Get(Identifier ) {
            return Wrapper(-1, nullptr, *this);
        }
    }
}