#pragma once

#include <exception>
#include <string>

namespace Yolk
{
    namespace Exceptions
    {
        struct Exception : public std::exception
        {
            private:
                std::string message;
            public:
                Exception(std::string m = "Exception thrown.") : message(m) {}
            virtual const char* what() const throw() {
                return message.c_str();
            }
        };
    }
}
