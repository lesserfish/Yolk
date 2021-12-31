#include "src/Yolk/YolkVM/YVM.h"
#include "src/Yolk/YolkVM/Elementary.h"
#include <iostream>

using Instruction = Yolk::VM::OVO::Instruction;
using Arg = Yolk::VM::OVO::Instruction::ARG;
using Data = Yolk::VM::OVO::Data;

int main()
{
    Yolk::Memory::MemoryManager manager;
    Yolk::Memory::WrapperTable wtable(manager);
    Yolk::Memory::MemoryBlock memblock(manager, wtable);

    auto wrap = manager.AllocateMemory<int>(-1);
    memblock.RegisterWrapper("myVariable", wrap);
    
    Yolk::VM::YVM vm(manager, wtable);
    Yolk::VM::Elementary::GenerateElementaryOperations(vm.GetOpHandler());

    Yolk::VM::OVO ovo;
    ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::MOV, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::DATA, 0x0}}); // MOV REGA, myVariable
    ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::NEW, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x05}}); // CLONE REGB, FLOAT
    ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CMPNEQ, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::REG, 0x1}}); // CMPNEQ REG0, REGB
    ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::ADD, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::REG, 0x0}}); // ADD REGB, REGA
    ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::ADD, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::REG, 0x1}}); // ADD REGB, REGB
    ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::CAST, Arg{ Arg::MODE::REG, 0x1}, Arg { Arg::MODE::SYMBOL, 0x1}}); // CAST REGB, INT
    ovo.InstructionSet.push_back(Instruction{Instruction::INSTRUCTION::COPY, Arg{ Arg::MODE::REG, 0x0}, Arg { Arg::MODE::REG, 0x1}}); // COPY REGA, REGB

    ovo.DataSet.push_back(Data::GenerateData(std::string("myVariable")));

    vm.Run(ovo, memblock.GetSymbolTable());

    std::cout << vm.GetMessage() << std::endl;
    std::cout << vm.GetClock() << std::endl;
    vm.Debug();
}