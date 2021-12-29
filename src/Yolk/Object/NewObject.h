#pragma once

#include "Network.h"
#include "../Memory/Memory/NewMemoryBlock.h"
#include "../Wrapper/WrapperGenerator.h"
#include <map>

namespace Yolk
{
    class Object : public Network
    {
        public:

        using Name = std::string;
        using Father = Object;

        struct ObjectOptions
        {
            ObjectOptions()
            {}
            // Memory Block Options
            std::function<void(std::string)> ObjLogCallback = [](std::string){};
            std::function<void(std::string)> memBlockLogCallback = [](std::string){};
        };
        protected:
        
       
        enum class Mode
        {
            God,
            Follower
        };

        public:

        //protected:
        Object(Name _Name, Memory::MemoryManager& manager, Memory::WrapperTable& _wrapperTable, ObjectOptions options = ObjectOptions());
        Object(Name _Name, Father *_Father, ObjectOptions options = ObjectOptions());
        
        virtual ~Object();

        public:

        std::string RequestNewName(std::string RequestedName);
        Name GetLocalName() const;
        Name GetGlobalName() const;

        Memory::MemoryManager& GetMemoryManager() const;
        Memory::WrapperTable& GetWrapperTable() const;
        Memory::MemoryBlock& GetMemoryBlock();
        
        protected:

        template <typename T>
        bool RegisterField(T& lvalue, std::string Name);
        void DeregisterField(std::string Name);
        template <typename Out, typename... In>
        bool RegisterMethod(std::function<Out(In...)> rvalue, std::string Name);
        void DeregisterMethod(std::string Name);
        bool RegisterObject(Object *object);
        void DeregisterObject(Object *object); 
        
        void AlertDeath(Object *object);
        int GetObjectCount() const;
        bool ExecuteScript(std::string Script);
        
        protected:

        const Name localName;
        const Name globalName;

        Father* father;
        const Mode mode;

        Memory::MemoryManager& memoryManager;
        Memory::WrapperTable& wrapperTable;
        Memory::MemoryBlock memoryBlock;

        protected:
        std::function<void(std::string)> LogCallbackFunction;

    };
    
    inline Object::Object(Name _Name, Memory::MemoryManager& manager, Memory::WrapperTable& _wrapperTable, ObjectOptions options) :
            localName(_Name),
            globalName(_Name),
            father(this), 
            mode(Mode::God), 
            memoryManager(manager),
            wrapperTable(_wrapperTable),
            memoryBlock(manager,_wrapperTable, options.memBlockLogCallback),
            LogCallbackFunction(options.ObjLogCallback)

    {
        std::string Log = "[Object:"+ localName +"] INFO: A God has been created: " + globalName;
        LogCallbackFunction(Log);
    }
    
    inline Object::Object(Name _name, Father* _father, ObjectOptions options) :
            localName(_name),
            globalName(_father->GetGlobalName() + "::" + localName), 
            father(_father), 
            mode(Mode::Follower), 
            memoryManager(_father->GetMemoryManager()),
            wrapperTable(_father->GetWrapperTable()),
            memoryBlock(memoryManager, wrapperTable, options.memBlockLogCallback),
            LogCallbackFunction(options.ObjLogCallback)
    {
        std::string Log = "[Object:" + localName +"] INFO: Object created: " + globalName;
        LogCallbackFunction(Log);
        father->RegisterObject(this);
    }

    inline Object::~Object()
    {
        for(auto& object : Watchers)
        {
            Object *cast = static_cast<Object*>(object);
            cast->DeregisterObject(this);
        }
        std::string Log = "[Object:" + localName+"] INFO: " + globalName + " has been destroyed.";
        LogCallbackFunction(Log);
    }
    inline Memory::MemoryManager& Object::GetMemoryManager() const
    {
        return memoryManager;
    }
    inline Memory::WrapperTable& Object::GetWrapperTable() const
    {
        return wrapperTable;
    }
    inline Memory::MemoryBlock& Object::GetMemoryBlock()
    {
        return memoryBlock;
    }
    inline Object::Name Object::GetLocalName() const
    {
        return localName;
    }
    inline int Object::GetObjectCount() const
    {
        return GetWatchingCount();
    }
    inline Object::Name Object::GetGlobalName() const
    {
        return globalName;
    }
    
    template <typename T>
    inline bool Object::RegisterField(T& value, std::string Name)
    {
        Wrapper new_wrapper = WrapperGenerator<T>::GenerateStaticWrapper(value, memoryManager);
        return memoryBlock.RegisterWrapper(Name, new_wrapper).ok;
    }
    template <typename Out, typename... In>
    inline bool Object::RegisterMethod(std::function<Out(In...)> rvalue, std::string Name)
    {
        MethodWrapper new_wrapper = WrapperGenerator<Out, In...>::GenerateMethodWrapper(rvalue, memoryManager);
        return memoryBlock.RegisterWrapper(Name, new_wrapper).ok;
    }
    inline bool Object::RegisterObject(Object *object) // Now THIS Object can access the other one.
    {
        Watch(object);
        object->RegisterWatcher(this);

        std::string Name = object->GetLocalName();
        return memoryBlock.RegisterFriend(Name, object->GetMemoryBlock().GetSymbolTable()).ok;
    }
    inline void Object::DeregisterField(std::string Name)
    {
        memoryBlock.DeleteByName(Name);
    }
    inline void Object::DeregisterMethod(std::string Name)
    {

        memoryBlock.DeleteByName(Name);
    }
    inline void Object::DeregisterObject(Object *object)
    {
        StopWatching(object);
        object->DeregisterWatcher(this);

        memoryBlock.DeleteFriend(object->GetLocalName());
    }
    inline void Object::AlertDeath(Object *object)
    {
        StopWatching(object);
        DeregisterWatcher(object); 
        memoryBlock.DeleteFriend(object->GetLocalName());       
    }
    inline bool Object::ExecuteScript(std::string)
    {
        return true;
    }

}