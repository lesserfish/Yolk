#include "src/Yolk/Yolk.h"
#include <iostream>

int main()
{
    Yolk::Memory::MemoryManager manager;

    auto w = manager.AllocateMemory(7);
    auto w2 = manager.AllocateMemory(12);
    Yolk::Wrapper reg = manager.GenerateVoidWrapper();    
    std::cout << "2: " << manager.Size() << std::endl;
    reg = manager.CopyByValue(w);
    std::cout << "3: " << manager.Size() << std::endl;
    reg = w2;
    std::cout << "2: " << manager.Size() << std::endl;
}