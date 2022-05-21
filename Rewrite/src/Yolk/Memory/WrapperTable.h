#pragma once

#include "../Core/Core.h"
#include <unordered_map>
#include <typeindex>

namespace Yolk
{
    namespace Memory
    {
        using WrapperKey = unsigned long int;
        
        class KeyGenerator
        {
            public:
            static WrapperKey Tick()
            {
                KeyGenerator& instance = KeyGenerator::Instance();
                auto out = instance.key;
                instance.key++;
                return out;
            }
            static WrapperKey CurrentTick()
            {
                KeyGenerator& instance = KeyGenerator::Instance();
                return instance.key;
            }
            static KeyGenerator& Instance()
            {
                static KeyGenerator kg;
                return kg;
            }
            protected:
            WrapperKey key;
            private:
            KeyGenerator() : key(0) {}
        };

        struct WrapperSuperInfo
        {
            WrapperSuperInfo(Wrapper::Pointer _wrapper, WrapperType _wrapperType, bool _alive, WrapperKey _key)
                : wrapper(_wrapper), wrapperType(_wrapperType), alive(_alive), key(_key)
            {
            }
            Wrapper::Pointer wrapper;
            WrapperType wrapperType;
            bool alive;
            WrapperKey key;
        };

        struct WrapperInfo
        {
            WrapperInfo(WrapperType _wrapperType, bool _alive, WrapperKey _key)
                : wrapperType(_wrapperType), alive(_alive), key(_key)
            {
            }
            WrapperType wrapperType;
            bool alive;
            WrapperKey key;
        };
        class WrapperTable
        {
        public:
            WrapperTable(Yolk::Memory::MemoryManager &);
            ~WrapperTable();

            // API
            void Erase(WrapperKey);
            Wrapper CopyField(WrapperKey);
            MethodWrapper CopyMethod(WrapperKey);
            WrapperKey Add(Wrapper);
            WrapperKey Add(MethodWrapper);
            WrapperKey Size() const;
            bool Exists(WrapperKey) const;
            WrapperInfo GetInfo(WrapperKey) const;

        private:
            Yolk::Memory::MemoryManager &memoryManager;
            std::unordered_map<WrapperKey, WrapperSuperInfo> Table;
        };

        inline WrapperTable::WrapperTable(Yolk::Memory::MemoryManager& _memoryManager) : memoryManager(_memoryManager), Table() {}
        inline void WrapperTable::Erase(WrapperKey id)
        {
            if(id >= KeyGenerator::CurrentTick())
                return;

            //Table.at(id).wrapper->Free(); ???
            Table.at(id).wrapper.reset();
            Table.at(id).alive = false;
        }
        inline Wrapper WrapperTable::CopyField(WrapperKey id)
        {
            Wrapper out = *Table.at(id).wrapper;
            return out;
        }
        inline MethodWrapper WrapperTable::CopyMethod(WrapperKey id)
        {
            MethodWrapper out = *std::static_pointer_cast<MethodWrapper>(Table.at(id).wrapper);
            return out;
        }
        inline WrapperKey WrapperTable::Add(Wrapper wrapper)
        {
            WrapperKey id = KeyGenerator::Tick();

            Wrapper::Pointer new_pointer = std::make_shared<Wrapper>(wrapper);
            WrapperSuperInfo new_entry(new_pointer, WrapperType::FieldWrapper, true, id);
            Table.insert(std::pair(id, new_entry));
            return id;
        }
        inline WrapperKey WrapperTable::Add(MethodWrapper wrapper)
        {
            WrapperKey id = KeyGenerator::Tick();

            Wrapper::Pointer new_pointer = std::make_shared<MethodWrapper>(wrapper);
            WrapperSuperInfo new_entry(new_pointer, WrapperType::MethodWrapper, true, id);
            Table.insert(std::pair(id, new_entry));
            return id;
        }
        inline WrapperKey WrapperTable::Size() const
        {
            return KeyGenerator::CurrentTick();
        }
        inline WrapperTable::~WrapperTable()
        {
            for (auto &w : Table)
            {
                if (w.second.alive)
                    w.second.wrapper.reset();
            }
        }
        inline bool WrapperTable::Exists(WrapperKey key) const
        {
            if (key >= KeyGenerator::CurrentTick())
                return false;
            if (!Table.at(key).alive)
                return false;
            return true;
        }
        inline WrapperInfo WrapperTable::GetInfo(WrapperKey key) const
        {
            WrapperSuperInfo sinfo = Table.at(key);
            WrapperInfo info(sinfo.wrapperType, sinfo.alive, sinfo.key); 
            return info;
        }

    }
}
