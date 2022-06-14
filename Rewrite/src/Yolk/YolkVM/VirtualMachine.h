#include "../Memory/Memory.h"

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
