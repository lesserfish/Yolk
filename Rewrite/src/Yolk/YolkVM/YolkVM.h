#include "../Memory/Memory.h"

namespace Yolk
{
    namespace VM
    {
        class YolkVM
        {
            public:
                enum class Status : uint8_t
                {
                    PENDING,
                    RUNNING,
                    HALTED,
                    ERROR
                };
            private:

        };
    }
}
