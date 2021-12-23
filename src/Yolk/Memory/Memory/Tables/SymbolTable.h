#pragma once

#include "WrapperTable.h"
#include <string>
#include <unordered_map>
#include <functional>
namespace Yolk
{
    namespace Memory
    {
        struct SymbolKey
        {
            SymbolKey(std::string name = "", std::string mode = "", std::string args = "", bool _alias = false) : Name(name), Mode(mode), Args(args), alias(_alias)
            {
            }
            std::string Name;
            std::string Mode;
            std::string Args;
            bool alias;
            bool operator==(const SymbolKey &key) const
            {
                std::string c1 = Name;
                std::string c2 = key.Name;
                return c1 == c2;
            };
            bool operator<(const SymbolKey &key) const
            {
                std::string c1 = Name;
                std::string c2 = key.Name;
                return c1 < c2;
            };
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
            std::string to_hash = key.Name;
            return hash<string>()(to_hash);
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
            using Value = WrapperTable::Key;
            using Key = SymbolKey;
            static const Value NANValue = -1;

            using Table = std::unordered_map<Key, Value>;

        public:
            bool Add(Key, Value, bool Forced = false);
            bool CreateAlias(Key, Key);
            bool DeleteAlias(Key);
            Value Get(Key);
            bool Get(Key, Value &);
            bool Exists(Key);
            void Delete(Key);
            void Delete(std::vector<Key>);
            Key Find(Value);
            bool Find(Value, Key &);

        private:
            Table symbolTable;
        };

        inline bool SymbolTable::Add(Key key, Value value, bool Forced)
        {
            if (key == Key()) // No empty string key
                return false;
            auto const result = symbolTable.insert(std::make_pair(key, value));
            if (!result.second && Forced)
            {
                result.first->second = value;
                return true;
            }
            return result.second;
        }
        inline bool SymbolTable::CreateAlias(Key original, Key alias)
        {
            if(original == Key() || alias == Key())
                return false;
            auto const original_value = symbolTable.find(original);

            if(original_value == symbolTable.end())
                return false; // Original name does not exist
            
            auto const result = symbolTable.insert(std::make_pair(alias, original_value->second));
            return result.second;
        }
        inline bool SymbolTable::DeleteAlias(Key alias)
        {
            auto result = symbolTable.find(alias);
            if(result == symbolTable.end())
                return false;
            if(!result->first.alias)
                return false;

            symbolTable.erase(result);
            return true;
        }
        inline SymbolTable::Value SymbolTable::Get(Key key)
        {
            auto result = symbolTable.find(key);
            if (result == symbolTable.end())
                return NANValue;
            return result->second;
        }
        inline bool SymbolTable::Get(Key key, Value &outvalue)
        {
            auto result = symbolTable.find(key);
            if (result == symbolTable.end())
                return false;
            outvalue = result->second;
            return true;
        }
        inline bool SymbolTable::Exists(Key key)
        {
            auto result = symbolTable.find(key);
            if (result == symbolTable.end())
                return false;
            return true;
        }
        inline void SymbolTable::Delete(Key key)
        {
            symbolTable.erase(key);
        }
        inline void SymbolTable::Delete(std::vector<Key> keys)
        {
            for (Key &key : keys)
            {
                Delete(key);
            }
        }
        inline SymbolTable::Key SymbolTable::Find(Value value)
        {
            for (Table::iterator it = symbolTable.begin(); it != symbolTable.end(); it++)
            {
                if (it->second == value)
                {
                    return it->first;
                }
            }
            return SymbolTable::Key();
        }
        inline bool SymbolTable::Find(Value value, Key &out)
        {
            for (Table::iterator it = symbolTable.begin(); it != symbolTable.end(); it++)
            {
                if (it->second == value)
                {
                    out = it->first;
                    return true;
                }
            }
            return false;
        }
    }
}