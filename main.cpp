#include "src/Yolk/Yolk.h"
#include <unordered_map>
#include <map>
#include <typeindex>
#include <cstring>
#include <cstddef>

int FunctionTest(int a, float b)
{
    int o = a + (int)b;
    return o;
}
int main()
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::MemoryBlock memblock(manager);

    auto m = Yolk::WrapperGenerator<int, int, float>::GenerateMethodWrapper(FunctionTest, manager);
    memblock.RegisterWrapper("GetInfo", m);

    Yolk::Wrapper REGA(manager.GenerateVoidWrapper());
    Yolk::Wrapper REGOUT(manager.GenerateVoidWrapper());
    Yolk::MethodWrapper MREG(manager.GenerateVoidWrapper());
    Yolk::ArgumentWrapper ARGREG;

    // var output = GetInfo(2, 3.14f);  <-- Command we are going to run.

    // mov REGA, 2
    REGA = manager.AllocateMemory<int>(2);
    // pushar REGA
    ARGREG << REGA;
    // mov REGA, 3.14f
    REGA = manager.AllocateMemory<float>(7.14f);
    // pushar REGA
    ARGREG << REGA;
    // movr "GetInfo"
    MREG = memblock.GetMethodWrapperByName("GetInfo");
    // callm
    auto o = MREG.Invoke(ARGREG);
    REGOUT = o.output;
    // mov REGA, REGOUT
    REGA = REGOUT;
    // namel REGA, "output"
    memblock.RegisterWrapper("output", REGA);

    auto w = memblock.GetFieldWrapperByName("output");

    manager.Debug();
}
