#pragma once

#include "Wrapper.h"
#include <vector>
#include <deque>

namespace Yolk
{
    using ArgumentWrapper = std::deque<Wrapper>;
    inline ArgumentWrapper VoidWrapper = {};

    inline ArgumentWrapper& operator<<(ArgumentWrapper& argument, Wrapper wrapper)
    {
        argument.push_back(wrapper);
        return argument;
    }
}