#pragma once

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
        static MethodWrapper GenerateMethodWrapper(Memory::MemoryAllocator &allocator, std::function<T(F...)> func)
        {
            auto alloc_allocator = allocator.AllocateMemory<std::function<T(F...)>>(func);
            MethodWrapper m(alloc_allocator);
            m.InstantiateWrapper<T, F...>();
            return m;
        }
    };

    template <typename T>
    struct WrapperGenerator<T>
    {
        static MethodWrapper GenerateMethodWrapper(Memory::MemoryAllocator &allocator, std::function<T()> func)
        {
            auto alloc_allocator = allocator.AllocateMemory<std::function<T()>>(func);
            MethodWrapper m(alloc_allocator);
            m.InstantiateWrapper<T>();
            return m;
        }
        static Wrapper GenerateStaticWrapper(Memory::MemoryAllocator &allocator, T &Input)
        {
            return allocator.CreateWrapper(Input);
        }
        static Wrapper GenerateDynamicWrapper(Memory::MemoryAllocator &allocator, T Input)
        {
            return allocator.AllocateMemory(Input);
        }
    };

    template <>
    struct WrapperGenerator<void>
    {
        static MethodWrapper GenerateMethodWrapper(Memory::MemoryAllocator &allocator, std::function<void()> func)
        {
            auto alloc_allocator = allocator.AllocateMemory<std::function<void()>>(func);
            MethodWrapper m(alloc_allocator);
            m.InstantiateWrapper<void>();
            return m;
        }
    };

    template <>
    struct WrapperGenerator<>
    {
        template <typename T, typename... F>
        static WrapperArgument GenerateWrapperArgument(Wrapper w, T arg, F... rest)
        {
            WrapperArgument argument = GenerateWrapperArgument(arg, rest...);
            argument.push_front(w);
            return argument;
        }
        static WrapperArgument GenerateWrapperArgument(Wrapper w)
        {
            WrapperArgument argument = {w};
            return argument;
        }
        static WrapperArgument GenerateWrapperArgument()
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
