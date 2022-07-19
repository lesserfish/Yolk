#include "VirtualMachine.h"

namespace Yolk
{
    namespace VM
    {
        Wrapper& VirtualMachine::SelectRegister(Ovo::Code::Arg& arg)
        {
            RegisterType reg = static_cast<RegisterType>(arg.value);
            switch(reg)
            {
                case RegisterType::REGA:
                    return rega;
                case RegisterType::REGB:
                    return regb;
                case RegisterType::REGC:
                    return regc;
                case RegisterType::REGD:
                    return regd;
                case RegisterType::REGOUT:
                    return regout;
                case RegisterType::REGM:
                    return regm;
                default:
                    std::string error = "Received request for non-existent register. Requested register with value " + std::to_string(arg.value);
                    throw std::invalid_argument(error);
            };
        }

    }
}
