#pragma once

#include "../../../Wrapper/Wrapper.h"
#include "../../../Wrapper/MethodWrapper.h"
#include <vector>
#include <typeindex>

namespace Yolk
{
    namespace Memory
    {
        enum class Privacy
        {
            Public,     // Anyone has Read + Write access to all members
            Private,    // Nobody but the holder has Read or Write access to all members
            Protected   // Everybody has read access to all members, but only the holder class has write access 
        };
        class WrapperTable
        {
            public:

            using Key = unsigned long long int;

            enum class Status
            {
                Dead = -1,
                Alive
            };

            struct WrapperInfo
            {
                WrapperInfo(WrapperType _wrapperType, std::type_index _stdType, Status _status, Key _id, Privacy _privacy)
                    :   wrapperType(_wrapperType), stdType(_stdType), status(_status), id(_id), privacy(_privacy)
                {}
                WrapperType wrapperType;
                std::type_index stdType;
                Status status;
                Key id;
                Privacy privacy;
            };
            struct WrapperSuperInfo : public WrapperInfo
            {
                WrapperSuperInfo(Wrapper::Pointer _wrapperPointer, WrapperType _wrapperType, std::type_index _stdType, Status _status, Key _id, Privacy privacy)
                    :   WrapperInfo(_wrapperType, _stdType, _status, _id, privacy), wrapperPointer(_wrapperPointer)
                {}
                Wrapper::Pointer wrapperPointer;
                
            };

            using Table = std::vector<WrapperSuperInfo>;
            using Value = WrapperSuperInfo;

            public:
            WrapperTable(MemoryManager &_manager) : manager(_manager), wrapperTable(){}
            ~WrapperTable();

            public:

            void Erase(Key id);
            Wrapper CopyField(Key id);
            MethodWrapper CopyMethod(Key id);
            Wrapper CopyObject(Key id);
            Key Add(Wrapper wrapper, Privacy privacy = Privacy::Public);
            Key Add(MethodWrapper wrapper, Privacy privacy = Privacy::Public);
            Key AddObject(Wrapper wrapper, Privacy privacy = Privacy::Public);
            Key Size() const;
            bool Exists(Key id) const;
            WrapperInfo GetInfo(Key id) const;
            WrapperSuperInfo GetSuperInfo(Key id) const;
            
            
            public:
            MemoryManager& manager;
            Table wrapperTable;
        };


        inline void WrapperTable::Erase(Key id)
        {
            auto &e = wrapperTable.at(id);
            e.wrapperPointer.reset();
            e.status = Status::Dead;
        }
        inline Wrapper WrapperTable::CopyField(Key id)
        {
            Wrapper out = *wrapperTable.at(id).wrapperPointer;
            return out;
        }
        inline MethodWrapper WrapperTable::CopyMethod(Key id)
        {
            MethodWrapper out = *std::static_pointer_cast<MethodWrapper>(wrapperTable.at(id).wrapperPointer);
            return out;
        } 
        inline Wrapper WrapperTable::CopyObject(Key id)
        {
            Wrapper out = *wrapperTable.at(id).wrapperPointer;
            return out;
        }
        inline WrapperTable::Key WrapperTable::Add(Wrapper wrapper, Privacy privacy)
        {
            if(wrapper.manager.Name() != manager.Name())
                return -1;
                
            Key id = wrapperTable.size();

            Wrapper::Pointer new_pointer = std::make_shared<Wrapper>(wrapper);
            Value new_entry(new_pointer, WrapperType::FieldWrapper, wrapper.field->GetType(), Status::Alive, id, privacy);
            wrapperTable.push_back(new_entry);

            return id;
        }
        inline WrapperTable::Key WrapperTable::Add(MethodWrapper wrapper, Privacy privacy)
        {
            if(wrapper.manager.Name() != manager.Name())
                return -1;
            
            Key id = wrapperTable.size();

            Wrapper::Pointer new_pointer = std::make_shared<MethodWrapper>(wrapper);
            Value new_entry(new_pointer, WrapperType::MethodWrapper, wrapper.field->GetType(), Status::Alive, id, privacy);
            wrapperTable.push_back(new_entry);
            return id;
        }
        inline WrapperTable::Key WrapperTable::AddObject(Wrapper wrapper, Privacy privacy)
        {
            if(wrapper.manager.Name() != manager.Name())
                return -1;
                
            Key id = wrapperTable.size();

            Wrapper::Pointer new_pointer = std::make_shared<Wrapper>(wrapper);
            Value new_entry(new_pointer, WrapperType::FieldWrapper, wrapper.field->GetType(), Status::Alive, id, privacy);
            wrapperTable.push_back(new_entry);

            return id;
        }
        inline WrapperTable::Key WrapperTable::Size() const
        {
            return wrapperTable.size();
        }
        inline WrapperTable::~WrapperTable()
        {
            for (auto &w : wrapperTable)
            {
                if(w.status == Status::Alive)
                    w.wrapperPointer.reset();
            }
        }
        inline bool WrapperTable::Exists(Key key) const
        {
            if(key >= wrapperTable.size())
                return false;
            if(wrapperTable.at(key).status == Status::Dead)
                return false;
            return true;
        }
        inline WrapperTable::WrapperInfo WrapperTable::GetInfo(Key key) const
        {
            WrapperSuperInfo value = wrapperTable.at(key);
            WrapperInfo info(value);

            return info;
        }
        inline WrapperTable::WrapperSuperInfo WrapperTable::GetSuperInfo(Key id) const
        {
            WrapperSuperInfo info = wrapperTable.at(id);
            return info;
        }

    }
}