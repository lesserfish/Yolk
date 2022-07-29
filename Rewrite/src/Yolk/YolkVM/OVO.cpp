#include "OVO.h"
#include "Instruction.h"
#include "../Exceptions.h"
#include <algorithm>

namespace Yolk
{
    namespace VM
    {
        OPCode OPFromString(std::string input)
        {
            std::transform(input.begin(), input.end(), input.begin(), ::toupper);
            for(auto it = AllOPCodes.begin(); it != AllOPCodes.end(); it++)
            {
                auto instruction = Instruction::Select(*it);
                std::string asstring = instruction->to_string();

                if(input.compare(asstring))
                {
                    return *it;
                }
            }
            throw Exceptions::Exception("Could not find instruction with name " + input);
        }
    }
}
