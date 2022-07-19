#pragma once

#include "../Core/Core.h"
#include "Exceptions.h"
#include <unordered_map>
#include <typeindex>

namespace Yolk
{
    namespace Memory
    {
        class MemoryInterface;
        
        using MapKey = unsigned long int;
        
        class KeyGenerator
        {
            public:
            static MapKey Tick()
            {
                KeyGenerator& instance = KeyGenerator::Instance();
                auto out = instance.key;
                instance.key++;
                return out;
            }
            static KeyGenerator& Instance()
            {
                static KeyGenerator kg;
                return kg;
            }
            protected:
            MapKey key;
            private:
            KeyGenerator() : key(0) {}
        };

        struct WrapperOut 
        {
            Wrapper wrapper;
            MapKey key;
        };
        struct MethodWrapperOut 
        {
            MethodWrapper wrapper;
            MapKey key;
        };
        struct MemoryPointerOut 
        {
            MemoryInterface* memory;
            MapKey key;
        };

        struct MPWrapper {
            MPWrapper() : pointer(nullptr), active(false) {}
            MPWrapper(MemoryInterface* p) : pointer(p), active(true) {}
            MemoryInterface* pointer;
            bool active;
        };
        class MemoryTable
        {
        public:
            MemoryTable(DynamicMemory&);
            ~MemoryTable();

            // API
            void Erase(MapKey);
            WrapperOut GetField(MapKey);
            MethodWrapperOut GetMethod(MapKey);
            MemoryPointerOut GetMemory(MapKey);
            MapKey Add(Wrapper);
            MapKey Add(MethodWrapper);
            MapKey Add(MemoryInterface*);
            MapKey Size() const;
            bool Exists(MapKey) const;
            void UnsetMemoryPointer(MemoryInterface *);

        private:
            DynamicMemory& dynamicMemory;
            std::unordered_map<MapKey, Wrapper> wrapperTable;
            std::unordered_map<MapKey, MethodWrapper> methodWrapperTable;
            std::unordered_map<MapKey, MPWrapper> memoryPointerTable;
        };

        inline MemoryTable::MemoryTable(Yolk::Memory::DynamicMemory& _dynamicMemory) : dynamicMemory(_dynamicMemory), wrapperTable(), methodWrapperTable(), memoryPointerTable() {}
        inline MemoryTable::~MemoryTable(){}
        
        inline void MemoryTable::Erase(MapKey id)
        {
            wrapperTable.erase(id);
            methodWrapperTable.erase(id);
            memoryPointerTable.erase(id);
        }
        inline WrapperOut MemoryTable::GetField(MapKey id)
        {
            auto search = wrapperTable.find(id);
            if(search == wrapperTable.end()){
               throw MException("Could not find field in Memory table [" + std::to_string(id) + "]");
            }

            return WrapperOut { search->second,
                                id};
        }
        inline MethodWrapperOut MemoryTable::GetMethod(MapKey id)
        {
            auto search = methodWrapperTable.find(id);
            if(search == methodWrapperTable.end()){
               throw MException("Could not find method in Memory table [" + std::to_string(id) + "]");
            }

            return MethodWrapperOut { search->second,
                                id};
             
        }
        inline MemoryPointerOut MemoryTable::GetMemory(MapKey id)
        {
            auto search = memoryPointerTable.find(id);
            if(search == memoryPointerTable.end()){
               throw MException("Could not find memory in Memory table [" + std::to_string(id) + "]");
            }

            if(search->second.active) {
                return MemoryPointerOut { search->second.pointer,
                                id};
            }
            
            throw MException("Nemory is set as not active in Memory table [" + std::to_string(id) + "]");
        }
        inline MapKey MemoryTable::Add(Wrapper wrapper)
        {
            MapKey id = KeyGenerator::Tick();
            wrapperTable.emplace(std::make_pair(id, wrapper));
            return id;
        }
        inline MapKey MemoryTable::Add(MethodWrapper wrapper)
        {
            MapKey id = KeyGenerator::Tick();
            methodWrapperTable.emplace(std::make_pair(id, wrapper));
            return id;
        }
        inline MapKey MemoryTable::Add(MemoryInterface *mempointer) {
            MapKey id = KeyGenerator::Tick();
            memoryPointerTable.emplace(std::make_pair(id, MPWrapper(mempointer)));
            return id;
        }
        inline MapKey MemoryTable::Size() const
        {
            auto sum = wrapperTable.size() + methodWrapperTable.size() + memoryPointerTable.size();
            return sum;
        }

        inline bool MemoryTable::Exists(MapKey id) const
        {
            bool search1 = wrapperTable.find(id) == wrapperTable.end();
            bool search2 = methodWrapperTable.find(id) == methodWrapperTable.end();
            bool search3 = memoryPointerTable.find(id) == memoryPointerTable.end();
            bool search = search1 || search2 || search3;
            return search;
        }
        inline void MemoryTable::UnsetMemoryPointer(MemoryInterface* pointer) {
            for(auto it = memoryPointerTable.begin(); it != memoryPointerTable.end(); it++)
            {
                if(it->second.pointer == pointer){
                    it->second.active = false;
                }
            }
        }
    }
}
