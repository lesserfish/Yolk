#pragma once

#include "Wrapper.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include "ArgumentWrapper.h"
#include "ArgumentUnwrapper.h"
#include <memory>
#include <functional>

namespace Yolk
{
    class MethodWrapper : public Wrapper
    {
    private:
        struct InvokeOutput
        {
            Wrapper output;
            bool ok;
            std::string Message;
        };

        struct AbstractInvoker
        {
            virtual ~AbstractInvoker(){}
            virtual InvokeOutput Invoke(Memory::MemoryManager &manager, Wrapper &Function, ArgumentWrapper &Argument) = 0;
            virtual void Debug() { std::cout << "Abstract\n"; }
            virtual std::shared_ptr<AbstractInvoker> Clone() const = 0;
            virtual std::vector<std::type_index> GetInType() const { return {}; }
            virtual std::type_index GetOutType() const { return typeid(void); }
        };
        template <typename T, typename... F>
        struct Invoker : public AbstractInvoker
        {
            using Func = std::function<T(F...)>;

            InvokeOutput Invoke(Memory::MemoryManager &manager, Wrapper &Function, ArgumentWrapper &Argument)
            {
                Wrapper out = manager.AllocateMemory<T>();
                auto func = Function.field->As<std::function<T(F...)>>();
                auto output = ArgumentUnwrapper::Unwrap<T, F...>::Run(func, out, Argument);

                std::string outMessage = output.message;
                bool outOk = output.ok;
                InvokeOutput o{out, outOk, outMessage};
                return o;
            }

            std::type_index GetOutType() const
            {
                return typeid(T);
            }
            std::vector<std::type_index> GetInType() const
            {
                std::vector<std::type_index> TypeArray = {typeid(F)...};
                return TypeArray;
            }
            std::shared_ptr<AbstractInvoker> Clone() const
            {
                return std::make_shared<Invoker<T, F...>>(*this);
            }

            void Debug() { std::cout << "Normal\n"; }
        };

    public:
        MethodWrapper(Identifier _ID, TypedField::Pointer _field, Memory::MemoryManager &manager);
        MethodWrapper(const Wrapper &copy);
        MethodWrapper(const MethodWrapper &copy);
        ~MethodWrapper();
        MethodWrapper &operator=(const MethodWrapper &coy);

        template <typename T, typename... F>
        bool InstantiateWrapper(std::function<T(F...)> _function);

        InvokeOutput Invoke(ArgumentWrapper &Argument);

        std::vector<std::type_index> GetInType() const;
        std::type_index GetOutType() const;
        bool IsValid() const;
        void Free();

    private:
        std::shared_ptr<AbstractInvoker> invoker;
    };

    inline MethodWrapper::MethodWrapper(Identifier _ID, TypedField::Pointer _field, Memory::MemoryManager &manager)
        : Wrapper(_ID, _field, manager, WrapperType::MethodWrapper), invoker(nullptr)
    {
    }
    inline MethodWrapper::MethodWrapper(const Wrapper &copy) : Wrapper(copy), invoker(nullptr)
    {
        wType = WrapperType::MethodWrapper;
    }
    inline MethodWrapper::MethodWrapper(const MethodWrapper &copy) : Wrapper(copy)
    {
        invoker = copy.invoker->Clone();
    }
    inline MethodWrapper &MethodWrapper::operator=(const MethodWrapper &copy)
    {
        Free();
        Wrapper::operator=(copy);
        invoker = copy.invoker->Clone();
        return *this;
    }
    inline void MethodWrapper::Free()
    {
        invoker.reset();
    }
    inline bool MethodWrapper::IsValid() const
    {
        if (invoker)
            return true;
        return false;
    }
    inline MethodWrapper::InvokeOutput MethodWrapper::Invoke(ArgumentWrapper &Argument)
    {
        if (!invoker)
            return (InvokeOutput{manager.AllocateMemory<void>(), false, "Error! The method invocator has not been created!"});
        return invoker->Invoke(manager, *this, Argument);
    }
    template <typename T, typename... F>
    inline bool MethodWrapper::InstantiateWrapper(std::function<T(F...)> _function)
    {
        Free();
        std::type_index memory_type = field->GetType();
        if (memory_type != typeid(std::function<T(F...)>))
            return false;

        if (!field->Copy(_function))
            return false;

        invoker = std::make_shared<Invoker<T, F...>>();

        return true;
    }
    inline std::vector<std::type_index> MethodWrapper::GetInType() const
    {
        if(!invoker)
            return {};
        return invoker->GetInType();
    }
    inline std::type_index MethodWrapper::GetOutType() const
    {
        if(!invoker)
            return typeid(void);
        return invoker->GetOutType();
    }
    inline MethodWrapper::~MethodWrapper()
    {
        Free();
    }
}