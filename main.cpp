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
    auto a = manager.AllocateMemory<int>(7);
    auto b = manager.AllocateMemory<double>(7.0);
    auto c = op.EvaluateEquality(a, b);
    std::cout << c.field->Print() << std::endl;

    std::cout << a.field->GetType().name() << " - " << a.field->Print() << std::endl;
    a.field->Cast<unsigned int>();
    std::cout << a.field->GetType().name() << " - " << a.field->Print() << std::endl;

}
