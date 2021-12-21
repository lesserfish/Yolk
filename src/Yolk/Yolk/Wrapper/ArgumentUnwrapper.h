#pragma once

#include "TypedField.h"
#include "ArgumentWrapper.h"

#include <string>
#include <functional>

namespace Yolk
{
    struct UnwrapperOutput
    {
        UnwrapperOutput(bool _ok = true, std::string _message = "") : ok(_ok), message(_message){}
        bool ok;
        std::string message;
    };

    class ArgumentUnwrapper
    {
    public:
        template <typename ReturnType, typename... T>
        struct Unwrap
        {
            template <typename Func, typename... Args>
            static UnwrapperOutput Run(Func &, Wrapper&, ArgumentWrapper& , Args...) { return UnwrapperOutput(false, ""); }
        };

        template <typename ReturnType, typename U, typename... T>
        struct Unwrap<ReturnType, U, T...>
        {
            template <typename Func, typename... Args>
            static UnwrapperOutput Run(Func &function, Wrapper& output, ArgumentWrapper& input, Args... args)
            {
                if (input.size() == 0)
                {
                    return UnwrapperOutput(false, "Error. Not enough arguments passed to function.");
                }
                
                Wrapper v = input.at(0);
                input.pop_front();

                const std::type_index &ti1 = typeid(U);
                const std::type_index &ti2 = v.field->GetType();

                if (ti1 != ti2)
                {
                    return UnwrapperOutput(false, "Error. Argument does not fit required type.");
                }

                U cast = v.field->As<U>();
                return Unwrap<ReturnType, T...>::Run(function, output, input, args..., cast);
            }
        };

        template <typename ReturnType>
        struct Unwrap<ReturnType>
        {
            template <typename Func, typename... Args>
            static UnwrapperOutput Run(Func &function, Wrapper& output, ArgumentWrapper& input, Args... args)
            {
                constexpr bool ReturnTypeNonVoid = !std::is_void<ReturnType>::value;

                const std::type_index &ti1 = typeid(Func);
                const std::type_index &ti2 = typeid(std::function<ReturnType(Args...)>);
                
                if (input.size() > 0)
                {
                    return UnwrapperOutput(false, "Error. Too many arguments passed to function.");
                }

                if(ti1 != ti2)
                {
                    return UnwrapperOutput(false, "Error. Function type and Argument type mismatch.");
                }
                if constexpr(ReturnTypeNonVoid)
                {
                    ReturnType out = function(args...);
                    output.field->Copy(out);
                }
                else
                {
                    function(args...);
                }
                
                return UnwrapperOutput(true, "");
            }
        };
    };
}