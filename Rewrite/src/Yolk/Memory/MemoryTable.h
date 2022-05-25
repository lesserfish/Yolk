#pragma once

#include "../Core/Core.h"
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
            bool ok;
        };
        struct MethodWrapperOut 
        {
            MethodWrapper wrapper;
            MapKey key;
            bool ok;
        };
        struct MemoryPointerOut 
        {
            MemoryInterface* memory;
            MapKey key;
            bool ok;
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

        private:
            DynamicMemory& dynamicMemory;
            std::unordered_map<MapKey, Wrapper> wrapperTable;
            std::unordered_map<MapKey, MethodWrapper> methodWrapperTable;
            std::unordered_map<MapKey, MemoryInterface*> memoryPointerTable;
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
               return WrapperOut {  dynamicMemory.GetVoidWrapper(),
                                    id,
                                    false};
            }

            return WrapperOut { search->second,
                                id,
                                true};
        }
        inline MethodWrapperOut MemoryTable::GetMethod(MapKey id)
        {
            auto search = methodWrapperTable.find(id);
            if(search == methodWrapperTable.end()){
               return MethodWrapperOut {  MethodWrapper(dynamicMemory.GetVoidWrapper()),
                                    id,
                                    false};
            }

            return MethodWrapperOut { search->second,
                                id,
                                true};
             
        }
        inline MemoryPointerOut MemoryTable::GetMemory(MapKey id)
        {
            auto search = memoryPointerTable.find(id);
            if(search == memoryPointerTable.end()){
               return MemoryPointerOut {  nullptr,
                                    id,
                                    false};
            }

            return MemoryPointerOut { search->second,
                                id,
                                true};
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
            memoryPointerTable[id] = mempointer;
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
    }
}
