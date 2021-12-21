#pragma once

#include "Tables/WrapperTable.h"
#include "Tables/SymbolTable.h"
#include "../MemoryManager/MemoryManager.h"
#include <typeindex>

namespace Yolk
{
    namespace Memory
    {

        class MemoryBlock
        {
        public:
        private:
            SymbolKey GetSymbolKey(std::string Name);

        public:
            bool RegisterWrapper(std::string Name, Wrapper wrapper, Privacy privacy = Privacy::Public, bool Force = false);
            bool RegisterWrapper(std::string Name, MethodWrapper wrapper, Privacy privacy = Privacy::Public, bool Force = false);

            bool RegisterWrapper(std::string Name, Wrapper wrapper, WrapperTable::Key &outkey, Privacy privacy = Privacy::Public, bool Force = false);
            bool RegisterWrapper(std::string Name, MethodWrapper wrapper, WrapperTable::Key &outkey, Privacy privacy = Privacy::Public, bool Force = false);

            bool RegisterObject(std::string Name, Wrapper wrapper, Privacy privacy = Privacy::Public, bool Force = false);
            bool RegisterObject(std::string Name, Wrapper wrapper, WrapperTable::Key &outkey, Privacy privacy = Privacy::Public, bool Force = false);

            void DeleteByName(std::string Name);
            void DeleteByWrapperKey(WrapperTable::Key);

            Wrapper GetFieldWrapperByWrapperKey(WrapperTable::Key key);
            MethodWrapper GetMethodWrapperByWrapperKey(WrapperTable::Key key);
            Wrapper GetObjectWrapperByWrapperKey(WrapperTable::Key key);

            Wrapper GetFieldWrapperByName(std::string Name);
            MethodWrapper GetMethodWrapperByName(std::string Name);
            Wrapper GetObjectWrapperByName(std::string Name);

            WrapperTable::WrapperInfo GetWrapperInfoByName(std::string Name);
            WrapperTable::WrapperInfo GetWrapperInfoByWrapperKey(WrapperTable::Key key);

            WrapperTable::Key GetWrapperKeyByName(std::string Name);
            bool GetWrapperKeyByName(std::string Name, WrapperTable::Key &out);
            bool Exists(std::string Name);

            MemoryBlock(
                MemoryManager &_manager, std::string _name = "", Privacy pMode = Privacy::Public, std::function<void(std::string)> LogCallback = [](std::string) {});

            void Debug()
            {
            }

        private:
            MemoryManager &memoryManager;
            std::string holderName;
            Privacy PrivacyMode;
            std::function<void(std::string)> LogCallbackFunction;
            SymbolTable symbolTable;
            WrapperTable wrapperTable;
        };

        inline SymbolKey MemoryBlock::GetSymbolKey(std::string Name)
        {
            SymbolKey out(Name);
            return out;
        }

        inline MemoryBlock::MemoryBlock(MemoryManager &_manager, std::string _name, Privacy pMode, std::function<void(std::string)> LogCallback)
            : memoryManager(_manager),
              holderName(_name),
              PrivacyMode(pMode),
              LogCallbackFunction(LogCallback),
              wrapperTable(_manager)
        {
        }

        inline bool MemoryBlock::RegisterWrapper(std::string Name, Wrapper wrapper, WrapperTable::Key &outkey, Privacy, bool Force)
        {

            std::string Log = "";
            SymbolKey symbol_key = GetSymbolKey(Name);

            SymbolTable::Value out_value;
            bool keyExists = symbolTable.Get(symbol_key, out_value);

            if (keyExists)
            {
                if (Force)
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a field wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Forcing it!";
                    LogCallbackFunction(Log);

                    WrapperTable::Key wrapper_key = out_value;
                    wrapperTable.Erase(wrapper_key);
                    symbolTable.Delete(symbol_key);
                }
                else
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a field wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Returning!";
                    LogCallbackFunction(Log);
                    return false;
                }
            }

            SymbolTable::Value new_wrapper_key = wrapperTable.Add(wrapper);
            symbolTable.Add(symbol_key, new_wrapper_key);

            Log = "[Memory Block:" + holderName + "] INFO: A Field wrapper [" + Name + " - " + wrapper.field->GetType().name() + " ] was successfully registered in the memory block! Wrapper Key = " + std::to_string(new_wrapper_key) + ".";
            LogCallbackFunction(Log);

            outkey = new_wrapper_key;

            return true;
        }
        inline bool MemoryBlock::RegisterWrapper(std::string Name, MethodWrapper wrapper, WrapperTable::Key &outkey, Privacy, bool Force)
        {
            std::string Log = "";
            SymbolKey symbol_key = GetSymbolKey(Name);

            SymbolTable::Value out_value;
            bool keyExists = symbolTable.Get(symbol_key, out_value);

            if (keyExists)
            {
                if (Force)
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a method wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Forcing it!";
                    LogCallbackFunction(Log);

                    WrapperTable::Key wrapper_key = out_value;
                    wrapperTable.Erase(wrapper_key);
                    symbolTable.Delete(symbol_key);
                }
                else
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register a method wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Returning!";
                    LogCallbackFunction(Log);

                    return false;
                }
            }

            SymbolTable::Value new_wrapper_key = wrapperTable.Add(wrapper);
            symbolTable.Add(symbol_key, new_wrapper_key);

            Log = "[Memory Block:" + holderName + "] INFO: A Method wrapper [" + Name + " - " + wrapper.field->GetType().name() + " ] was successfully registered in the memory block! Wrapper Key = " + std::to_string(new_wrapper_key) + ".";
            LogCallbackFunction(Log);

            outkey = new_wrapper_key;

            return true;
        }
        inline bool MemoryBlock::RegisterObject(std::string Name, Wrapper wrapper, WrapperTable::Key &outkey, Privacy, bool Force)
        {
            std::string Log = "";
            SymbolKey symbol_key = GetSymbolKey(Name);

            SymbolTable::Value out_value;
            bool keyExists = symbolTable.Get(symbol_key, out_value);

            if (keyExists)
            {
                if (Force)
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register an object wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Forcing it!";
                    LogCallbackFunction(Log);

                    WrapperTable::Key wrapper_key = out_value;
                    wrapperTable.Erase(wrapper_key);
                    symbolTable.Delete(symbol_key);
                }
                else
                {
                    Log = "[Memory Block:" + holderName + "] WARNING: Attempted to register an object wrapper [" + Name + " - " + wrapper.field->GetType().name() + "] but a key already with that named already existed. Returning!";
                    LogCallbackFunction(Log);
                    return false;
                }
            }

            SymbolTable::Value new_wrapper_key = wrapperTable.Add(wrapper);
            symbolTable.Add(symbol_key, new_wrapper_key);

            Log = "[Memory Block:" + holderName + "] INFO: An object wrapper [" + Name + " - " + wrapper.field->GetType().name() + " ] was successfully registered in the memory block! Wrapper Key = " + std::to_string(new_wrapper_key) + ".";
            LogCallbackFunction(Log);

            outkey = new_wrapper_key;

            return true;
        }
        inline bool MemoryBlock::RegisterWrapper(std::string Name, Wrapper wrapper, Privacy privacy, bool Force)
        {
            WrapperTable::Key tmp;
            return RegisterWrapper(Name, wrapper, tmp, privacy, Force);
        }
        inline bool MemoryBlock::RegisterWrapper(std::string Name, MethodWrapper wrapper, Privacy privacy, bool Force)
        {
            WrapperTable::Key tmp;
            return RegisterWrapper(Name, wrapper, tmp, privacy, Force);
        }
        inline bool MemoryBlock::RegisterObject(std::string Name, Wrapper wrapper, Privacy privacy, bool Force)
        {
            WrapperTable::Key tmp;
            return RegisterObject(Name, wrapper, tmp, privacy, Force);
        }
        inline void MemoryBlock::DeleteByName(std::string Name)
        {

            std::string Log = "";
            SymbolKey symbol_key = GetSymbolKey(Name);

            SymbolTable::Value out_value;
            bool keyExists = symbolTable.Get(symbol_key, out_value);

            if (!keyExists)
            {
                Log = "[Memory Block:" + holderName + "] WARNING: Attempted to delete a key with name " + Name + " from the memory block but the key does not exist!";
                LogCallbackFunction(Log);
                return;
            }

            WrapperTable::Key key = out_value;

            wrapperTable.Erase(key);
            symbolTable.Delete(symbol_key);

            Log = "[Memory Block:" + holderName + "] INFO: Deleting a wrapper with name " + Name + " from the memory block.";
            LogCallbackFunction(Log);
        }
        inline void MemoryBlock::DeleteByWrapperKey(WrapperTable::Key wrapper_key)
        {
            std::string Log = "";
            SymbolTable::Value symbol_value = wrapper_key;
            SymbolTable::Key symbol_key;
            bool keyExists = symbolTable.Find(symbol_value, symbol_key);

            if (!keyExists)
            {
                Log = "[Memory Block:" + holderName + "] WARNING: Attempted to delete a key with wrapper key " + std::to_string(wrapper_key) + " from the memory block but the key does not exist!";
                LogCallbackFunction(Log);
                return;
            }

            wrapperTable.Erase(wrapper_key);
            symbolTable.Delete(symbol_key);

            Log = "[Memory Block:" + holderName + "] INFO: Deleting a wrapper with wrapper key " + std::to_string(wrapper_key) + " from the memory block.";
            LogCallbackFunction(Log);
        }

        inline Wrapper MemoryBlock::GetFieldWrapperByWrapperKey(WrapperTable::Key key)
        {
            Wrapper out = wrapperTable.CopyField(key);
            return out;
        }
        inline MethodWrapper MemoryBlock::GetMethodWrapperByWrapperKey(WrapperTable::Key key)
        {
            MethodWrapper out = wrapperTable.CopyMethod(key);
            return out;
        }
        inline Wrapper MemoryBlock::GetObjectWrapperByWrapperKey(WrapperTable::Key key)
        {
            Wrapper out = wrapperTable.CopyObject(key);
            return out;
        }
        inline Wrapper MemoryBlock::GetFieldWrapperByName(std::string Name)
        {
            SymbolTable::Key symbol_key = GetSymbolKey(Name);

            WrapperTable::Key wrapper_key;
            bool keyExists = symbolTable.Get(symbol_key, wrapper_key);

            if (!keyExists)
                return memoryManager.AllocateMemory<void>();

            return wrapperTable.CopyField(wrapper_key);
        }
        inline MethodWrapper MemoryBlock::GetMethodWrapperByName(std::string Name)
        {

            SymbolTable::Key symbol_key = GetSymbolKey(Name);

            WrapperTable::Key wrapper_key;
            bool keyExists = symbolTable.Get(symbol_key, wrapper_key);

            if (!keyExists)
                return memoryManager.AllocateMemory<void>();

            return wrapperTable.CopyMethod(wrapper_key);
        }
        inline Wrapper MemoryBlock::GetObjectWrapperByName(std::string Name)
        {
            SymbolTable::Key symbol_key = GetSymbolKey(Name);

            WrapperTable::Key wrapper_key;
            bool keyExists = symbolTable.Get(symbol_key, wrapper_key);

            if (!keyExists)
                return memoryManager.AllocateMemory<void>();

            return wrapperTable.CopyObject(wrapper_key);
        }
        inline WrapperTable::WrapperInfo MemoryBlock::GetWrapperInfoByName(std::string Name)
        {
            SymbolTable::Key symbol_key = GetSymbolKey(Name);

            WrapperTable::Key wrapper_key;
            bool keyExists = symbolTable.Get(symbol_key, wrapper_key);

            if (!keyExists)
            {
                return WrapperTable::WrapperInfo(WrapperType::FieldWrapper, typeid(void), WrapperTable::Status::Dead, -1, Privacy::Public);
            }

            return wrapperTable.GetInfo(wrapper_key);
        }

        inline WrapperTable::WrapperInfo MemoryBlock::GetWrapperInfoByWrapperKey(WrapperTable::Key key)
        {
            return wrapperTable.GetInfo(key);
        }

        inline WrapperTable::Key MemoryBlock::GetWrapperKeyByName(std::string Name)
        {
            SymbolTable::Key symbol_key = GetSymbolKey(Name);
            return symbolTable.Get(symbol_key);
        }
        inline bool MemoryBlock::GetWrapperKeyByName(std::string Name, WrapperTable::Key &out)
        {
            SymbolTable::Key symbol_key = GetSymbolKey(Name);
            return symbolTable.Get(symbol_key, out);
        }

        inline bool MemoryBlock::Exists(std::string Name)
        {
            SymbolTable::Key key = GetSymbolKey(Name);
            SymbolTable::Value tmp;
            bool out = symbolTable.Get(key, tmp);

            return out;
        }
    }
}
