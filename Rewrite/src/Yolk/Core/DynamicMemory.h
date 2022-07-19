#pragma once


#include "../Exceptions.h"
#include "../Common.h"
#include <unordered_map>
#include <string>

namespace Yolk
{
    namespace Memory
    {
        class DynamicMemory {
            private:
            DynamicMemory(const DynamicMemory&) = delete;
            DynamicMemory(DynamicMemory&) = delete;
            public:

            DynamicMemory();
            ~DynamicMemory();
            
            Wrapper GetVoidWrapper();

            template<typename T> Wrapper AllocateMemory();
            template<typename T> Wrapper AllocateMemory(T value);
            template<typename T> Wrapper CreateWrapper(T& value);
            Wrapper CreateCopy(Wrapper other);
            
            Viewers UpdateViewersCount(Identifier id, Viewers diff);
            Viewers ViewersCount(Identifier id);

            bool Exists(Identifier id);
            unsigned int Size() const;
            
            void Debug(std::string in = "") {
                std::cout << "Debug: \n:";
                std::cout << in << std::endl;
                for(auto m = AllocatedMemory.begin(); m != AllocatedMemory.end(); m++)
                {
                    std::cout << "  -";
                    m->second->Debug();
                    std::cout << std::endl;
                }
                std::cout << std::endl << std::endl;
            }
            private:

            std::unordered_map<Identifier, AbstractData::Pointer> AllocatedMemory;
            Wrapper VoidWrapper;
        };
        inline DynamicMemory::DynamicMemory() : AllocatedMemory(), VoidWrapper(0, TypedField::Pointer(new TypedField), *this){}
        inline DynamicMemory::~DynamicMemory(){
        }

        inline Wrapper DynamicMemory::GetVoidWrapper(){
            return VoidWrapper;
        }
        template<typename T> inline Wrapper DynamicMemory::AllocateMemory(){
            constexpr bool canCreate = requires() {
                new DynamicData<T>();
            };
            constexpr bool canFree = requires(){
                delete(new DynamicData<T>());
            };
            if constexpr(canCreate && canFree){
                AbstractData::Pointer dptr = std::make_shared<DynamicData<T>>();


                T& ref = dynamic_pointer_cast<DynamicData<T>>(dptr)->Get();
                TypedField::Pointer tfptr(new TypedField(ref));
                Identifier id = dptr->ID();

                AllocatedMemory.insert(std::pair(id, dptr));
                Wrapper wrapper(id, tfptr, *this);
                
                return wrapper;
            }
            throw Exceptions::Exception("Failed to allocated memory.");
        }
        template<typename T> inline Wrapper DynamicMemory::AllocateMemory(T value){
            constexpr bool canCreate = requires() {
                new DynamicData<T>(value);
            };
            constexpr bool canFree = requires(){
                delete(new DynamicData<T>(value));
            };
            if constexpr(canCreate && canFree){
                AbstractData::Pointer dptr = std::make_shared<DynamicData<T>>(value);


                T& ref = dynamic_pointer_cast<DynamicData<T>>(dptr)->Get();
                TypedField::Pointer tfptr(new TypedField(ref));
                Identifier id = dptr->ID();
                AllocatedMemory.insert(std::pair(id, dptr));
                Wrapper wrapper(id, tfptr, *this);
                
                return wrapper;
            }
            throw Exceptions::Exception("Failed to allocated memory.");
        }
        template<typename T> inline Wrapper DynamicMemory::CreateWrapper(T& value){
            TypedField::Pointer tfptr(new TypedField(value));
            Identifier id = MEMID::Next();
            Wrapper wrapper(id, tfptr, *this);

            return wrapper;
        }

        inline Wrapper DynamicMemory::CreateCopy(Wrapper other){
            try{
                auto copyattempt = other.field->CopyByValue();
                Identifier id = copyattempt.datapointer->ID();
                AllocatedMemory.insert(std::pair(id, copyattempt.datapointer));

                Wrapper wrapper(id, copyattempt.field, *this);
                return wrapper; 
            }catch(const Exceptions::Exception &exception)
            {
                throw exception;
            }
            
        }
        
        inline Viewers DynamicMemory::UpdateViewersCount(Identifier id, Viewers diff){
            auto it = AllocatedMemory.find(id);
            if(it == AllocatedMemory.end()){
                return 0;
            }

            int updatedScore = it->second->UpdateViewersCount(diff);
            if(updatedScore == 0){
                it->second->Debug();
                AllocatedMemory.erase(it);
            }
            return updatedScore;
        }
        inline Viewers DynamicMemory::ViewersCount(Identifier id){
            return UpdateViewersCount(id, 0);
        }

        inline bool DynamicMemory::Exists(Identifier id){
            auto it = AllocatedMemory.find(id);
            if(it == AllocatedMemory.end()){
                return false;
            }
            return true;
        }
        inline unsigned int DynamicMemory::Size() const {
            return AllocatedMemory.size();
        }
    }
}
