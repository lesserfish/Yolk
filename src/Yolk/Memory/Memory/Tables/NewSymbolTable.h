#pragma once

#include "NewWrapperTable.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <iostream>

namespace Yolk
{
    namespace Memory
    {
        struct SymbolKey
        {
            SymbolKey(std::string _Name = "") : Name(_Name) {}
            std::string Name;

            bool operator==(const SymbolKey &other) const
            {
                std::string c1 = Name;
                std::string c2 = other.Name;
                return c1 == c2;
            }
        };
        struct SymbolValue
        {
            SymbolValue(WrapperKey _key = 0) : key(_key) {}
            WrapperKey key;

            bool operator==(const SymbolValue &other) const
            {
                return (key == other.key);
            }
        };
    }
}
namespace std
{
    template <>
    struct hash<Yolk::Memory::SymbolKey>
    {
        size_t operator()(const Yolk::Memory::SymbolKey &key) const
        {
            return hash<string>()(key.Name);
        }
    };
}
namespace Yolk
{
    namespace Memory
    {
        class SymbolTable
        {
        public:
            using Pointer = SymbolTable *;
            using Level = unsigned long int;

            struct FindResult
            {
                SymbolKey key;
                bool ok;
            };
            struct Result
            {
                SymbolValue value;
                bool ok;
            };

        public:
            SymbolTable();
            SymbolTable(Pointer);
            SymbolTable(const SymbolTable&);
            SymbolTable& operator=(const SymbolTable& other);
            ~SymbolTable();

            void BranchDown();
            void BranchUp();

            // API Interface
            Level GetLevel() const;
            bool Add(SymbolKey, SymbolValue);
            bool GlobalAdd(SymbolKey, SymbolValue);
            Result Get(SymbolKey);
            bool Exists(SymbolKey);
            void Delete(SymbolKey);
            void GlobalDelete(SymbolKey);
            void Delete(std::vector<SymbolKey>);
            FindResult Find(SymbolValue);

            void ClearAll();
            void ClearChildren();
            static void Clone(const SymbolTable &origin, SymbolTable &destiny);
            void Debug();

        private:
        protected:
            const Level level;
            Pointer self;
            Pointer Father;
            Pointer Child;
            std::unordered_map<std::string, Pointer> Friends;
            std::unordered_map<SymbolKey, SymbolValue> Table;
        };

        inline SymbolTable::SymbolTable() : level(0), self(this), Father(this), Child(nullptr), Friends(), Table() {}
        inline SymbolTable::SymbolTable(Pointer _Father) : level(_Father->level + 1), self(this), Father(_Father), Child(nullptr), Friends(_Father->Friends), Table(_Father->Table){}
        inline SymbolTable::SymbolTable(const SymbolTable& other) : level(0), Father(this), Child(nullptr), Friends(), Table()
        {
            Clone(other, *this);
        }
        inline SymbolTable& SymbolTable::operator=(const SymbolTable& other)
        {
            ClearAll();
            Clone(other, *this);
            return *this;
        }
        inline SymbolTable::~SymbolTable()
        {
            ClearChildren();
        }
        inline SymbolTable::Level SymbolTable::GetLevel() const
        {
            return self->level;
        }

        inline void SymbolTable::BranchDown()
        {
            self->Child = new SymbolTable(self);
            self = self->Child;
        }
        inline void SymbolTable::BranchUp()
        {
            if (GetLevel() == 0)
                return;
            self = self->Father;

            delete self->Child;
            self->Child = nullptr;
        }
        inline bool SymbolTable::Add(SymbolKey key, SymbolValue value)
        {
            if (key == SymbolKey())
                return false;
            ;
            auto const result = self->Table.insert(std::make_pair(key, value));
            return result.second;
        }
        inline bool SymbolTable::GlobalAdd(SymbolKey key, SymbolValue value)
        {
            bool out = true;
            Pointer p = self;
            do
            {
                auto const result = p->Table.insert(std::make_pair(key, value));
                out = out && result.second;
                p = p->Father;
            } while (p->level != 0);

            out = out && p->Table.insert(std::make_pair(key, value)).second;
            return out;
        }
        inline SymbolTable::Result SymbolTable::Get(SymbolKey key)
        {
            auto result = self->Table.find(key);
            if (result == self->Table.end())
                return Result{SymbolValue(), false};
            return Result{result->second, true};
        }
        inline bool SymbolTable::Exists(SymbolKey key)
        {
            auto result = self->Table.find(key);
            if (result == self->Table.end())
                return false;
            return true;
        }
        inline void SymbolTable::Delete(SymbolKey key)
        {
            self->Table.erase(key);
        }
        inline void SymbolTable::GlobalDelete(SymbolKey key)
        {
            Pointer p = self;
            do
            {
                p->Table.erase(key);
                p = p->Father;
            } while (p->level != 0);

            p->Table.erase(key);
        }
        inline void SymbolTable::Delete(std::vector<SymbolKey> keys)
        {
            for (auto key : keys)
            {
                self->Table.erase(key);
            }
        }
        inline SymbolTable::FindResult SymbolTable::Find(SymbolValue value)
        {
            for (auto it = self->Table.begin(); it != self->Table.end(); it++)
            {
                if (it->second == value)
                {
                    FindResult out{it->first, true};
                    return out;
                }
            }

            FindResult out{SymbolKey(), false};
            return out;
        }
        inline void SymbolTable::Debug()
        {
            Pointer p = self;
            while (p->level != 0)
            {
                std::cout << "\nLevel: " << p->level << std::endl;
                std::string flog = p->Father == p ? "Is his own father\n" : "Has a father\n";
                std::string clog = p->Child ? "Has a child\n" : "Does not have a child\n";

                std::cout << flog << clog << std::endl
                          << "Table: \n";
                for (auto i : p->Table)
                {
                    std::cout << ": " << i.first.Name << " - " << i.second.key << std::endl;
                };
                p = p->Father;
            }
            std::cout << "\nLevel: " << p->level << std::endl;
            std::string flog = p->Father == p ? "Is his own father\n" : "Has a father\n";
            std::string clog = p->Child ? "Has a child\n" : "Does not have a child\n";
            std::cout << flog << clog << std::endl
                          << "Table: \n";
            
            
            for (auto i : p->Table)
            {
                std::cout << ": " << i.first.Name << " - " << i.second.key << std::endl;
            }
        }
        inline void SymbolTable::ClearAll()
        {
            while (GetLevel() != 0)
            {
                BranchUp(); // Delete all downward branches.
            }
            self->Table.clear();
        }
        inline void SymbolTable::ClearChildren()
        {
            if (Child)
            {
                Child->ClearChildren();
            }
            delete Child;
            Child = nullptr;
        }
        inline void SymbolTable::Clone(const SymbolTable &origin, SymbolTable &destiny)
        {
            destiny.ClearChildren();

            if (origin.level == 0)
            {
                destiny.Father = &destiny;
            }
            if (origin.Child)
            {
                destiny.Child = new SymbolTable(&destiny);
                Clone(*origin.Child, *destiny.Child);
                destiny.self = destiny.Child->self;
            }
            else
            {
                destiny.Child = nullptr;
                destiny.self = &destiny;
            }

            destiny.Table = origin.Table;
            destiny.Friends = origin.Friends;
        }
    }
}