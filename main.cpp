#include "src/Yolk/Yolk.h"
#include "src/Yolk/YolkVM/Operators.h"
#include "src/Yolk/YolkVM/Elementary.h"
#include <unordered_map>
#include <map>
#include <typeindex>

struct A
{
    char x;
};
int main()
{   
    Yolk::Memory::MemoryManager manager;
    Yolk::VM::Operator op(manager);

    //op.RegisterEquality<int, double>();
    Yolk::VM::GenerateElementaryOperations(op);
    auto a = manager.AllocateMemory<unsigned int>(7);
    auto b = manager.AllocateMemory<int>(12);

    op.RegisterCast<int, float>();
    op.RegisterCast<float, int>();

    std::cout << a.field->GetType().name() << std::endl;
    a.field->CastAs(*b.field);
    std::cout << a.field->GetType().name() << std::endl;

    //std::cout << op.EvaluateCast<A>(b).field->Print() << std::endl;
    std::cout << op.EvaluateCast<float>(b).field->Print() << std::endl;
}
