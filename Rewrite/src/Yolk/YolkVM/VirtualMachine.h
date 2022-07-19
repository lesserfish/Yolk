#pragma once


#include "../Memory/Memory.h"
#include "../Core/Core.h"
#include "OVO.h"

namespace Yolk
{
    namespace VM
    {
        enum class Status : uint8_t {
            RUNNING,
            HALTED,
            ERROR
        };

        class VirtualMachine 
        {
            public:
                friend class Instruction;
                Wrapper& SelectRegister(Ovo::Code::Arg&);
            private:
                Wrapper rega;
                Wrapper regb;
                Wrapper regc;
                Wrapper regd;
                Wrapper regout;
                MethodWrapper regm;
                bool regcmp;
                WrapperArgument regarg;
                std::deque<Wrapper> stack;
                std::vector<Ovo::Code>::iterator ip;
        };
        
    }
}
