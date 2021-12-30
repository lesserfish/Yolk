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
    Yolk::VM::Elementary::GenerateElementaryOperations(vm.opHandler);

    vm.symTable = &memblock.GetSymbolTable();
    vm.workingSymTable = &memblock.GetSymbolTable();

    Yolk::VM::OVO::Instruction::ARG arg1;
    Yolk::VM::OVO::Instruction::ARG arg2;

    // MOV REGA. "myVariable"
    std::cout << "\n\tMOV REGA, myVariable\n";
    arg1.mode = Yolk::VM::OVO::Instruction::ARG::MODE::SYMBOL;
    arg1.value = 0x0;   // REGA
    arg2.mode = Yolk::VM::OVO::Instruction::ARG::MODE::DATA;
    arg2.value = 0x0;

    vm.I_MOV(arg1, arg2);
    manager.Debug();
    std::cout << "\n";
    vm.Debug();

    // CLONE REGB, INT
    std::cout << "\n\tCLONE REGB, FLOAT\n\n";
    arg1.mode = Yolk::VM::OVO::Instruction::ARG::MODE::SYMBOL;
    arg1.value = 0x01;
    arg2.mode = Yolk::VM::OVO::Instruction::ARG::MODE::SYMBOL;
    arg2.value = 0x05;

    vm.I_CLONE(arg1, arg2);

    manager.Debug();
    std::cout << "\n";
    vm.Debug();

    // CMPEQ REGA, REGB
    std::cout << "\n\tCMPNEQ REGA, REGB\n\n";
    arg1.value = 0x0;
    arg2.value = 0x1;

    vm.I_CMPNEQ(arg1, arg2);
    manager.Debug();
    std::cout << "\n";
    vm.Debug();

    // ADD REGB, REGA
    std::cout << "\n\tADD REGB, REGA\n\n";
    vm.I_ADD(arg2, arg1);
    manager.Debug();
    std::cout << "\n";
    vm.Debug();
    
    // ADD REGB, REGB
    std::cout << "\n\tADD REGB, REGB\n\n";
    
    vm.I_ADD(arg2, arg1);
    manager.Debug();
    std::cout << "\n";
    vm.Debug();

    // CAST REGB, INT
    std::cout << "\n\tCAST REGB, INT\n\n";

    arg1.value = 0x1; // REGB
    arg2.value = 0x1; // INT

    vm.I_CAST(arg1, arg2);

    manager.Debug();
    std::cout << "\n";
    vm.Debug();

    // COPY REGA, REGB
    std::cout << "\n\tCOPY REGA, REGB\n\n";

    arg1.value = 0x0;
    arg2.value = 0x1;
    vm.I_COPY(arg1, arg2);
    
    manager.Debug();
    std::cout << "\n";
    vm.Debug();

}