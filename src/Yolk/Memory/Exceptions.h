#pragma once

#include "../Exceptions.h"
#include <string>

namespace Yolk
{
    namespace Memory
    {
        struct MException : public Yolk::Exceptions::Exception
        {
            private:
                std::string message;
            public:
                MException(std::string m = "Memory exception thrown.") : Yolk::Exceptions::Exception(m), message(m) {}
                virtual const char* what() const throw() {
                    return message.c_str();
                }
        };
    }
}
