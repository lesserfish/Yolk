#include "VirtualMachine.h"

namespace Yolk
{
    namespace VM
    {
        VirtualMachine::VirtualMachine(Memory::DynamicMemory& mem, Memory::MemoryInterface* meminterface) :
            memory(mem),
            baseInterface(meminterface),
            currentInterface(meminterface),
            rega(mem.GetVoidWrapper()),
            regb(mem.GetVoidWrapper()),
            regc(mem.GetVoidWrapper()),
            regd(mem.GetVoidWrapper()),
            regout(mem.GetVoidWrapper()),
            regm(mem.GetVoidWrapper())
        {}
        Wrapper& VirtualMachine::SelectRegister(uint64_t value)
        {
            RegisterType reg = static_cast<RegisterType>(value);
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
                    std::string error = "Received request for non-existent register. Requested register with value " + std::to_string(value);
                    throw std::invalid_argument(error);
            };
        }
        std::string VirtualMachine::SelectText(uint64_t )
        {
            return "";
        }

    }
}
