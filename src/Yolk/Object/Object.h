#pragma once

#include "Network.h"
#include "../Memory/Memory/MemoryBlock.h"
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
            ObjectOptions(  std::function<void(std::string)> ObjectLogCallback = [](std::string){}, 
                            Memory::Privacy _privacy = Memory::Privacy::Public , 
                            std::function<void(std::string)> MemBlockLogCallback = [](std::string){} )
                    
                    :
                            ObjLogCallback(ObjectLogCallback),
                            privacy(_privacy),
                            memBlockLogCallback(MemBlockLogCallback)
            {}
            
            // Memory Block Options
            std::function<void(std::string)> ObjLogCallback;
            Memory::Privacy privacy;
            std::function<void(std::string)> memBlockLogCallback;
        };
        protected:
        
       
        enum class Mode
        {
            God,
            Follower
        };

        public:

        //protected:
        Object(Name _Name, Memory::MemoryManager& manager, ObjectOptions options = ObjectOptions());
        Object(Name _Name, Father *_Father, ObjectOptions options = ObjectOptions());
        
        virtual ~Object();

        public:

        std::string RequestNewName(std::string RequestedName, Object* Child);
        Name GetLocalName() const;
        Name GetGlobalName() const;

        Memory::MemoryManager& GetMemoryManager() const;
        virtual Memory::MemoryBlock& GetMemoryBlock();
        
        protected:

        template <typename T>
        bool RegisterField(T& lvalue, std::string Name);
        void DeregisterField(std::string Name);
        template <typename Out, typename... In>
        bool RegisterMethod(std::function<Out(In...)> rvalue, std::string Name);
        void DeregisterMethod(std::string Name);

        bool RegisterObject(Object *object);
        
        private:
        bool RegisterObject(Object *object, std::string Name); // <-- todo: Remove this!
        void DeregisterObject(std::string Name);  // <-- todo: Remove this!
        
        protected:
        void DeregisterObject(Object *object); 

        int GetObjectCount() const;

        bool RegisterChild(Object *, std::string Name);
        void DeregisterChild(Object *);
        void DeregisterChild(Name name);
        
        bool ExecuteScript(std::string Script);

        void IsolateSelf();

        void UpdateFather(Object* newFather);

        virtual void DeregisterWatcher(Network* object);

        virtual void InformExistence(Object* object);
        
        private:

        Name CreateChildLocalName(Name local);

        protected:

        private:

        const Name localName;
        const Name globalName;

        Father* father;
        const Mode mode;

        Memory::MemoryManager& memoryManager;
        Memory::MemoryBlock memoryBlock;

        std::vector<Object*> Children;

        protected:
        std::function<void(std::string)> LogCallbackFunction;

    };
    
    inline Object::Object(Name _name, Memory::MemoryManager& manager, ObjectOptions options) : 
            localName(_name),
            globalName(_name),
            father(this), 
            mode(Mode::God), 
            memoryManager(manager),
            memoryBlock(manager, localName, options.privacy, options.memBlockLogCallback),
            LogCallbackFunction(options.ObjLogCallback)

    {
        std::string Log = "[Object:"+ localName +"] INFO: A God has been created: " + globalName;
        LogCallbackFunction(Log);
    }
    
    inline Object::Object(Name _name, Father* _father, ObjectOptions options) :
            localName(_father->RequestNewName(_name, this)),
            globalName(_father->GetGlobalName() + "::" + localName), 
            father(_father), 
            mode(Mode::Follower), 
            memoryManager(_father->GetMemoryManager()),
            memoryBlock(memoryManager,localName, options.privacy, options.memBlockLogCallback),
            LogCallbackFunction(options.ObjLogCallback)
    {
        std::string Log = "[Object:" + localName +"] INFO: Object created: " + globalName;
        LogCallbackFunction(Log);
        father->InformExistence(this);
    }

    inline Object::~Object()
    {
        for(auto& object : Watchers)
        {
            Object *cast = static_cast<Object*>(object);
            cast->DeregisterObject(this);
        }
        if(Children.size() > 0)
        {
            std::string Log = "[Object:"+ localName +"] WARNING: An error has occurred! There is still a child alive during this destruction. Attempting to find adoption.";
            LogCallbackFunction(Log);
        }

        if(mode == Mode::Follower){
            for(auto& c : Children)
            {
                bool result = father->RegisterChild(c, c->GetGlobalName());

                if(!result)
                {
                    std::string Log = "[Object:]"+localName+" CRITICAL ERROR: Failed to register child "+ c->GetGlobalName() + ". Isolating Child!";
                    c->IsolateSelf();
                    LogCallbackFunction(Log);
                    continue;
                }
                //auto newLocalName = father->RequestNewName(c->GetLocalName(), c);
                c->UpdateFather(father);
                //c->localName = newLocalName;
                //c->globalName = father->GetGlobalName() + "::" + newLocalName;
            }
        }

        if(mode == Mode::Follower)
            father->DeregisterChild(this);
        
        std::string Log = "[Object:" + localName+"] INFO: " + globalName + " has been destroyed.";
        LogCallbackFunction(Log);
    }

    inline void Object::UpdateFather(Object* newFather)
    {
         father = newFather;
    }
    inline void Object::IsolateSelf()
    {
        // Todo!
    }
    inline Memory::MemoryManager& Object::GetMemoryManager() const
    {
        return memoryManager;
    }
    
    inline Object::Name Object::RequestNewName(std::string _Name, Object* Child)
    {
        Name childLocalName = CreateChildLocalName(_Name);
        Name childGlobalName = globalName + "::" + childLocalName;

        RegisterChild(Child, childGlobalName);
        return childLocalName;
    }
    inline Object::Name Object::CreateChildLocalName(Name local)
    {
        int i = 0;

        for(auto child : Children)
        {
            std::string currentOption = (i == 0) ? local : local + "_" + std::to_string(i);
            if(child->GetLocalName() == currentOption)
            {
                i++;
            }
        }

        std::string output = (i == 0) ? local : local + "_" + std::to_string(i);
        return output;
    }

    inline bool Object::RegisterChild(Object *child, std::string Name)
    {
        RegisterObject(child, Name);
        for(auto it = Children.begin(); it != Children.end(); it++)
        {
            if(*it == child)
            {
                return false;
            }
        }
        
        Children.push_back(child);
        return true;
    }
    inline void Object::DeregisterWatcher(Network* object)
    {
        std::string Log = "[" + globalName + "] Deregistering watcher!";
        LogCallbackFunction(Log);
        Network::DeregisterWatcher(object);
    }
    inline void Object::DeregisterChild(Object *child)
    {
        DeregisterObject(child);
        for(auto it = Children.begin(); it != Children.end(); it++)
        {
            if(*it == child)
            {
                Children.erase(it);
                return;
            }
        }
    }

    inline Memory::MemoryBlock& Object::GetMemoryBlock()
    {
        return memoryBlock;
    }
    
    inline void Object::DeregisterChild(Name name)
    {
        DeregisterObject(name);
        for(auto it = Children.begin(); it != Children.end(); it++)
        {
            if((*it)->GetGlobalName() == name)
            {
                DeregisterChild(*it);
            }
        }
    }

    template <typename T>
    inline bool Object::RegisterField(T& value, std::string Name)
    {
        Wrapper new_wrapper = WrapperGenerator<T>::GenerateStaticWrapper(value, memoryManager);
        return memoryBlock.RegisterWrapper(Name, new_wrapper);
    }

    template <typename Out, typename... In>
    inline bool Object::RegisterMethod(std::function<Out(In...)> rvalue, std::string Name)
    {
        MethodWrapper new_wrapper = WrapperGenerator<Out, In...>::GenerateMethodWrapper(rvalue, memoryManager);
        return memoryBlock.RegisterWrapper(Name, new_wrapper);
    }

    template <>
    struct WrapperGenerator<Object>
    {
        static Wrapper GenerateObjectWrapper(Object &object, Memory::MemoryManager& manager)
        {
            return manager.RegisterStatic(object);
        };
    };
    inline int Object::GetObjectCount() const
    {
        return GetWatchingCount();
    }
    inline bool Object::RegisterObject(Object *object)
    {
        std::string Name = object->GetGlobalName();
        return RegisterObject(object, Name);
    }
    inline bool Object::RegisterObject(Object *object, std::string Name)
    {
        std::string Log;

        Wrapper object_wrapper = WrapperGenerator<Object>::GenerateObjectWrapper(*object, memoryManager);
        bool o1 = memoryBlock.RegisterObject(Name, object_wrapper);
        bool o2 = Watch(object);

        if(!o1 || !o2)
        {
            Log = "["+globalName+"] ERROR: Failed to register object: " + Name;
            LogCallbackFunction(Log);
            if(o1)
                memoryBlock.DeleteByName(Name);
            if(o2)
                StopWatching(object);
            return false;
        }
        Log = "["+globalName+"] INFO: Registered new object: " + Name;
        LogCallbackFunction(Log);
        return true;
    }
    inline void Object::DeregisterObject(Object *object)
    {
        std::string Log = "["+ globalName +"]Requested Deregister of Object: " + object->GetLocalName();
        LogCallbackFunction(Log);

        std::string Name = object->GetGlobalName();
        memoryBlock.DeleteByName(Name);
        StopWatching(object);
    }
    inline void Object::DeregisterObject(std::string Name)
    {
        for(auto it = Watching.begin(); it != Watching.end(); it++)
        {
            Object *cast = static_cast<Object *>(*it);
            if(cast->GetGlobalName() == Name)
            {
                memoryBlock.DeleteByName(cast->GetGlobalName());
                StopWatching(*it);
                return;
            }
        }
    }
    inline void Object::DeregisterField(std::string Name)
    {
       memoryBlock.DeleteByName(Name);
    }

    inline void Object::DeregisterMethod(std::string Name)
    {
        memoryBlock.DeleteByName(Name);
    }
    inline void Object::InformExistence(Object *object)
    {
        if(mode != Mode::God && father != this) // Second condition should follow trivially from the first. We are still checking just to make sure.
        {
            father->InformExistence(object);
        }
    }

    inline Object::Name Object::GetLocalName() const
    {
        return localName;
    }
    inline Object::Name Object::GetGlobalName() const
    {
        return globalName;
    }

    inline bool Object::ExecuteScript(std::string)
    {
        return true;
    }

}