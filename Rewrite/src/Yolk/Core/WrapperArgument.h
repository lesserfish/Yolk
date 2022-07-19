#pragma once

#include "../Exceptions.h"
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

    
    template<bool strict = true> 
    class ArgumentUnwrapper
    {
    public:
        template <typename ReturnType, typename... T>
        struct Unwrap
        {
            template <typename Func, typename... Args>
            static Wrapper Run(Memory::DynamicMemory& memory, Func &, WrapperArgument& , Args...) {
                throw Exceptions::Exception("");
            }
        };
        template <typename ReturnType, typename U, typename... T>
        struct Unwrap<ReturnType, U, T...>
        {
            template <typename Func, typename... Args>
            static Wrapper Run(Memory::DynamicMemory& memory, Func &function, WrapperArgument& input, Args... args)
            {
                if (input.size() == 0)
                {
                    throw Exceptions::Exception("Argument Unwrapper exception. Not enough arguments passed to function.");
                }
                
                Wrapper v = input.at(0);
                input.pop_front();

                    
                if(strict){
                    const std::type_index &ti1 = typeid(U);
                    const std::type_index &ti2 = v.field->Type();

                    if (ti1 != ti2)
                    {
                        throw Exceptions::Exception("Argument Unwrapper exception. Argumend does not fit required type.");
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
            static Wrapper Run(Memory::DynamicMemory& memory, Func &function, WrapperArgument& input, Args... args)
            {
                if (input.size() > 0)
                {
                    throw Exceptions::Exception("Argumnent Unwrapper exception. Too many arguments passed to function.");
                }

                if(strict){
                    const std::type_index &ti1 = typeid(Func);
                    const std::type_index &ti2 = typeid(std::function<ReturnType(Args...)>);
                    if(ti1 != ti2)
                    {
                        throw Exceptions::Exception("Argument Unwrapper exception. Function type and Argument type mismatch.");
                    }
                }
                

                constexpr bool CanEvaluate = requires(Args... a){
                    function(a...);
                };
                
                if constexpr(!CanEvaluate) {
                    throw Exceptions::Exception("Argument Unwrapper exception. Function type and Argument type mismatch.");
                }
                
                constexpr bool ReturnTypeIsVoid = std::is_void<ReturnType>::value;

                if constexpr(ReturnTypeIsVoid) {
                    function(args...);
                    return memory.GetVoidWrapper();
                } else{
                    ReturnType ret = function(args...);
                    try{
                        auto out = memory.AllocateMemory<ReturnType>(ret);
                        return out;
                    } catch(const Exceptions::Exception& exception)
                    {
                        throw Exceptions::Exception("Argument Unwrapper exception. Failed to allocate for output value.");
                    }
                }
                
                //return true, "";
            }
        };
    };
}

