#pragma once

#include "../Exceptions.h"
#include <memory>
#include <functional>


namespace Yolk
{
    class MethodWrapper : public Wrapper
    {
    private:
        
        struct AbstractInvoker
        {
            virtual ~AbstractInvoker(){}
            virtual Wrapper Invoke(Memory::MemoryAllocator &allocator, Wrapper &Function, WrapperArgument &Argument) = 0;
            virtual void Debug() { std::cout << "Abstract\n"; }
            virtual std::shared_ptr<AbstractInvoker> Clone() const = 0;
            virtual std::vector<std::type_index> GetInType() const { return {}; }
            virtual std::type_index GetOutType() const { return typeid(void); }
        };
        template <typename T, typename... F>
        struct Invoker : public AbstractInvoker
        {
            using Func = std::function<T(F...)>;

            Wrapper Invoke(Memory::MemoryAllocator &allocator, Wrapper &Function, WrapperArgument &Argument)
            {
                auto func = Function.field->As<std::function<T(F...)>>();
                auto out = ArgumentUnwrapper<>::Unwrap<T, F...>::Run(allocator, func, Argument);
                return out;
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
        MethodWrapper(Identifier _ID, TypedField::Pointer _field, Memory::MemoryAllocator &allocator);
        MethodWrapper(const Wrapper &copy);
        MethodWrapper(const MethodWrapper &copy);
        ~MethodWrapper();
        MethodWrapper &operator=(const MethodWrapper &coy);

        template <typename T, typename... F>
        bool InstantiateWrapper(std::function<T(F...)> _function);
        template <typename T, typename... F>
        bool InstantiateWrapper();
        
        Wrapper Invoke(WrapperArgument &Argument);

        std::vector<std::type_index> GetInType() const;
        std::type_index GetOutType() const;
        bool IsValid() const;
        void Free();

    private:
        std::shared_ptr<AbstractInvoker> invoker;
    };

    inline MethodWrapper::MethodWrapper(Identifier _ID, TypedField::Pointer _field, Memory::MemoryAllocator &allocator)
        : Wrapper(_ID, _field, allocator, WrapperType::MethodWrapper), invoker(nullptr)
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
    inline MethodWrapper::Wrapper MethodWrapper::Invoke(WrapperArgument &Argument)
    {
        if (!invoker){
            throw Exceptions::Exception("Method Wrapper exception: The method invocated has not been created.");
        }
        return invoker->Invoke(allocator, *this, Argument);
    }
    template <typename T, typename... F>
    inline bool MethodWrapper::InstantiateWrapper(std::function<T(F...)> _function)
    {
        Free();
        std::type_index memory_type = field->Type();
        
        if (memory_type != typeid(std::function<T(F...)>))
            return false;
        
        field->Set(_function);

        invoker = std::make_shared<Invoker<T, F...>>();
        return true;
    }
    template <typename T, typename... F>
    inline bool MethodWrapper::InstantiateWrapper()
    {
        Free();
        std::type_index memory_type = field->Type();
        if (memory_type != typeid(std::function<T(F...)>))
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
