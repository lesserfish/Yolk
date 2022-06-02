#pragma once

#include "../Core/Core.h"

namespace Yolk
{
    namespace Memory
    {

        class MemoryInterface
        {

        public:
            
            MemoryInterface(DynamicMemory& _memory);
            ~MemoryInterface();
            
            bool RegisterWrapper(Wrapper wrapper, std::string Name, bool global = false);
            bool RegisterMethodWrapper(MethodWrapper wrapper, std::string Name, bool global = false);
            bool RegisterMemoryPointer(MemoryInterface*, std::string, bool global = false);
            
            bool Register(Wrapper wrapper, std::string Name, bool global = false);
            bool Register(MethodWrapper wrapper, std::string Name, bool global = false);
            bool Register(MemoryInterface* , std::string Name, bool global = false);
            
            void Delete(std::string Name, bool global = false);
            void UnsetMemoryPointer(MemoryInterface*);

            WrapperOut GetWrapper(std::string);
            MethodWrapperOut GetMethodWrapper(std::string);
            MemoryPointerOut GetMemoryPointer(std::string);
            SymbolValue::Type GetType(std::string);

            void BranchUp();
            void BranchDown();

            SymbolTableInterface& GetSymbolTableInterface();
            MemoryTable& GetMemoryTable();
        private:
            DynamicMemory& memory;
            MemoryTable memoryTable;
            SymbolTableInterface symbolTableInterface;
        };
        
        inline MemoryInterface::MemoryInterface(DynamicMemory& _memory) : memory(_memory), memoryTable(_memory), symbolTableInterface() {}
        inline MemoryInterface::~MemoryInterface() {}
        
        inline bool MemoryInterface::RegisterWrapper(Wrapper wrapper, std::string Name, bool global) {
            if(symbolTableInterface.Exists(Name)){
                return false;
            }
            auto mapkey = memoryTable.Add(wrapper);
            SymbolKey symbolkey(Name);
            SymbolValue symbolvalue(mapkey, SymbolValue::Type::Wrapper);
            if(global) {
                symbolTableInterface.GlobalAdd(symbolkey, symbolvalue);
            } else {
                symbolTableInterface.Add(symbolkey, symbolvalue);
            }
            return true;
        }
        inline bool MemoryInterface::RegisterMethodWrapper(MethodWrapper wrapper, std::string Name, bool global) {
            if(symbolTableInterface.Exists(Name)){
                return false;
            }
            auto mapkey = memoryTable.Add(wrapper);
            SymbolKey symbolkey(Name);
            SymbolValue symbolvalue(mapkey, SymbolValue::Type::MethodWrapper);
            if(global) {
                symbolTableInterface.GlobalAdd(symbolkey, symbolvalue);
            } else {
                symbolTableInterface.Add(symbolkey, symbolvalue);
            }
            return true;
        }
        inline bool MemoryInterface::RegisterMemoryPointer(MemoryInterface* pointer, std::string Name, bool global) {
            if(symbolTableInterface.Exists(Name)){
                return false;
            }
            auto mapkey = memoryTable.Add(pointer);
            SymbolKey symbolkey(Name);
            SymbolValue symbolvalue(mapkey, SymbolValue::Type::MemoryPointer);
            if(global) {
                symbolTableInterface.GlobalAdd(symbolkey, symbolvalue);
            } else {
                symbolTableInterface.Add(symbolkey, symbolvalue);
            }
            return true;
        }
        inline void MemoryInterface::Delete(std::string Name, bool global) {
            if(global) {
                SymbolKey symbolkey(Name);
                auto pair = symbolTableInterface.GlobalDelete(symbolkey);
                if(pair.second.ok){
                    auto mapkey = pair.second.key;
                    memoryTable.Erase(mapkey);
                }
            } else {
                SymbolKey symbolkey(Name);
                auto pair = symbolTableInterface.Delete(symbolkey);
                if(pair.second.ok){
                    auto mapkey = pair.second.key;
                    memoryTable.Erase(mapkey);
                }
            }
        }
        inline void MemoryInterface::UnsetMemoryPointer(MemoryInterface* pointer) {
            memoryTable.UnsetMemoryPointer(pointer);
        }
        inline WrapperOut MemoryInterface::GetWrapper(std::string Name){
            SymbolKey symbolkey(Name);
            auto pair = symbolTableInterface.Get(symbolkey);
            if(pair.second.type != SymbolValue::Type::Wrapper) {
                return WrapperOut {memory.GetVoidWrapper(), 0, false};
            }
            auto mapkey = pair.second.key;
            return memoryTable.GetField(mapkey);
        }
        inline MethodWrapperOut MemoryInterface::GetMethodWrapper(std::string Name) {
            SymbolKey symbolkey(Name);
            auto pair = symbolTableInterface.Get(symbolkey);
            if(pair.second.type != SymbolValue::Type::MethodWrapper) {
                return MethodWrapperOut {MethodWrapper(memory.GetVoidWrapper()), 0, false};
            }
            auto mapkey = pair.second.key;
            return memoryTable.GetMethod(mapkey);
        }
        inline MemoryPointerOut MemoryInterface::GetMemoryPointer(std::string Name) {
            SymbolKey symbolkey(Name);
            auto pair = symbolTableInterface.Get(symbolkey);
            if(pair.second.type != SymbolValue::Type::MemoryPointer) {
                return MemoryPointerOut {nullptr, 0, false};
            }
            auto mapkey = pair.second.key;
            return memoryTable.GetMemory(mapkey);
        }
        inline SymbolValue::Type MemoryInterface::GetType(std::string Name){
            SymbolKey symbolkey(Name);
            return symbolTableInterface.Get(symbolkey).second.type;
        }
        inline SymbolTableInterface& MemoryInterface::GetSymbolTableInterface(){
            return symbolTableInterface;
        }
        inline MemoryTable& MemoryInterface::GetMemoryTable(){
            return memoryTable;
        }
        inline void MemoryInterface::BranchUp() {
            auto deleteditems = symbolTableInterface.BranchUp();
            for(auto item = deleteditems.begin(); item!= deleteditems.end(); item++){
                auto symbolkey = item->first;
                auto symbolvalue = item->second;

                if(symbolvalue.ok){
                    auto mapkey = symbolvalue.key;
                    memoryTable.Erase(mapkey);
                }
            }
        }
        inline void MemoryInterface::BranchDown() {
            symbolTableInterface.BranchDown();
        }
        inline bool MemoryInterface::Register(Wrapper wrapper, std::string Name, bool global){
            return RegisterWrapper(wrapper, Name, global);
        }
        inline bool MemoryInterface::Register(MethodWrapper wrapper, std::string Name, bool global){
            return RegisterMethodWrapper(wrapper, Name, global);
        }
        inline bool MemoryInterface::Register(MemoryInterface* pointer, std::string Name, bool global){
            return RegisterMemoryPointer(pointer, Name, global);
        }
    }
}
