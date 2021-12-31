#include "src/Yolk/YolkVM/Elementary.h"
#include "src/Yolk/Wrapper/WrapperGenerator.h"
#include "src/Yolk/YolkVM/Assembler.h"
#include <iostream>
#include <chrono>

void Print(int x)
{
    std::cout << "Result: " << x << std::endl;
}
int main()
{

    // TODO: INC and DEC instructions. Should have the form
    // INC REGX
    // DEC REGX
    // INC REGX symbol containing an integer
    // DEC REGX symbol containing an integer
    //
    // ADD and DEC should have the possibility of elementary additions, like
    // ADD REGX, i32.127.
    // Same for MUL, DIV, MOD, AND and OR.

    std::string Content = 
    "MOVM str:Print\n"
    "CLONE REGA, i32:1\n"
    "CLONE REGC, i32:0\n"
    "NEW REGB, INT\n"
    ".loop_begin:\n"
    "CMPEQ REGB, i32:100000\n"
    "JNTRUE .loop_end\n"
    "ADD REGB, REGA\n"
    "ADD REGC, REGB\n"
    "JMP .loop_begin\n"
    ".loop_end:\n"
    "PUSHAR REGC\n"
    "CALLM\n";

    auto ovo = Yolk::VM::Assembler::Assemble(Content);

    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wtable(manager);
    Yolk::Memory::MemoryBlock memblock(manager, wtable);

    auto w = Yolk::WrapperGenerator<void,int>::GenerateMethodWrapper(Print, manager);
    memblock.RegisterWrapper("Print", w);

    Yolk::VM::YVM vm(manager, wtable);
    Yolk::VM::Elementary::GenerateElementaryOperations(vm.GetOpHandler());

    std::chrono::steady_clock Clock;

    auto start = Clock.now();
    vm.Run(ovo, memblock.GetSymbolTable());
    auto stop = Clock.now();
    std::cout << "Timer: " << std::chrono::duration<double, std::micro>(stop - start).count() << std::endl;
    std::cout << vm.GetMessage() << std::endl << vm.GetClock() << std::endl;


}