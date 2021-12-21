#pragma once

#include "Wrapper.h"
#include "MethodWrapper.h"
#include "ArgumentWrapper.h"
#include "../Memory/MemoryManager/MemoryManager.h"
#include <functional>

namespace Yolk
{
    template <typename... F>
    struct WrapperGenerator
    {
    };

    template <typename T, typename... F>
    struct WrapperGenerator<T, F...>
    {
        static MethodWrapper GenerateMethodWrapper(std::function<T(F...)> Input, Memory::MemoryManager &manager)
        {
            auto alloc_memory = manager.AllocateMemory<std::function<T(F...)>>();
            MethodWrapper m(alloc_memory);
            m.InstantiateWrapper(Input);
            return m;
        }
    };

    template <typename T>
    struct WrapperGenerator<T>
    {
        static MethodWrapper GenerateMethodWrapper(std::function<T()> Input, Memory::MemoryManager &manager)
        {
            auto alloc_memory = manager.AllocateMemory<std::function<T()>>();
            MethodWrapper m(alloc_memory);
            m.InstantiateWrapper(Input);
            return m;
        }
        static Wrapper GenerateStaticWrapper(T &Input, Memory::MemoryManager &manager)
        {
            return manager.RegisterStatic<T>(Input);
        }
        static Wrapper GenerateDynamicWrapper(T Input, Memory::MemoryManager &manager)
        {
            return manager.AllocateMemory<T>(Input);
        }
    };

    template <>
    struct WrapperGenerator<void>
    {
        static MethodWrapper GenerateMethodWrapper(std::function<void()> Input, Memory::MemoryManager &manager)
        {
            auto alloc_memory = manager.AllocateMemory<std::function<void()>>();
            MethodWrapper m(alloc_memory);
            m.InstantiateWrapper(Input);
            return m;
        }
    };

    template <>
    struct WrapperGenerator<>
    {
        template <typename T, typename... F>
        static ArgumentWrapper GenerateArgumentWrapper(Wrapper w, T arg, F... rest)
        {
            ArgumentWrapper argument = GenerateArgumentWrapper(arg, rest...);
            argument.push_front(w);
            return argument;
        }
        static ArgumentWrapper GenerateArgumentWrapper(Wrapper w)
        {
            ArgumentWrapper argument = {w};
            return argument;
        }
        static ArgumentWrapper GenerateArgumentWrapper()
        {
            return VoidWrapper;
        }
    };


    template <typename T, typename... F>
    struct FunctionGenerator
    {
        static std::function<T(F...)> AsFunction(std::function<T(F...)> _func)
        {
            return _func;
        }
    };

}