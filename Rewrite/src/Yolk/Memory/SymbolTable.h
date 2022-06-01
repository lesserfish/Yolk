#pragma once

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
            enum Type {
                Wrapper,
                MethodWrapper,
                MemoryPointer,
                None
            };
            SymbolValue(MapKey k, Type t) : key(k), type(t), ok(true) {}
            SymbolValue(MapKey k, Type t, bool o) : key(k), type(t), ok(o) {}
            MapKey key;
            Type type;
            bool ok;
            bool operator==(const SymbolValue &other) const
            {
                return (key == other.key);
            }
            bool operator==(const MapKey& k) const
            {
                return (key == k);
            }
            static SymbolValue Failure(){
                SymbolValue out = SymbolValue(
                    0,
                    Type::None,
                    false);
                return out;
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
        struct SymbolKeySearchResult
        {
            SymbolKey key;
            bool ok;
        };
        class SymbolTableInterface;

        class SymbolTable {
            public:
                SymbolTable();
                SymbolTable(SymbolTable& ref);
                ~SymbolTable();

                bool Exists(SymbolKey);
                std::pair<SymbolKey, SymbolValue> Get(SymbolKey);
                std::vector<std::pair<SymbolKey, SymbolValue>> GetAll();
                
                bool Add(SymbolKey, SymbolValue, bool addtolocaltable = true);
                std::pair<SymbolKey, SymbolValue> Delete(SymbolKey);
                std::vector<std::pair<SymbolKey, SymbolValue>> Delete(std::vector<SymbolKey>);
                std::vector<std::pair<SymbolKey, SymbolValue>> DeleteAll();
                
                SymbolKeySearchResult Find(SymbolValue);

            private:
                friend class SymbolTableInterface;
                std::unordered_map<SymbolKey, SymbolValue> Table;
                std::vector<std::pair<SymbolKey, SymbolValue>> LocalTable;
        };
        
        inline SymbolTable::SymbolTable() : Table(), LocalTable() {}
        inline SymbolTable::SymbolTable(SymbolTable& ref) : Table(ref.Table), LocalTable() {}
        inline SymbolTable::~SymbolTable() {}
        inline bool SymbolTable::Exists(SymbolKey key) {
            auto result = Table.find(key);
            return !(result == Table.end());
        }
        inline std::pair<SymbolKey, SymbolValue> SymbolTable::Get(SymbolKey key) {
            auto result = Table.find(key);
            if(result == Table.end()){
                return std::make_pair(key, SymbolValue::Failure());
            }
            return std::make_pair(key, result->second);
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTable::GetAll() {
            std::vector<std::pair<SymbolKey, SymbolValue>> out;
            for (auto it = Table.begin(); it != Table.end(); it++)
            {
                out.push_back(std::make_pair(it->first, it->second));
            }
            return out;
        }
        inline bool SymbolTable::Add(SymbolKey key, SymbolValue value, bool addtolocaltable) {
            
            auto result = Table.insert(std::make_pair(key, value));
            if(result.second && addtolocaltable){
               LocalTable.push_back(std::make_pair(key, value));
               return true;
            }
            return false;
        }
        inline std::pair<SymbolKey, SymbolValue> SymbolTable::Delete(SymbolKey key){
            auto result = Table.find(key);
            if(result == Table.end()){
                return std::make_pair(key, SymbolValue::Failure());
            }
            auto out = std::make_pair(key, result->second);
            
            Table.erase(result);
            for(auto it = LocalTable.begin(); it < LocalTable.end(); it++){
                if(it->first == key){
                    LocalTable.erase(it);
                    break;
                }
            }

            return out;
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTable::Delete(std::vector<SymbolKey> todelete) {
            std::vector<std::pair<SymbolKey, SymbolValue>> out;

            for(auto it = todelete.begin(); it < todelete.end(); it++){
                auto d = Delete(*it);
                if(d.second.ok){
                    out.push_back(d);
                }
            }
            return out;
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTable::DeleteAll(){
            std::vector<SymbolKey> todelete;
            for (auto it = Table.begin(); it != Table.end(); it++){
                todelete.push_back(it->first);
            }
            return Delete(todelete);
        }
        inline SymbolKeySearchResult SymbolTable::Find(SymbolValue value) {
            for (auto it = Table.begin(); it != Table.end(); it++){
                if(it->second == value){
                    return SymbolKeySearchResult{it->first, true};
                }
            }
            return SymbolKeySearchResult{SymbolKey{}, false};
        }

        class SymbolTableInterface
        {
        public:
            SymbolTableInterface();
            ~SymbolTableInterface();

            // API Interface
            
            unsigned int GetLevel() const;
            void BranchDown();
            std::vector<std::pair<SymbolKey, SymbolValue>> BranchUp();
            
            bool Exists(SymbolKey);
            std::pair<SymbolKey, SymbolValue> Get(SymbolKey);
            std::vector<std::pair<SymbolKey, SymbolValue>> GetAll();
            
            bool Add(SymbolKey, SymbolValue);
            bool GlobalAdd(SymbolKey, SymbolValue);
            std::pair<SymbolKey, SymbolValue> Delete(SymbolKey);
            std::pair<SymbolKey, SymbolValue> GlobalDelete(SymbolKey);
            std::vector<std::pair<SymbolKey, SymbolValue>> Delete(std::vector<SymbolKey>);
            std::vector<std::pair<SymbolKey, SymbolValue>> DeleteAll();
            
            SymbolKeySearchResult Find(SymbolValue);

        protected:
            std::vector<SymbolTable*> Tables;
        };
        inline SymbolTableInterface::SymbolTableInterface() : Tables() {
            SymbolTable* start = new SymbolTable();
            Tables.push_back(start);
        }
        inline SymbolTableInterface::~SymbolTableInterface() {
            for(auto it = Tables.begin(); it != Tables.end(); it++){
                SymbolTable* ptr = *it;
                delete ptr;
            }
        }
        inline unsigned int SymbolTableInterface::GetLevel() const {
            return Tables.size() - 1;
        }
        inline void SymbolTableInterface::BranchDown() {
            SymbolTable* lastelement = Tables.back();
            SymbolTable* newelement = new SymbolTable(*lastelement);
            Tables.push_back(newelement);
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTableInterface::BranchUp(){
            std::vector<std::pair<SymbolKey, SymbolValue>> out;
            if(GetLevel() == 0){
                return out;
            }
            SymbolTable* lastelement = Tables.back();
            Tables.pop_back();
            out = lastelement->LocalTable;
            delete lastelement;
            return out;
        }
        inline bool SymbolTableInterface::Exists(SymbolKey key) {
            SymbolTable* lastelement = Tables.back();
            return lastelement->Exists(key);
        }
        inline std::pair<SymbolKey, SymbolValue> SymbolTableInterface::Get(SymbolKey key){
            SymbolTable* lastelement = Tables.back();
            return lastelement->Get(key);
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTableInterface::GetAll(){
            SymbolTable* lastelement = Tables.back();
            return lastelement->GetAll();
        }
        inline bool SymbolTableInterface::Add(SymbolKey key, SymbolValue value) {
            SymbolTable* lastelement = Tables.back();
            return lastelement->Add(key, value);
        }
        inline bool SymbolTableInterface::GlobalAdd(SymbolKey key, SymbolValue value) {
            bool out = true;
            for(auto it = Tables.begin(); it != Tables.end(); it++){
                SymbolTable* lastelement = (*it);
                out = out && lastelement->Add(key, value, it == Tables.begin());
            }
            return out;
        }
        inline std::pair<SymbolKey, SymbolValue> SymbolTableInterface::GlobalDelete(SymbolKey key) {
            auto out = std::make_pair(key, SymbolValue::Failure());
            for(auto it = Tables.begin(); it != Tables.end(); it++){
                SymbolTable* lastelement = (*it);
                out = lastelement->Delete(key);
            }
            return out;
        }
        inline std::pair<SymbolKey, SymbolValue> SymbolTableInterface::Delete(SymbolKey key){
            SymbolTable* lastelement = Tables.back();
            return lastelement->Delete(key);
        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTableInterface::Delete(std::vector<SymbolKey> todelete){
            SymbolTable* lastelement = Tables.back();
            return lastelement->Delete(todelete);

        }
        inline std::vector<std::pair<SymbolKey, SymbolValue>> SymbolTableInterface::DeleteAll() {
            SymbolTable* lastelement = Tables.back();
            return lastelement->DeleteAll();
        }
        inline SymbolKeySearchResult SymbolTableInterface::Find(SymbolValue value){
            SymbolTable* lastelement = Tables.back();
            return lastelement->Find(value);
        }

    }
}
