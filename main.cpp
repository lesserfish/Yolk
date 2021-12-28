#include "src/Yolk/Yolk.h"
#include <unordered_map>
#include <map>
#include <typeindex>
#include <cstring>
#include <cstddef>

using Data = Yolk::VM::OVO::Data;

int main()
{
    Yolk::Memory::MemoryManager manager;

    auto d = Data(12);
    std::string str = Data::ToString(d);
    auto n = Data::FromString(str);

    std::cout << n.size << std::endl;
    std::cout << (n.mode == Data::Mode::INT) << std::endl;

    auto w = Data::ToWrapper(n, manager);
    std::cout << w.field->Print() << std::endl;

    for(auto x : str)
    {
        std::cout <<(unsigned short int )x;
    }
    std::cout << std::endl;
}
