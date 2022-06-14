#include "src/Yolk/Yolk.h"
#include <iostream>
#include <string>
#include <cstdio>

int main(){
    for(const auto& it : Yolk::VM::AllOPCodes) 
    {
        std::cout << Yolk::VM::Instruction::Select(it)->to_string() << std::endl;
    }
}
