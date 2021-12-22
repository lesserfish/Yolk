#include "src/Yolk/Yolk.h"
#include "src/Yolk/YolkVM/Operators.h"

int main()
{
    Yolk::Memory::MemoryManager manager;
    Yolk::VM::Operator op(manager);

    op.RegisterAdd<int, int>();
    auto a = manager.AllocateMemory<int>(7);
    auto b = manager.AllocateMemory<int>(8);

    auto c = op.EvaluateAdd(a, b);

    std::cout << c.field->Print() << std::endl;
}
