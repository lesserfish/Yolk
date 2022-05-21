#pragma once

#include "WrapperTable.h"
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
            struct FriendResult
            {
                Pointer result;
                bool ok;
            };

        public:
            SymbolTable();
            SymbolTable(Pointer);
            SymbolTable(const SymbolTable &);
            SymbolTable &operator=(const SymbolTable &other);
            ~SymbolTable();

            void BranchDown();
            std::vector<std::pair<SymbolKey, SymbolValue>> BranchUp();

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
            std::vector<SymbolValue> GetAll();

            std::vector<std::pair<SymbolKey, SymbolValue>> ClearAll();
            std::vector<std::pair<SymbolKey, SymbolValue>> ClearChildren(bool toggle_recursion = false);
            static void Clone(const SymbolTable &origin, SymbolTable &destiny);
            void Debug();

            FriendResult GetFriend(std::string);
            bool AddFriend(std::string, Pointer);
            void DeleteFriend(std::string);

        private:
        protected:
            const Level level;
            Pointer self;
            Pointer Father;
            Pointer Child;
            std::unordered_map<std::string, Pointer> Friends;
            std::unordered_map<SymbolKey, SymbolValue> Table;
            std::vector<std::pair<SymbolKey, SymbolValue>> LocalTable;
        };

        inline SymbolTable::SymbolTable() : level(0), self(this), Father(this), Child(nullptr), Friends(), Table() {}
        inline SymbolTable::SymbolTable(Pointer _Father) : level(_Father->level + 1), self(this), Father(_Father), Child(nullptr), Friends(_Father->Friends), Table(_Father->Table) {}
        inline SymbolTable::SymbolTable(const SymbolTable &other) : level(0), Father(this), Child(nullptr), Friends(), Table()
        {
            Clone(other, *this);
        }
        inline SymbolTable &SymbolTable::operator=(const SymbolTable &other)
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
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTable::BranchUp()
        {
            std::vector<std::pair<SymbolKey, SymbolValue>> out;
            if (GetLevel() == 0)
                return out;

            out = self->LocalTable;
            self = self->Father;

            delete self->Child;
            self->Child = nullptr;

            return out;
        }
        inline bool SymbolTable::Add(SymbolKey key, SymbolValue value)
        {
            if (key == SymbolKey())
                return false;

            auto const result = self->Table.insert(std::make_pair(key, value));

            if (result.second)
                self->LocalTable.push_back(std::make_pair(key, value));
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
            p->LocalTable.push_back(std::make_pair(key, value));
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
        inline std::vector<SymbolValue> SymbolTable::GetAll()
        {
            std::vector<SymbolValue> out;
            for (auto it = Table.begin(); it != Table.end(); it++)
            {
                out.push_back(it->second);
            }
            return out;
        }
        inline void SymbolTable::Debug()
        {
            std::cout << "----------------------------------\nBeggining Debug:\n\n";
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

                std::cout << "Local Table: ";
                for (auto i : p->LocalTable)
                {
                    std::cout << i.first.Name << ":" << i.second.key << "\t";
                }
                std::cout << "\n";
                p = p->Father;
            }
            std::cout << "\nLevel: " << p->level << std::endl;
            std::string flog = p->Father == p ? "Is his own father\n" : "Has a father\n";
            std::string clog = p->Child ? "Has a child\n" : "Does not have a child\n";
            std::cout << flog << clog << std::endl
                      << "Table: ";

            for (auto i : p->Table)
            {
                std::cout << ": " << i.first.Name << " - " << i.second.key << std::endl;
            }
            std::cout << "Local Table: \n";
            for (auto i : p->LocalTable)
            {
                std::cout << i.first.Name << ":" << i.second.key << "\t";
            }
            std::cout << "\n";
            std::cout << "---------------------------------------\n";
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTable::ClearAll()
        {
            std::vector<std::pair<SymbolKey, SymbolValue>> out = LocalTable;

            while (GetLevel() != 0)
            {
                auto extension = BranchUp(); // Delete all downward branches.
                out.insert(out.begin(), extension.begin(), extension.end());
            }
            self->Table.clear();

            return out;
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTable::ClearChildren(bool toggle_recursion)
        {
            std::vector<std::pair<SymbolKey, SymbolValue>> out;
            if(toggle_recursion)
                out = LocalTable;
            if (Child)
            {
                auto extension = Child->ClearChildren(true);
                out.insert(out.end(), extension.begin(), extension.end());
            }
            delete Child;
            Child = nullptr;

            return out;
        }
        inline void SymbolTable::Clone(const SymbolTable &origin, SymbolTable &destiny) // This breaks stuff. Should not be used.
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
            destiny.LocalTable = origin.LocalTable;
        }
        inline bool SymbolTable::AddFriend(std::string name, Pointer p)
        {
            bool out = Friends.insert(std::pair(name, p)).second;
            return out;
        }
        inline void SymbolTable::DeleteFriend(std::string name)
        {
            Friends.erase(name);
        }
        inline SymbolTable::FriendResult SymbolTable::GetFriend(std::string Name)
        {
            auto out = Friends.find(Name);
            if (out == Friends.end())
                return FriendResult{nullptr, false};
            return FriendResult{out->second, true};
        }
    }
}
