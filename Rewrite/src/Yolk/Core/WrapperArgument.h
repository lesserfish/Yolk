#pragma once

#include <vector>
#include <deque>
#include <string>
#include <functional>

namespace Yolk
{
    using WrapperArgument = std::deque<Wrapper>;
    
    inline WrapperArgument VoidWrapper = {};
    inline WrapperArgument& operator<<(WrapperArgument& argument, Wrapper wrapper)
    {
        argument.push_back(wrapper);
        return argument;
    }

    struct UnwrapperOutput
    {
        UnwrapperOutput(Wrapper w, bool _ok = true, std::string _message = "") : wrapper(w), ok(_ok), message(_message){}
        Wrapper wrapper;
        bool ok;
        std::string message;
    };
    
    template<bool strict = true> 
    class ArgumentUnwrapper
    {
    public:
        template <typename ReturnType, typename... T>
        struct Unwrap
        {
            template <typename Func, typename... Args>
            static UnwrapperOutput Run(Memory::DynamicMemory& memory, Func &, WrapperArgument& , Args...) {  return UnwrapperOutput(memory.GetVoidWrapper(), false, ""); }
        };
        template <typename ReturnType, typename U, typename... T>
        struct Unwrap<ReturnType, U, T...>
        {
            template <typename Func, typename... Args>
            static UnwrapperOutput Run(Memory::DynamicMemory& memory, Func &function, WrapperArgument& input, Args... args)
            {
                if (input.size() == 0)
                {
                    return UnwrapperOutput(memory.GetVoidWrapper(), false, "Not enough arguments passed to function.");
                }
                
                Wrapper v = input.at(0);
                input.pop_front();

                    
                if(strict){
                    const std::type_index &ti1 = typeid(U);
                    const std::type_index &ti2 = v.field->Type();

                    if (ti1 != ti2)
                    {
                        return UnwrapperOutput(memory.GetVoidWrapper(), false, "Argumend does not fit required type.");
                    }
                }

                U cast = v.field->As<U>();
                return Unwrap<ReturnType, T...>::Run(memory, function, input, args..., cast);
            }
        };

        template <typename ReturnType>
        struct Unwrap<ReturnType>
        {
            template <typename Func, typename... Args>
            static UnwrapperOutput Run(Memory::DynamicMemory& memory, Func &function, WrapperArgument& input, Args... args)
            {
                if (input.size() > 0)
                {
                    return UnwrapperOutput(memory.GetVoidWrapper(), false, "Too many arguments passed to function.");
                }

                if(strict){
                    const std::type_index &ti1 = typeid(Func);
                    const std::type_index &ti2 = typeid(std::function<ReturnType(Args...)>);
                    if(ti1 != ti2)
                    {
                        return UnwrapperOutput(memory.GetVoidWrapper(), false, "Function type and Argument type mismatch.");
                    }
                }
                

                constexpr bool CanEvaluate = requires(Args... a){
                    function(a...);
                };
                
                if constexpr(!CanEvaluate) {
                    return UnwrapperOutput(memory.GetVoidWrapper(), false, "Function type and Argument type mismatch.");
                }
                
                constexpr bool ReturnTypeIsVoid = std::is_void<ReturnType>::value;

                if constexpr(ReturnTypeIsVoid) {
                    function(args...);
                    return UnwrapperOutput(memory.GetVoidWrapper(), true, "");
                } else{
                    ReturnType ret = function(args...);
                    auto out = memory.AllocateMemory<ReturnType>(ret);

                    if(!out.ok){
                        return UnwrapperOutput(out.wrapper, false, "Failed to allocate for output value.");
                    }
                    return UnwrapperOutput(out.wrapper, true, "");
                }
                
                //return UnwrapperOutput(true, "");
            }
        };
    };
}

