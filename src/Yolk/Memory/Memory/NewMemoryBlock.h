#pragma once

#include "Tables/NewSymbolTable.h"
#include "Tables/NewWrapperTable.h"

namespace Yolk
{
    namespace Memory
    {

        class MemoryBlock
        {
        private:
            SymbolKey GetSymbolKey(std::string Name);

        public:

            struct RegisterOutput
            {
                WrapperKey wrapperKey;
                bool ok;
            };
            struct FieldOutput
            {
                Wrapper wrapper;
                bool ok;
            };
            struct MethodOutput
            {
                MethodWrapper wrapper;
                bool ok;
            };
            struct KeyOutput
            {
                WrapperKey key;
                bool ok;
            };
            RegisterOutput RegisterWrapper(std::string Name, Wrapper wrapper, bool Force = false);
            RegisterOutput RegisterWrapper(std::string Name, MethodWrapper wrapper, bool Force = false);

            void DeleteByName(std::string Name);
            void DeleteByWrapperKey(WrapperKey);

            FieldOutput GetFieldWrapperByWrapperKey(WrapperKey key);
            MethodOutput GetMethodWrapperByWrapperKey(WrapperKey key);

            FieldOutput GetFieldWrapperByName(std::string Name);
            MethodOutput GetMethodWrapperByName(std::string Name);

            WrapperInfo GetWrapperInfoByName(std::string Name);
            WrapperInfo GetWrapperInfoByWrapperKey(WrapperKey key);

            KeyOutput GetWrapperKeyByName(std::string Name);

            SymbolTable& GetSymbolTable();

            MemoryBlock(MemoryManager &_manager, WrapperTable& _wrapperTable, std::function<void(std::string)> LogCallback = [](std::string){});

        private:
            MemoryManager& memoryManager;
            WrapperTable& wrapperTable;
            SymbolTable symbolTable;
            std::function<void(std::string)> LogCallbackFunction;
            std::string holderName;
        };

        
        inline MemoryBlock::MemoryBlock(MemoryManager &_manager, WrapperTable& _wrapperTable, std::function<void(std::string)> LogCallback)
            :   memoryManager(_manager),
                wrapperTable(_wrapperTable),
                LogCallbackFunction(LogCallback),
                holderName("")
        {
        }
        inline SymbolKey MemoryBlock::GetSymbolKey(std::string Name)
        {
            SymbolKey symbolKey(Name);
            return symbolKey;
        }
        inline MemoryBlock::RegisterOutput MemoryBlock::RegisterWrapper(std::string Name, Wrapper wrapper, bool Force)
        {
            std::string Log = "";
            SymbolKey symbol_key = GetSymbolKey(Name);
            
            SymbolTable::Result result = symbolTable.Get(symbol_key);

            bool keyExists = result.ok;
            if (keyExists)
            {
                if (Force)
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a field wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Forcing it!";
                    LogCallbackFunction(Log);

                    WrapperKey wrapper_key = result.value.key;
                    wrapperTable.Erase(wrapper_key);
                    symbolTable.Delete(symbol_key);
                }
                else
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a field wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Returning!";
                    LogCallbackFunction(Log);
                    return RegisterOutput { result.value.key, false};
                }
            }

            WrapperKey new_wrapper_key = wrapperTable.Add(wrapper);
            symbolTable.Add(symbol_key, new_wrapper_key);

            Log = "[Memory Block:" + holderName + "] INFO: A Field wrapper [" + Name + " - " + wrapper.field->GetType().name() + " ] was successfully registered in the memory block! Wrapper Key = " + std::to_string(new_wrapper_key) + ".";
            LogCallbackFunction(Log);

            return RegisterOutput { new_wrapper_key, true };
        }
        inline MemoryBlock::RegisterOutput MemoryBlock::RegisterWrapper(std::string Name, MethodWrapper wrapper, bool Force)
        {
            std::string Log = "";
            SymbolKey symbol_key = GetSymbolKey(Name);
            
            SymbolTable::Result result = symbolTable.Get(symbol_key);

            bool keyExists = result.ok;
            if (keyExists)
            {
                if (Force)
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a method wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Forcing it!";
                    LogCallbackFunction(Log);

                    WrapperKey wrapper_key = result.value.key;
                    wrapperTable.Erase(wrapper_key);
                    symbolTable.Delete(symbol_key);
                }
                else
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a method wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Returning!";
                    LogCallbackFunction(Log);
                    return RegisterOutput { result.value.key, false};
                }
            }

            WrapperKey new_wrapper_key = wrapperTable.Add(wrapper);
            symbolTable.Add(symbol_key, new_wrapper_key);

            Log = "[Memory Block:" + holderName + "] INFO: A Method wrapper [" + Name + " - " + wrapper.field->GetType().name() + " ] was successfully registered in the memory block! Wrapper Key = " + std::to_string(new_wrapper_key) + ".";
            LogCallbackFunction(Log);

            return RegisterOutput { new_wrapper_key, true };
        }
        inline void MemoryBlock::DeleteByName(std::string Name)
        {

            std::string Log = "";

            SymbolKey symbol_key = GetSymbolKey(Name);
            SymbolValue out_value;
            
            SymbolTable::Result result = symbolTable.Get(symbol_key);

            if (!result.ok)
            {
                Log = "[Memory Block:" + holderName + "] WARNING: Attempted to delete a key with name " + Name + " from the memory block but the key does not exist!";
                LogCallbackFunction(Log);
                return;
            }

            WrapperKey key = result.value.key;

            wrapperTable.Erase(key);
            symbolTable.Delete(symbol_key);

            Log = "[Memory Block:" + holderName + "] INFO: Deleting a wrapper with name " + Name + " from the memory block.";
            LogCallbackFunction(Log);
        }
        inline void MemoryBlock::DeleteByWrapperKey(WrapperKey wrapper_key)
        {
            std::string Log = "";
            
            SymbolValue symbol_value(wrapper_key);

            SymbolTable::FindResult result = symbolTable.Find(symbol_value);

            if (!result.ok)
            {
                Log = "[Memory Block:" + holderName + "] WARNING: Attempted to delete a key with wrapper key " + std::to_string(wrapper_key) + " from the memory block but the key does not exist!";
                LogCallbackFunction(Log);
                return;
            }

            wrapperTable.Erase(wrapper_key);
            symbolTable.Delete(result.key);

            Log = "[Memory Block:" + holderName + "] INFO: Deleting a wrapper with wrapper key " + std::to_string(wrapper_key) + " from the memory block.";
            LogCallbackFunction(Log);
        }

        inline MemoryBlock::FieldOutput MemoryBlock::GetFieldWrapperByWrapperKey(WrapperKey key)
        {
            if(!wrapperTable.Exists(key))
                return FieldOutput{ memoryManager.GenerateVoidWrapper(), false};
            Wrapper out = wrapperTable.CopyField(key);
            return FieldOutput {out, true};
        }
        inline MemoryBlock::MethodOutput MemoryBlock::GetMethodWrapperByWrapperKey(WrapperKey key)
        {
            if(!wrapperTable.Exists(key))
                return MethodOutput{MethodWrapper(memoryManager.GenerateVoidWrapper()), false};
            MethodWrapper out = wrapperTable.CopyMethod(key);
            return MethodOutput {out, true};
        }
        inline MemoryBlock::FieldOutput MemoryBlock::GetFieldWrapperByName(std::string Name)
        {
            SymbolKey symbol_key = GetSymbolKey(Name);

            SymbolTable::Result result = symbolTable.Get(symbol_key);

            if (!result.ok)
                return FieldOutput { memoryManager.GenerateVoidWrapper(), false};
            return FieldOutput { wrapperTable.CopyField(result.value.key), true};
        }
        inline MemoryBlock::MethodOutput MemoryBlock::GetMethodWrapperByName(std::string Name)
        {
            SymbolKey symbol_key = GetSymbolKey(Name);

            SymbolTable::Result result = symbolTable.Get(symbol_key);

            if (!result.ok)
                return MethodOutput { MethodWrapper(memoryManager.GenerateVoidWrapper()), false};
            return MethodOutput { wrapperTable.CopyMethod(result.value.key), true};
        }
        inline WrapperInfo MemoryBlock::GetWrapperInfoByName(std::string Name)
        {
            SymbolKey symbol_key = GetSymbolKey(Name);

            SymbolTable::Result result = symbolTable.Get(symbol_key);

            if (!result.ok)
            {
                return WrapperInfo(WrapperType::FieldWrapper, false, 0);
            }

            return wrapperTable.GetInfo(result.value.key);
        }
        inline WrapperInfo MemoryBlock::GetWrapperInfoByWrapperKey(WrapperKey key)
        {
            return wrapperTable.GetInfo(key);
        }
        inline MemoryBlock::KeyOutput MemoryBlock::GetWrapperKeyByName(std::string Name)
        {
            SymbolKey symbol_key = GetSymbolKey(Name);
            SymbolTable::Result result = symbolTable.Get(symbol_key);

            return KeyOutput {result.value.key, result.ok};
        }
        inline SymbolTable& MemoryBlock::GetSymbolTable()
        {
            return symbolTable;
        }
    }
}
