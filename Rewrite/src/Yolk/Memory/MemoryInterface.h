#pragma once

#include "../Core/Core.h"

namespace Yolk
{
    namespace VM
    {
        class VirtualMachine;
    }
    namespace Memory
    {
        class MemoryInterface
        {

        public:
            friend class VM::VirtualMachine;
            
            MemoryInterface(DynamicMemory& _memory);
            ~MemoryInterface();
            
            void RegisterWrapper(Wrapper wrapper, std::string Name, bool global = false);
            void RegisterMethodWrapper(MethodWrapper wrapper, std::string Name, bool global = false);
            void RegisterMemoryPointer(MemoryInterface*, std::string, bool global = false);
            
            void Register(Wrapper wrapper, std::string Name, bool global = false);
            void Register(MethodWrapper wrapper, std::string Name, bool global = false);
            void Register(MemoryInterface* , std::string Name, bool global = false);
            
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
        
        inline void MemoryInterface::RegisterWrapper(Wrapper wrapper, std::string Name, bool global) {
            if(symbolTableInterface.Exists(Name)){
                throw MException("Memory exception thrown. Failed to register wrapper. Name already exists.");
            }
            auto mapkey = memoryTable.Add(wrapper);
            SymbolKey symbolkey(Name);
            SymbolValue symbolvalue(mapkey, SymbolValue::Type::Wrapper);
            if(global) {
                symbolTableInterface.GlobalAdd(symbolkey, symbolvalue);
            } else {
                symbolTableInterface.Add(symbolkey, symbolvalue);
            }
        }
        inline void MemoryInterface::RegisterMethodWrapper(MethodWrapper wrapper, std::string Name, bool global) {
            if(symbolTableInterface.Exists(Name)){
                throw MException("Memory exception thrown. Failed to register wrapper. Name already exists.");
            }
            auto mapkey = memoryTable.Add(wrapper);
            SymbolKey symbolkey(Name);
            SymbolValue symbolvalue(mapkey, SymbolValue::Type::MethodWrapper);
            if(global) {
                symbolTableInterface.GlobalAdd(symbolkey, symbolvalue);
            } else {
                symbolTableInterface.Add(symbolkey, symbolvalue);
            }
        }
        inline void MemoryInterface::RegisterMemoryPointer(MemoryInterface* pointer, std::string Name, bool global) {
            if(symbolTableInterface.Exists(Name)){
                throw MException("Memory exception thrown. Failed to register wrapper. Name already exists.");
            }
            auto mapkey = memoryTable.Add(pointer);
            SymbolKey symbolkey(Name);
            SymbolValue symbolvalue(mapkey, SymbolValue::Type::MemoryPointer);
            if(global) {
                symbolTableInterface.GlobalAdd(symbolkey, symbolvalue);
            } else {
                symbolTableInterface.Add(symbolkey, symbolvalue);
            }
        }
        inline void MemoryInterface::Delete(std::string Name, bool global) {
            if(global) {
                SymbolKey symbolkey(Name);
                try{
                    auto pairs = symbolTableInterface.GlobalDelete(symbolkey);
                    for(auto pair = pairs.begin(); pair != pairs.end(); pair++){
                        auto mapkey = pair->second.key;
                        memoryTable.Erase(mapkey);
                    }
                } catch(const MException& exception)
                {
                    throw exception;
                }
            } else {
                SymbolKey symbolkey(Name);
                try {
                    auto pair = symbolTableInterface.Delete(symbolkey);
                    auto mapkey = pair.second.key;
                    memoryTable.Erase(mapkey);
                } catch(const MException& exception)
                {
                    throw exception;
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
                throw MException("Requested wrapper of type field. Got other type of wrapper");
            }
            auto mapkey = pair.second.key;
            return memoryTable.GetField(mapkey);
        }
        inline MethodWrapperOut MemoryInterface::GetMethodWrapper(std::string Name) {
            SymbolKey symbolkey(Name);
            auto pair = symbolTableInterface.Get(symbolkey);
            if(pair.second.type != SymbolValue::Type::MethodWrapper) {
                throw MException("Requested wrapper of type method. Got other type of wrapper");
            }
            auto mapkey = pair.second.key;
            return memoryTable.GetMethod(mapkey);
        }
        inline MemoryPointerOut MemoryInterface::GetMemoryPointer(std::string Name) {
            SymbolKey symbolkey(Name);
            auto pair = symbolTableInterface.Get(symbolkey);
            if(pair.second.type != SymbolValue::Type::MemoryPointer) {
                throw MException("Requested wrapper of type memory. Got other type of wrapper");
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

                auto mapkey = symbolvalue.key;
                memoryTable.Erase(mapkey);
            }
        }
        inline void MemoryInterface::BranchDown() {
            symbolTableInterface.BranchDown();
        }
        inline void MemoryInterface::Register(Wrapper wrapper, std::string Name, bool global){
            RegisterWrapper(wrapper, Name, global);
        }
        inline void MemoryInterface::Register(MethodWrapper wrapper, std::string Name, bool global){
            RegisterMethodWrapper(wrapper, Name, global);
        }
        inline void MemoryInterface::Register(MemoryInterface* pointer, std::string Name, bool global){
            RegisterMemoryPointer(pointer, Name, global);
        }
    }
}
