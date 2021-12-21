#pragma once

#include "MemoryIndexer.h"
#include "../../Wrapper/TypedField.h"
#include "../../Wrapper/Wrapper.h"
#include <vector>
#include <memory>
#include <typeindex>
#include <sstream>
#include <functional>
#include <type_traits>

namespace Yolk
{
    namespace Memory
    {
        class MemoryManager
        {
        public:
            using Identifier = MemoryIndexer::Identifier;
            using AudienceCount = MemoryIndexer::Identifier;
            enum class DataMode
            {
                Dynamic,
                Static
            };

        private:
            struct AbstractData
            {
                virtual ~AbstractData(){};
                using Pointer = std::shared_ptr<AbstractData>;
                virtual Identifier GetID() const = 0;
                virtual AudienceCount ChangeAudience(AudienceCount difference) = 0;
                virtual std::type_index GetType() const = 0;
                virtual void *GetPointer() const = 0;
                virtual DataMode GetMode() const = 0;
                virtual std::string Print() const = 0;
                virtual void Debug() = 0;
                virtual TypedField::Pointer GenerateOwnTypedField() = 0;
                virtual AbstractData::Pointer CreateCopyByValue(Identifier id) = 0;
                virtual AbstractData::Pointer CreateCopyByReference(Identifier id) = 0;
            };
            using MemoryArray = std::vector<AbstractData::Pointer>;

            template <typename T>
            struct DynamicData : public AbstractData
            {
                using Pointer = std::shared_ptr<DynamicData<T>>;

                DynamicData(Identifier _ID) : ID(_ID), Audience(1) {}
                DynamicData(Identifier _ID, T tvalue) : ID(_ID), Audience(1), data(tvalue) {}
                ~DynamicData()
                {
                }
                T &GetReference()
                {
                    return data;
                }
                Identifier GetID() const
                {
                    return ID;
                }
                AudienceCount ChangeAudience(AudienceCount difference)
                {
                    Audience += difference;
                    return Audience;
                }
                void *GetPointer() const
                {
                    void *out = (void *)&data;
                    return out;
                }
                void Debug()
                {
                    std::stringstream buffer;
                    constexpr bool HasShiftOperator = requires(T t)
                    {
                        buffer << t << std::endl;
                    };

                    std::cout << "Dynamic Data (Type = " << typeid(data).name() << ", Id =  " << ID << ", Audience: " << Audience << ") - ";
                    if constexpr (HasShiftOperator)
                    {
                        std::cout << data << std::endl;
                    }
                    else
                    {
                        std::cout << "[Unknown Object]" << std::endl;
                    }
                }
                std::string Print() const
                {
                    std::stringstream buffer;
                    constexpr bool hasShiftOperator = requires(T t)
                    {
                        buffer << t << std::endl;
                    };

                    if constexpr (hasShiftOperator)
                    {
                        buffer << data;
                        return buffer.str();
                    }
                    return "[Unknown Object]";
                }
                DataMode GetMode() const
                {
                    return DataMode::Dynamic;
                }
                std::type_index GetType() const
                {
                    return typeid(data);
                }
                TypedField::Pointer GenerateOwnTypedField()
                {
                    T &ref = data;
                    TypedField::Pointer new_tfield(new TypedField(ref));
                    return new_tfield;
                }
                AbstractData::Pointer CreateCopyByValue(Identifier id)
                {
                    AbstractData::Pointer newCopy = std::make_shared<DynamicData<T>>(id, data);
                    return newCopy;
                }
                AbstractData::Pointer CreateCopyByReference(Identifier id)
                {
                    AbstractData::Pointer newCopy = std::make_shared<StaticData<T>>(id, data);
                    return newCopy;
                }
                Identifier ID;
                AudienceCount Audience;
                T data;
            };

            template <typename T>
            struct StaticData : public AbstractData
            {
                StaticData(Identifier _ID, T &reference) : ID(_ID), Audience(1), data(reference) {}

                T &GetReference()
                {
                    return data;
                }
                Identifier GetID() const
                {
                    return ID;
                }
                AudienceCount ChangeAudience(AudienceCount difference)
                {
                    Audience += difference;
                    return Audience;
                }
                void *GetPointer() const
                {
                    void *out = (void *)&data;
                    return out;
                }
                void Debug()
                {
                    std::stringstream buffer;
                    constexpr bool HasShiftOperator = requires(T t)
                    {
                        buffer << t << std::endl;
                    };

                    std::cout << "Static Data (Type = " << typeid(data).name() << ", Id =  " << ID << ", Audience: " << Audience << ") - ";
                    if constexpr (HasShiftOperator)
                    {
                        std::cout << data << std::endl;
                    }
                    else
                    {
                        std::cout << "[Unknown Object]" << std::endl;
                    }
                }
                std::string Print() const
                {
                    std::stringstream buffer;
                    constexpr bool hasShiftOperator = requires(T t)
                    {
                        buffer << t << std::endl;
                    };

                    if constexpr (hasShiftOperator)
                    {
                        buffer << data;
                        return buffer.str();
                    }
                    return "[Unknown Object]";
                }
                std::type_index GetType() const
                {
                    return typeid(data);
                }
                DataMode GetMode() const
                {
                    return DataMode::Static;
                }
                TypedField::Pointer GenerateOwnTypedField()
                {
                    TypedField::Pointer new_tfield(new TypedField(data)); // <- Problem is in here! Somehow, this TypeField is const?!!!
                    return new_tfield;
                }
                AbstractData::Pointer CreateCopyByValue(Identifier id)
                {
                    AbstractData::Pointer newCopy = std::make_shared<DynamicData<T>>(id, data);
                    return newCopy;
                }
                AbstractData::Pointer CreateCopyByReference(Identifier id)
                {
                    AbstractData::Pointer newCopy = std::make_shared<StaticData<T>>(id, data);
                    return newCopy;
                }
                Identifier ID;
                AudienceCount Audience;
                T &data;
            };

        public:
            MemoryManager(
                std::string _Name = std::to_string(MemoryIndexer::Tick()), std::function<void(std::string)> Logcallback = [](std::string) {});
            //MemoryManager(std::function<void(std::string)> Logcallback);
            MemoryManager(MemoryManager &other);
            MemoryManager(MemoryManager *other);
            virtual ~MemoryManager();

            template <typename T>
            Wrapper AllocateMemory();
            template <typename T>
            Wrapper AllocateMemory(T tvalue);

            template <typename T>
            Wrapper RegisterStatic(T &value);

            Wrapper CopyByValue(Wrapper original);
            Wrapper CopyByReference(Wrapper original, bool new_entry = false);

            AudienceCount ChangeAudience(Identifier _id, AudienceCount difference = 0);

            bool Exists(Identifier _id) const;
            void Debug();
            void RegisterLogcallbackFunction(std::function<void(std::string)> Logcallback);
            Identifier Size() const;
            const std::string Name() const;

        private:
            Wrapper GenerateVoidWrapper();
            MemoryManager(const MemoryManager &) = delete;

            const std::string name;
            MemoryManager *Manager;
            std::function<void(std::string)> LogCallbackFunction;
            MemoryArray AllocatedMemory;
        };

        inline MemoryManager::MemoryManager(std::string _Name, std::function<void(std::string)> LogCallback) : name(_Name), Manager(this), LogCallbackFunction(LogCallback)
        {
            std::string Log = "[Memory Manager] INFO: Created Memory Manager with name: " + name;
            LogCallbackFunction(Log);
        }
        inline MemoryManager::MemoryManager(MemoryManager &other) : name(other.Name()), Manager(&other), LogCallbackFunction(other.LogCallbackFunction)
        {
            std::string Log = "[Memory Manager] INFO: Created Memory Manager from reference with name: " + other.name;
            LogCallbackFunction(Log);
        }
        inline MemoryManager::MemoryManager(MemoryManager *other) : name(other->Name()), Manager(other), LogCallbackFunction(other->LogCallbackFunction)
        {
            std::string Log = "[Memory Manager] INFO: Created Memory Manager from pointer with name: " + other->name;
            LogCallbackFunction(Log);
        }
        inline MemoryManager::~MemoryManager() {}

        template <typename T>
        inline Wrapper MemoryManager::AllocateMemory()
        {
            std::string Log = "";

            Identifier id = MemoryIndexer::Tick();

            Log = "[Memory Manager] INFO: Allocating memory for type: (" + std::string(typeid(T).name()) + "), with identifier = " + std::to_string(id) + ".";
            LogCallbackFunction(Log);

            AbstractData::Pointer new_data = std::make_shared<DynamicData<T>>(id);

            //T &reference = std::static_pointer_cast<DynamicData<T>>(new_data)->GetReference();
            //TypedField::Pointer new_tfield(new TypedField(reference));

            TypedField::Pointer new_tfield = new_data->GenerateOwnTypedField();

            Wrapper output(id, new_tfield, *this);

            Manager->AllocatedMemory.push_back(new_data);
            return output;
        }

        template <typename T>
        inline Wrapper MemoryManager::AllocateMemory(T tvalue)
        {
            std::string Log = "";

            Identifier id = MemoryIndexer::Tick();

            AbstractData::Pointer new_data = std::make_shared<DynamicData<T>>(id, tvalue);

            //T &reference = std::static_pointer_cast<DynamicData<T>>(new_data)->GetReference();
            //TypedField::Pointer new_tfield(new TypedField(reference));

            TypedField::Pointer new_tfield = new_data->GenerateOwnTypedField();

            Log = "[Memory Manager] INFO: Allocating memory for type: (" + std::string(typeid(T).name()) + "), with identifier = " + std::to_string(id) + ". Initialized value: " + new_tfield->Print() + ".";
            LogCallbackFunction(Log);

            Wrapper output(id, new_tfield, *this);

            Manager->AllocatedMemory.push_back(new_data);

            return output;
        }

        template <typename T>
        inline Wrapper MemoryManager::RegisterStatic(T &value)
        {
            Identifier id = MemoryIndexer::Tick();
            AbstractData::Pointer new_static = std::make_shared<StaticData<T>>(id, value);

            //T &reference = value;
            //TypedField::Pointer new_tfield(new TypedField(reference));

            TypedField::Pointer new_tfield = new_static->GenerateOwnTypedField();

            std::string Log = "[Memory Manager] INFO: Registering static value to memory with type: (" + std::string(typeid(T).name()) + "), with identifier = " + std::to_string(id) + ". Initialized value: " + new_tfield->Print() + ".";
            LogCallbackFunction(Log);

            Wrapper output(id, new_tfield, *this);

            Manager->AllocatedMemory.push_back(new_static);
            return output;
        }

        inline Wrapper MemoryManager::CopyByValue(Wrapper original)
        {
            if(original.wType != WrapperType::FieldWrapper)
                return GenerateVoidWrapper();

                
            Identifier originalId = original.ID;

            for (auto &memory : AllocatedMemory)
            {
                if (memory->GetID() == originalId)
                {
                    Identifier id = MemoryIndexer::Tick();
                    AbstractData::Pointer new_copy = memory->CreateCopyByValue(id);
                    TypedField::Pointer new_tfield = new_copy->GenerateOwnTypedField();

                    Wrapper output(id, new_tfield, *this);

                    std::string Log = "[Memory Manager] INFO: Copying Wrapper by value to memory with type: (" + std::string(original.field->GetType().name()) + "), with identifier = " + std::to_string(originalId) + ". Copied value: " + new_tfield->Print() + ".";
                    LogCallbackFunction(Log);
                    
                    Manager->AllocatedMemory.push_back(new_copy);
                    return output;
                }
            }

            return GenerateVoidWrapper();
        }
        inline Wrapper MemoryManager::CopyByReference(Wrapper original, bool new_entry)
        {
            if(!new_entry)
                return original;
        
            Identifier originalId = original.ID;

            for (auto &memory : AllocatedMemory)
            {
                if (memory->GetID() == originalId)
                {
                    Identifier id = MemoryIndexer::Tick();
                    AbstractData::Pointer new_copy = memory->CreateCopyByReference(id);
                    TypedField::Pointer new_tfield = new_copy->GenerateOwnTypedField();

                    Wrapper output(id, new_tfield, *this);

                    std::string Log = "[Memory Manager] INFO: Copying Wrapper by reference to memory with type: (" + std::string(original.field->GetType().name()) + "), with identifier = " + std::to_string(originalId) + ". Copied value: " + new_tfield->Print() + ".";
                    LogCallbackFunction(Log);
                    
                    Manager->AllocatedMemory.push_back(new_copy);
                    return output;
                }
            }

            return GenerateVoidWrapper();
        }
        inline MemoryManager::AudienceCount MemoryManager::ChangeAudience(Identifier _id, AudienceCount difference)
        {
            for (MemoryArray::iterator it = Manager->AllocatedMemory.begin(); it != Manager->AllocatedMemory.end(); it++)
            {
                if (_id == (*it)->GetID())
                {
                    int updatedScored = (*it)->ChangeAudience(difference);

                    if (updatedScored == 0)
                    {
                        std::string Log = "[Memory Manager] INFO: The audience of " + std::to_string(_id) + " [" + (*it)->GetType().name() + " , " + (*it)->Print() + "] has reached zero. Deleting it!";
                        LogCallbackFunction(Log);
                        Manager->AllocatedMemory.erase(it);

                        if (Manager->Size() == 0)
                        {
                            Log = "[Memory Manager] INFO: Memory table empty!";
                            LogCallbackFunction(Log);
                        }
                    }
                    return updatedScored;
                }
            }
            return 0;
        }

        inline bool MemoryManager::Exists(Identifier _id) const
        {
            for (MemoryArray::iterator it = Manager->AllocatedMemory.begin(); it != Manager->AllocatedMemory.end(); it++)
            {
                if (_id == (*it)->GetID())
                {
                    return true;
                }
            }
            return false;
        }

        inline void MemoryManager::Debug()
        {
            for (auto &m : Manager->AllocatedMemory)
            {
                m->Debug();
            }
        }

        inline void MemoryManager::RegisterLogcallbackFunction(std::function<void(std::string)> Logcallback)
        {
            LogCallbackFunction = Logcallback;
        }
        inline MemoryManager::Identifier MemoryManager::Size() const
        {
            return Manager->AllocatedMemory.size();
        }

        inline const std::string MemoryManager::Name() const
        {
            return name;
        }

        inline Wrapper MemoryManager::GenerateVoidWrapper()
        {
            MemoryManager::Identifier id = MemoryIndexer::Tick();
            TypedField::Pointer new_field = std::make_shared<TypedField>();
            Wrapper wrapper(id, new_field, *this);

            return wrapper;
        }
        template <>
        inline Wrapper MemoryManager::AllocateMemory<void>()
        {
            std::string Log = "[Memory Manager] INFO: Requested void allocation. Returning default TypedField wrapper.";
            LogCallbackFunction(Log);

            MemoryManager::Identifier id = MemoryIndexer::Tick();
            TypedField::Pointer new_field = std::make_shared<TypedField>();
            Wrapper wrapper(id, new_field, *this);

            return wrapper;
        }
    }

}

//#include "../../Wrapper/WrapperRequired.h"