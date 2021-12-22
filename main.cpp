#include "src/Yolk/Yolk.h"
#include "src/Yolk/YolkVM/Operators.h"
#include "src/Yolk/YolkVM/Elementary.h"
#include <unordered_map>
#include <map>
#include <typeindex>


int main()
{   
    Yolk::Memory::MemoryManager manager;
    Yolk::VM::Operator op(manager);

    //op.RegisterEquality<int, double>();
    Yolk::VM::GenerateElementaryOperations(op);
    auto a = manager.AllocateMemory<unsigned int>(7);
    auto b = manager.AllocateMemory<int>(12.0);

    std::cout << b.field->GetType().name() << std::endl;
    b.field->CastAs(*a.field);
    std::cout << b.field->GetType().name() << std::endl;

}
