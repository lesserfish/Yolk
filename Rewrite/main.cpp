#include "src/Yolk/Core/Core.h"
#include "src/Yolk/Memory/Memory.h"
#include "src/Yolk/YolkVM/VM.h"
#include <iostream>
#include <string>
#include <cstdio>

int main(){
    Yolk::VM::Ovo ovo;
    ovo.version = 0.1;
    ovo.code.push_back(Yolk::VM::Ovo::Code { Yolk::VM::Instruction::COPY, Yolk::VM::Ovo::Code::Arg {Yolk::VM::ArgType::REGISTER, 0}, Yolk::VM::Ovo::Code::Arg {Yolk::VM::ArgType::REGISTER, 1}});
    ovo.text.push_back(Yolk::VM::Ovo::Text("Hello there friend!"));
    ovo.text.push_back(Yolk::VM::Ovo::Text("This is the end."));
    ovo.ToFile("./demo.ovo");
    Yolk::VM::Ovo newovo;

    bool test = newovo.FromFile("./demo.ovo");

    std::cout << test << std::endl;

    std::cout << newovo.version << std::endl;

    for(auto it = newovo.code.begin(); it != newovo.code.end(); it++)
    {
        std::cout << static_cast<int>(it->instruction) << std::endl;
    }
    for(auto it = newovo.text.begin(); it != newovo.text.end(); it++)
    {
        std::cout << it->content << std::endl;
    }
}
