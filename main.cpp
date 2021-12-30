#include "src/Yolk/Yolk.h"
#include <iostream>

int main()
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wtable(manager);
    Yolk::Memory::MemoryBlock memblock(manager, wtable);

    auto wrap = manager.AllocateMemory<int>(-1);
    memblock.RegisterWrapper("myVariable", wrap);

    Yolk::VM::YVM vm(manager, wtable);
    Yolk::VM::GenerateElementaryOperations(vm.opHandler);
    vm.opHandler.RegisterAdd<float, float>();
    vm.opHandler.RegisterCast<int, float>();
    vm.opHandler.RegisterCast<float, int>();

    vm.symTable = &memblock.GetSymbolTable();
    vm.workingSymTable = &memblock.GetSymbolTable();

    Yolk::VM::OVO::Instruction::ARG arg1;
    Yolk::VM::OVO::Instruction::ARG arg2;

    // MOV REGA. "myVariable"
    std::cout << "MOV REGA, myVariable\n";
    arg1.mode = Yolk::VM::OVO::Instruction::ARG::MODE::SYMBOL;
    arg1.value = 0x0;   // REGA
    arg2.mode = Yolk::VM::OVO::Instruction::ARG::MODE::DATA;
    arg2.value = 0x0;

    vm.I_MOV(arg1, arg2);
    manager.Debug();
    vm.Debug();
    std::cout << "...\n";

    // CLONE REGB, INT
    std::cout << "CLONE REGB, INT\n";
    arg1.mode = Yolk::VM::OVO::Instruction::ARG::MODE::SYMBOL;
    arg1.value = 0x01;
    arg2.mode = Yolk::VM::OVO::Instruction::ARG::MODE::SYMBOL;
    arg2.value = 0x05;

    vm.I_CLONE(arg1, arg2);

    manager.Debug();
    vm.Debug();
    std::cout << "...\n";

    // CMPEQ REGA, REGB
    std::cout << "CMPEQ REGA, REGB\n";
    arg1.value = 0x0;
    arg2.value = 0x1;

    vm.I_CMPEQ(arg1, arg2);
    manager.Debug();
    vm.Debug();
    std::cout << "...\n";

    // ADD REGB, REGA
    std::cout << "ADD REGB, REGA\n";
    vm.I_ADD(arg2, arg1);
    manager.Debug();
    vm.Debug();
    std::cout << "...\n";
    
    // ADD REGB, REGB
    std::cout << "ADD REGB, REGB\n";
    
    vm.I_ADD(arg2, arg1);
    manager.Debug();
    vm.Debug();
    std::cout << "...\n";

    // CAST REGB, INT
    std::cout << "CAST REGB, INT\n";

    arg1.value = 0x1; // REGB
    arg2.value = 0x1; // INT

    vm.I_CAST(arg1, arg2);

    manager.Debug();
    vm.Debug();
    std::cout << "...\n";

    // COPY REGA, REGB
    std::cout << "COPY REGA, REGB\n";

    arg1.value = 0x0;
    arg2.value = 0x1;
    vm.I_COPY(arg1, arg2);
    
    manager.Debug();
    vm.Debug();
    std::cout << "...\n";

}