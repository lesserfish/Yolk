#include "src/Yolk/Yolk.h"
#include "src/Yolk/YolkVM/Operators.h"
#include "src/Yolk/YolkVM/Elementary.h"
#include <unordered_map>
#include <map>
#include <typeindex>

struct A
{
    char x;
    char y;
    char z;
};
int main()
{   
    Yolk::Memory::MemoryManager manager;
    Yolk::VM::Operator op(manager);

    //op.RegisterEquality<int, double>();
    Yolk::VM::GenerateElementaryOperations(op);
    auto b = manager.AllocateMemory<float>(12.5);

    op.RegisterCast<float, int>();
    std::cout << op.EvaluateCast<int>(b).field->Print() << std::endl;
    b.field->Cast<int>();
    std::cout << b.field->Print() << std::endl;

}
